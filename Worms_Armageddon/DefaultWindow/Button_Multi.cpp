#include "stdafx.h"
#include "Button_Multi.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

CButton_Multi::CButton_Multi()
{
}


CButton_Multi::~CButton_Multi()
{
	Release();
}

void CButton_Multi::Initialize(POINT * _pMouse)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/MainMenu/Multi.bmp", L"Multi");
	m_Button = CBmpMgr::Get_Instance()->Find_Image(L"Multi");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/MainMenu/Border.bmp", L"Border");
	m_Border = CBmpMgr::Get_Instance()->Find_Image(L"Border");

	m_vPos.fX = 900.0;
	m_vPos.fY = 300.0f;
	m_vPos.fCX = 240.0f;
	m_vPos.fCY = 150.0f;

	m_pMouse = _pMouse;
}

void CButton_Multi::Update(void)
{
	MouseUpdate();


	if (m_bMouseIn && CKeyMgr::Get_Inst()->Key_Down(VK_LBUTTON))
	{
		CSceneMgr::Get_Inst()->Set_Next_Scene(SCENE_TYPE::GAME);
		CSoundMgr::Get_Instance()->StopSound(CHANNELID::GAMESOUND);
		CSoundMgr::Get_Instance()->PlaySoundW(L"increaseiconnumber.wav", CHANNELID::GAMESOUND, 0.5f);
	}
}

void CButton_Multi::LateUpdate(void)
{
}

void CButton_Multi::Release(void)
{
}

void CButton_Multi::Render(HDC _hDC)
{
	BitBlt(_hDC,
		m_vPos.fX, // 복사받을 x위치의 좌표
		m_vPos.fY, // 복사 받을 y위치의 좌표)
		m_vPos.fCX, // 복사 받을 가로 길이
		m_vPos.fCY, // 복사 받을 세로 길이
		m_Button,	// 복사할 비트맵 이미지 dc
		0,		// 비트맵을 출력할 시작 x좌표
		0,		// 비트맵을 출력할 시작 y좌표
		SRCCOPY); //제거하고자 하는 색상

	if (m_bMouseIn)
	{
		GdiTransparentBlt(_hDC,
			m_vPos.fX, // 복사받을 x위치의 좌표
			m_vPos.fY, // 복사 받을 y위치의 좌표)
			m_vPos.fCX, // 복사 받을 가로 길이
			m_vPos.fCY, // 복사 받을 세로 길이
			m_Border,	// 복사할 비트맵 이미지 dc
			0,		// 비트맵을 출력할 시작 x좌표
			0,		// 비트맵을 출력할 시작 y좌표
			m_vPos.fCX, // 복사할 비트맵의 가로 사이즈
			m_vPos.fCY,// 복사할 비트맵의 세로 사이즈
			RGB(0, 0, 0)); //제거하고자 하는 색상
	}
}
