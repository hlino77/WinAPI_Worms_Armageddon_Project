#include "stdafx.h"
#include "Sprite_TeleWork.h"
#include "Obj_Worm.h"

CSprite_TeleWork::CSprite_TeleWork()
{
}


CSprite_TeleWork::~CSprite_TeleWork()
{

}

void CSprite_TeleWork::Initialize(CObj * _pObj)
{
	m_pOwner = _pObj;

	Set_SpriteAngle();


	m_iCurr = 0;
	m_iMax = 48;

	m_SpriteTime = GetTickCount();
	m_DelayTime = 40;
	m_SpriteDelay = 0;

	Set_Size();

	m_SpriteState = SPRITE_STATE::START;

	m_bReverse = false;
}

void CSprite_TeleWork::Update(void)
{
	Set_SpriteAngle();
	switch (m_SpriteState)
	{
	case SPRITE_STATE::START:
		if (m_SpriteTime + m_DelayTime < GetTickCount())
		{
			if (!m_bReverse)
			{
				++m_iCurr;
				if (m_iCurr >= m_iMax)
				{
					m_iCurr = m_iMax - 1;
					m_SpriteState = SPRITE_STATE::END;
				}
			}
			else
			{
				--m_iCurr;
				if (m_iCurr <= 0)
				{
					m_iCurr = 0;
					m_SpriteState = SPRITE_STATE::END;
				}
			}
				
			
		}
		break;
	}
}

void CSprite_TeleWork::LateUpdate(void)
{
}

void CSprite_TeleWork::Render(HDC _hDC)
{
	float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
	float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();

	GdiTransparentBlt(_hDC,
		(int)(m_pOwner->Get_Pos().fX - m_fCX * 0.5f) + fScrollX, // 복사받을 x위치의 좌표
		(int)(m_pOwner->Get_Pos().fY - m_fCY * 0.5f) + fScrollY, // 복사 받을 y위치의 좌표)
		(int)m_fCX, // 복사 받을 가로 길이
		(int)m_fCY, // 복사 받을 세로 길이
		m_hCurrDC,	// 복사할 비트맵 이미지 dc
		0,		// 비트맵을 출력할 시작 x좌표
		(int)(m_iCurr * m_fCY),		// 비트맵을 출력할 시작 y좌표
		(int)m_fCX, // 복사할 비트맵의 가로 사이즈
		(int)m_fCY,// 복사할 비트맵의 세로 사이즈
		RGB(192, 192, 128)); //제거하고자 하는 색상

}

void CSprite_TeleWork::Set_Size(void)
{
	m_fCX = 60.0f;
	m_fCY = 60.0f;
}

void CSprite_TeleWork::Set_SpriteAngle(void)
{
	float fLeftAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_LeftAngle();
	float fRightAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_RightAngle();
	m_CurrDir = m_pOwner->Get_ObjDir();

	if (m_CurrDir == OBJ_DIR::LEFT)
	{
		if (fLeftAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"TeleWorkLeftDown");
		}
		else if (fLeftAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"TeleWorkLeftUp");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"TeleWorkLeft");
		}

	}
	else if (m_CurrDir == OBJ_DIR::RIGHT)
	{
		if (fRightAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"TeleWorkRightUp");
		}
		else if (fRightAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"TeleWorkRightDown");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"TeleWorkRight");
		}
	}

}
