#include "stdafx.h"
#include "Sprite_Worm_Dead.h"


CSprite_Worm_Dead::CSprite_Worm_Dead()
{
}


CSprite_Worm_Dead::~CSprite_Worm_Dead()
{
}

void CSprite_Worm_Dead::Initialize(CObj * _pObj)
{
	m_pOwner = _pObj;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Die.bmp", L"Die");

	m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Die");


	m_iCurr = 0;
	m_iMax = 60;

	m_fCX = 60.0f;
	m_fCY = 60.0f;

	m_DelayTime = 30;
	m_SpriteDelay = 0;

	m_SpriteState = SPRITE_STATE::START;

	m_PrevSpriteTime = GetTickCount();
}

void CSprite_Worm_Dead::Update(void)
{
	if (m_SpriteState == SPRITE_STATE::START)
	{
		if (m_SpriteTime + m_DelayTime < GetTickCount())
		{
			++m_iCurr;
			if (m_iCurr >= m_iMax)
			{
				m_SpriteState = SPRITE_STATE::END;
			}
			m_SpriteTime = GetTickCount();
		}
	}
}

void CSprite_Worm_Dead::LateUpdate(void)
{
	
}

void CSprite_Worm_Dead::Render(HDC _hDC)
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

void CSprite_Worm_Dead::Set_Size(void)
{
}
