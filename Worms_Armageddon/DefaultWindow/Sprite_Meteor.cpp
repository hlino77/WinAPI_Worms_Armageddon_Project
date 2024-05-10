#include "stdafx.h"
#include "Sprite_Meteor.h"


CSprite_Meteor::CSprite_Meteor()
{
}


CSprite_Meteor::~CSprite_Meteor()
{
}

void CSprite_Meteor::Initialize(CObj * _pObj)
{
	m_pOwner = _pObj;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Meteor.bmp", L"Meteor");
	m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Meteor");


	m_iCurr = 0;
	m_iMax = 10;

	m_fCX = 50.0f;
	m_fCY = 50.0f;

	m_DelayTime = 20;

	m_SpriteDelay = 0;

	m_SpriteState = SPRITE_STATE::START;

	m_PrevSpriteTime = GetTickCount();
}

void CSprite_Meteor::Update(void)
{
	switch (m_SpriteState)
	{
	case SPRITE_STATE::START:
		if (m_SpriteTime + m_DelayTime < GetTickCount())
		{
			++m_iCurr;
			if (m_iCurr >= m_iMax)
			{
				m_iCurr = 0;
				m_SpriteState = SPRITE_STATE::END;
			}
			m_SpriteTime = GetTickCount();
		}
		break;
	case SPRITE_STATE::END:
		if (m_PrevSpriteTime + m_SpriteDelay <= GetTickCount())
		{
			m_SpriteState = SPRITE_STATE::START;
		}
		break;
	}
}

void CSprite_Meteor::LateUpdate(void)
{
}

void CSprite_Meteor::Render(HDC _hDC)
{
	float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
	float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();


	GdiTransparentBlt(_hDC,
		int(m_pOwner->Get_Pos().fX - m_fCX * 0.5f) + fScrollX, // ������� x��ġ�� ��ǥ
		(m_pOwner->Get_Pos().fY - m_fCY * 0.5f) + fScrollY, // ���� ���� y��ġ�� ��ǥ)
		m_fCX, // ���� ���� ���� ����
		m_fCY, // ���� ���� ���� ����
		m_hCurrDC,	// ������ ��Ʈ�� �̹��� dc
		0,		// ��Ʈ���� ����� ���� x��ǥ
		m_iCurr * m_fCY,		// ��Ʈ���� ����� ���� y��ǥ
		(int)m_fCX, // ������ ��Ʈ���� ���� ������
		(int)m_fCY,// ������ ��Ʈ���� ���� ������
		RGB(128, 128, 192)); //�����ϰ��� �ϴ� ����
}

void CSprite_Meteor::Set_Size(void)
{
}
