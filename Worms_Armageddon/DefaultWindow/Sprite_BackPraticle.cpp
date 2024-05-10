#include "stdafx.h"
#include "Sprite_BackPraticle.h"


CSprite_BackPraticle::CSprite_BackPraticle()
{
}


CSprite_BackPraticle::~CSprite_BackPraticle()
{
}

void CSprite_BackPraticle::Initialize(CObj * _pObj)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Map/Star.bmp", L"BackParticle");
	m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"BackParticle");

	m_pOwner = _pObj;
	Set_Size();

	m_iCurr = 0;
	m_iMax = 128;

	m_SpriteTime = GetTickCount();
	m_DelayTime = 0;
	m_SpriteDelay = 100;

	m_SpriteState = SPRITE_STATE::END;

	m_PrevSpriteTime = GetTickCount();
}

void CSprite_BackPraticle::Update(void)
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

void CSprite_BackPraticle::LateUpdate(void)
{

}

void CSprite_BackPraticle::Render(HDC _hDC)
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
		RGB(0, 0, 0)); //�����ϰ��� �ϴ� ����
}

void CSprite_BackPraticle::Set_Size(void)
{
	m_fCX = m_pOwner->Get_Pos().fCX;
	m_fCY = m_pOwner->Get_Pos().fCY;
}
