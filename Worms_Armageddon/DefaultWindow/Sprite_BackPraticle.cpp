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
		int(m_pOwner->Get_Pos().fX - m_fCX * 0.5f) + fScrollX, // 복사받을 x위치의 좌표
		(m_pOwner->Get_Pos().fY - m_fCY * 0.5f) + fScrollY, // 복사 받을 y위치의 좌표)
		m_fCX, // 복사 받을 가로 길이
		m_fCY, // 복사 받을 세로 길이
		m_hCurrDC,	// 복사할 비트맵 이미지 dc
		0,		// 비트맵을 출력할 시작 x좌표
		m_iCurr * m_fCY,		// 비트맵을 출력할 시작 y좌표
		(int)m_fCX, // 복사할 비트맵의 가로 사이즈
		(int)m_fCY,// 복사할 비트맵의 세로 사이즈
		RGB(0, 0, 0)); //제거하고자 하는 색상
}

void CSprite_BackPraticle::Set_Size(void)
{
	m_fCX = m_pOwner->Get_Pos().fCX;
	m_fCY = m_pOwner->Get_Pos().fCY;
}
