#include "stdafx.h"
#include "CameraMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"

CCameraMgr*							CCameraMgr::m_pInstance = nullptr;

CCameraMgr::CCameraMgr()
	:m_fScrollX(-1000.0f), m_fScrollY(-200.0f), m_vCameraPos(CMyVector2(0.0f,0.0f)), m_bMouseScroll(true), m_bStopX(false), m_bStopY(false), m_bMouse(false)
{
}


CCameraMgr::~CCameraMgr()
{
}

void CCameraMgr::Initialize(void)
{
	m_CameraState = CAMERA_STATE::NORMAL;

	m_vCameraPos.fCX = WINCX;
	m_vCameraPos.fCY = WINCY;

	Set_Mouse();

	ShowCursor(false);

	Set_CenterPoint();

	m_iShakeDelay = 500;
	m_iShakeStart = 0;
}

void CCameraMgr::Go_Target(CObj* _pObj)
{
	m_vGoTargetPos = _pObj->Get_Pos();
	m_CameraState = CAMERA_STATE::GOTARGET;
	CSoundMgr::Get_Instance()->StopSound(CHANNELID::GAMESOUND);
	CSoundMgr::Get_Instance()->PlaySoundW(L"CameraPan.wav", CHANNELID::GAMESOUND, g_fVolume);
}

void CCameraMgr::Go_Target(CMyVector2 _vPos)
{
	m_vGoTargetPos = _vPos;
	m_CameraState = CAMERA_STATE::GOTARGET;
	CSoundMgr::Get_Instance()->StopSound(CHANNELID::GAMESOUND);
	CSoundMgr::Get_Instance()->PlaySoundW(L"CameraPan.wav", CHANNELID::GAMESOUND, g_fVolume);
}

void CCameraMgr::Follow_Target(CObj* _pObj)
{
	m_pTarget = _pObj;
	m_pTargetPos = m_pTarget->Get_pPos();
	m_CameraState = CAMERA_STATE::FOLLOWTARGET;
}


void CCameraMgr::ShowMouse(void)
{
	m_CameraState = CAMERA_STATE::GETMOUSE;
	m_bMouse = true;
	m_bMouseScroll = false;
	Show_Cursor();
}

void CCameraMgr::PutMouse(void)
{
	m_CameraState = CAMERA_STATE::NORMAL;
	m_bMouse = false;
	m_bMouseScroll = true;
	Show_Cursor();
}

void CCameraMgr::Camera_Shake(void)
{
	if (m_CameraState == CAMERA_STATE::NORMAL)
	{
		m_fPrevScrollX = m_fScrollX;
		m_fPrevScrollY = m_fScrollY;

		m_iShakeStart = GetTickCount();

		m_CameraState = CAMERA_STATE::CAMERASHAKE;
	}
}

void CCameraMgr::Update(void)
{
	switch (m_CameraState)
	{
	case CAMERA_STATE::NORMAL:
		break;
	case CAMERA_STATE::FOLLOWTARGET:
		FollowTargetUpdate();
		break;
	case CAMERA_STATE::GOTARGET:
		GoTargetUpdate();
		break;
	case CAMERA_STATE::GETMOUSE:

		break;
	case CAMERA_STATE::CAMERASHAKE:
		ShakeUpdate();
		break;

	}


	Set_Mouse();

	Key_Input();

	if(m_bMouseScroll)
		Mouse_Scroll();
		

	


}

void CCameraMgr::LateUpdate(void)
{
	MapOut();

	Set_CameraPos();

	switch (m_CameraState)
	{
	case CAMERA_STATE::NORMAL:
		break;
	case CAMERA_STATE::FOLLOWTARGET:
		FollowTargetLateUpdate();
		break;
	case CAMERA_STATE::GOTARGET:
		GoTargetLateUpdate();
		break;
	case CAMERA_STATE::GETMOUSE:
		MouseUpdate();
		break;
	case CAMERA_STATE::CAMERASHAKE:
		ShakeLateUpdate();
		break;
	}
}



void CCameraMgr::Key_Input(void)
{
	if (CKeyMgr::Get_Inst()->Key_Down('P'))
	{
		ShowMouse();
	}
	if (CKeyMgr::Get_Inst()->Key_Down('O'))
	{
		PutMouse();
	}

	if (CKeyMgr::Get_Inst()->Key_Pressing(VK_NUMPAD4))
	{
		m_fScrollX += 10.0f;
	}
	if (CKeyMgr::Get_Inst()->Key_Pressing(VK_NUMPAD6))
	{
		m_fScrollX -= 10.0f;
	}
	if (CKeyMgr::Get_Inst()->Key_Pressing(VK_NUMPAD8))
	{
		m_fScrollY += 10.0f;

	}
	if (CKeyMgr::Get_Inst()->Key_Pressing(VK_NUMPAD5))
	{
		m_fScrollY -= 10.0f;
	}

	if (CKeyMgr::Get_Inst()->Key_Down('K'))
	{
		Camera_Shake();
	}


}

