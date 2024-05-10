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
		(int)(m_pOwner->Get_Pos().fX - m_fCX * 0.5f) + fScrollX, // ������� x��ġ�� ��ǥ
		(int)(m_pOwner->Get_Pos().fY - m_fCY * 0.5f) + fScrollY, // ���� ���� y��ġ�� ��ǥ)
		(int)m_fCX, // ���� ���� ���� ����
		(int)m_fCY, // ���� ���� ���� ����
		m_hCurrDC,	// ������ ��Ʈ�� �̹��� dc
		0,		// ��Ʈ���� ����� ���� x��ǥ
		(int)(m_iCurr * m_fCY),		// ��Ʈ���� ����� ���� y��ǥ
		(int)m_fCX, // ������ ��Ʈ���� ���� ������
		(int)m_fCY,// ������ ��Ʈ���� ���� ������
		RGB(192, 192, 128)); //�����ϰ��� �ϴ� ����

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
