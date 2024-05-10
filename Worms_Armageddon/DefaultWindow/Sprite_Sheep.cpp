#include "stdafx.h"
#include "Sprite_Sheep.h"


CSprite_Sheep::CSprite_Sheep()
{
}


CSprite_Sheep::~CSprite_Sheep()
{
}

void CSprite_Sheep::Initialize(CObj * _pObj)
{
	m_pOwner = _pObj;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/SheepWalkLeft.bmp", L"SheepWalkLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/SheepWalkRight.bmp", L"SheepWalkRight");


	m_iCurr = 0;
	m_iMax = 8;

	m_fCX = 60.0f;
	m_fCY = 60.0f;

	m_DelayTime = 20;

	m_SpriteDelay = 0;

	m_SpriteState = SPRITE_STATE::START;

	m_PrevSpriteTime = GetTickCount();
}

void CSprite_Sheep::Update(void)
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

void CSprite_Sheep::LateUpdate(void)
{
}

void CSprite_Sheep::Render(HDC _hDC)
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
		RGB(192, 192, 128)); //�����ϰ��� �ϴ� ����
}

void CSprite_Sheep::Set_Size(void)
{
}

void CSprite_Sheep::Change_Dir(void)
{
	switch (m_pOwner->Get_ObjDir())
	{
	case OBJ_DIR::LEFT:
		m_iCurr = 0;
		m_SpriteState = SPRITE_STATE::START;
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"SheepWalkLeft");
		break;
	case OBJ_DIR::RIGHT:
		m_iCurr = 0;
		m_SpriteState = SPRITE_STATE::START;
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"SheepWalkRight");
		break;
	}
}