void CCameraMgr::MapOut(void)
{
	if (m_fScrollX < -2400.0f)
		m_fScrollX = -2400.0f;

	if (m_fScrollY < -400.0f)
		m_fScrollY = -400.0f;

	if (m_fScrollX > 0.0f)
		m_fScrollX = 0.0f;
	
	if (m_fScrollY > 0.0f)
		m_fScrollY = 0.0f;
}

void CCameraMgr::Set_CameraPos(void)
{
	m_vCameraPos.fX = (m_fScrollX * -1) + 800.0f;
	m_vCameraPos.fY = (m_fScrollY * -1) + 450.0f;

	m_tCameraRect.left = m_vCameraPos.fX - m_vCameraPos.fCX * 0.5f;
	m_tCameraRect.top = m_vCameraPos.fY - m_vCameraPos.fCY * 0.5f;
	m_tCameraRect.right = m_vCameraPos.fX + m_vCameraPos.fCX * 0.5f;
	m_tCameraRect.bottom = m_vCameraPos.fY + m_vCameraPos.fCY * 0.5f;
}

void CCameraMgr::Set_Mouse(void)
{
	GetCursorPos(&m_Mouse);
	//ScreenToClient(g_hWnd, &m_Mouse);
}

void CCameraMgr::Mouse_Scroll(void)
{
	if (m_Mouse.x != m_Center.x || m_Mouse.y != m_Center.y)
	{
		m_fScrollX -= (m_Mouse.x - m_Center.x);
		m_fScrollY -= (m_Mouse.y - m_Center.y);

		
		m_CameraState = CAMERA_STATE::NORMAL;
		SetCursorPos(m_Center.x, m_Center.y);
	}

	
}

void CCameraMgr::Set_CenterPoint(void)
{
	m_hWindow = GetDesktopWindow();
	GetClientRect(m_hWindow, &m_ClientRect);


	m_Center = { (m_ClientRect.right - m_ClientRect.left) / 2, (m_ClientRect.bottom - m_ClientRect.top) / 2 };
	ClientToScreen(m_hWindow, &m_Center);

	SetCursorPos(m_Center.x, m_Center.y);
}

void CCameraMgr::FollowTargetUpdate(void)
{
	if (m_pTargetPos->fX < m_tCameraRect.left + 300)
		m_fScrollX -= m_pTargetPos->fX - (m_tCameraRect.left + 300);

	if (m_pTargetPos->fX > m_tCameraRect.right - 300)
		m_fScrollX -= m_pTargetPos->fX - (m_tCameraRect.right - 300);

	if (m_pTargetPos->fY < m_tCameraRect.top + 200)
		m_fScrollY -= m_pTargetPos->fY - (m_tCameraRect.top + 200);

	if (m_pTargetPos->fY > m_tCameraRect.bottom - 200)
		m_fScrollY -= m_pTargetPos->fY - (m_tCameraRect.bottom - 200);
}

void CCameraMgr::GoTargetUpdate(void)
{
	float fX = m_vGoTargetPos.fX - m_vCameraPos.fX;
	float fY = m_vGoTargetPos.fY - m_vCameraPos.fY;


	if (fabs(fX) < 2.0f)
	{
		m_fScrollX -= fX;
		m_bStopX = true;
	}

	if (fabs(fY) < 2.0f)
	{
		m_fScrollY -= fY;
		m_bStopY = true;
	}


	m_fScrollX -= fX * 0.1f;
	m_fScrollY -= fY * 0.1f;
}

void CCameraMgr::FollowTargetLateUpdate(void)
{
	if (m_pTarget->Is_Dead())
		m_CameraState = CAMERA_STATE::NORMAL;
}

void CCameraMgr::GoTargetLateUpdate(void)
{
	if (m_fScrollX <= -2400.0f)
		m_bStopX = true;

	if (m_fScrollY <= -400.0f)
		m_bStopY = true;

	if (m_fScrollX > 0.0f)
		m_bStopX = true;

	if (m_fScrollY > 0.0f)
		m_bStopY = true;

	if (m_bStopX && m_bStopY)
	{
		m_CameraState = CAMERA_STATE::NORMAL;
		m_bStopX = false;
		m_bStopY = false;
	}
}

void CCameraMgr::MouseUpdate(void)
{
	ScreenToClient(g_hWnd, &m_Mouse);
}

void CCameraMgr::Show_Cursor(void)
{
	if (m_bMouseScroll)
	{
		Set_CenterPoint();
		ShowCursor(false);
	}
	else
	{
		ShowCursor(true);
	}
}

void CCameraMgr::ShakeUpdate(void)
{
	m_fScrollX = m_fPrevScrollX + ((rand() % 3 - 1) * (rand() % 10 + 10));
	m_fScrollY = m_fPrevScrollY + ((rand() % 3 - 1) * (rand() % 10 + 10));
}

void CCameraMgr::ShakeLateUpdate(void)
{
	if (m_iShakeStart + m_iShakeDelay < GetTickCount())
	{
		m_fScrollX = m_fPrevScrollX;
		m_fScrollY = m_fPrevScrollY;

		m_CameraState = CAMERA_STATE::NORMAL;
	}
}


