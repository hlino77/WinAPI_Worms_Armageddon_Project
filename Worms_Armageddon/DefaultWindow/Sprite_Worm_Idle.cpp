#include "stdafx.h"
#include "Sprite_Worm_Idle.h"
#include "BmpMgr.h"
#include "TimeMgr.h"
#include "Obj_Worm.h"


CSprite_Worm_Idle::CSprite_Worm_Idle()
{
}


CSprite_Worm_Idle::~CSprite_Worm_Idle()
{
}

void CSprite_Worm_Idle::Initialize(CObj * _pObj)
{
	m_pOwner = _pObj;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Left_Idle.bmp", L"Left_Idle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Right_Idle.bmp", L"Right_Idle");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Left_Up_Idle.bmp", L"Left_Up_Idle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Right_Up_Idle.bmp", L"Right_Up_Idle");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Left_Down_Idle.bmp", L"Left_Down_Idle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Right_Down_Idle.bmp", L"Right_Down_Idle");

	m_CurrDir = m_pOwner->Get_ObjDir();
	Change_Dir();

	m_iCurr = 0;
	m_iMax = 20;

	m_fCX = 60.0f;
	m_fCY = 60.0f;

	m_SpriteTime = GetTickCount();
	m_DelayTime = 20;
	m_SpriteDelay = 100;
	
	m_SpriteState = SPRITE_STATE::END;

	m_PrevSpriteTime = GetTickCount();
}

void CSprite_Worm_Idle::Update(void)
{
	if (m_SpriteState == SPRITE_STATE::START || m_SpriteState == SPRITE_STATE::REVERSE)
	{
		if (m_SpriteTime + m_DelayTime < GetTickCount())
		{
			if (m_SpriteState == SPRITE_STATE::START)
				++m_iCurr;
			else if (m_SpriteState == SPRITE_STATE::REVERSE)
				--m_iCurr;


			if (m_iCurr >= m_iMax && m_SpriteState == SPRITE_STATE::START)
			{
				m_SpriteState = SPRITE_STATE::REVERSE;
				m_iCurr = m_iMax - 1;
			}
			
			if (m_iCurr <= 0 && m_SpriteState == SPRITE_STATE::REVERSE)
			{
				m_SpriteState = SPRITE_STATE::END;
				m_PrevSpriteTime = GetTickCount();
			}

			m_SpriteTime = GetTickCount();
		}
	}
	else if (m_SpriteState == SPRITE_STATE::END)
	{
		if (m_PrevSpriteTime + m_SpriteDelay <= GetTickCount())
		{
			m_SpriteState = SPRITE_STATE::START;
		}
	}
	
}

void CSprite_Worm_Idle::LateUpdate(void)
{
	if (m_CurrDir != m_pOwner->Get_ObjDir())
	{
		Change_Dir();
	}

	Set_Angle();

}

void CSprite_Worm_Idle::Render(HDC _hDC)
{
	Idle_Render(_hDC);
}

void CSprite_Worm_Idle::Idle_Render(HDC _hDC)
{
	float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
	float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();



	GdiTransparentBlt(_hDC,
		(int)(m_pOwner->Get_Pos().fX - m_fCX * 0.5f) + fScrollX, // ������� x��ġ�� ��ǥ
		(int)(m_pOwner->Get_Pos().fY - m_fCY * 0.5f) + fScrollY, // ���� ���� y��ġ�� ��ǥ)
		(int)m_fCX, // ���� ���� ���� ����
		(int)m_fCY, // ���� ���� ���� ����
		m_hCurrDC,	// ������ ��Ʈ�� �̹��� dc
		0,		// ��Ʈ���� ����� ���� x��ǥ
		(int)(m_iCurr * m_fCY),		// ��Ʈ���� ����� ���� y��ǥ
		(int)m_fCX, // ������ ��Ʈ���� ���� ������
		(int)m_fCY,// ������ ��Ʈ���� ���� ������
		(RGB(128, 128, 192))); //�����ϰ��� �ϴ� ����

	
}

void CSprite_Worm_Idle::Change_Dir(void)
{
	switch (m_pOwner->Get_ObjDir())
	{
	case OBJ_DIR::LEFT:
		m_CurrDir = m_pOwner->Get_ObjDir();
		break;
	case OBJ_DIR::RIGHT:
		m_CurrDir = m_pOwner->Get_ObjDir();
		break;
	}
}

void CSprite_Worm_Idle::Set_Angle(void)
{
	float fLeftAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_LeftAngle();
	float fRightAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_RightAngle();


	if (m_CurrDir == OBJ_DIR::LEFT)
	{
		if (fLeftAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Left_Down_Idle");
		}
		else if (fLeftAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Left_Up_Idle");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Left_Idle");
		}

	}
	else if (m_CurrDir == OBJ_DIR::RIGHT)
	{
		if (fRightAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Right_Up_Idle");
		}
		else if (fRightAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Right_Down_Idle");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Right_Idle");
		}
	}

	
}

