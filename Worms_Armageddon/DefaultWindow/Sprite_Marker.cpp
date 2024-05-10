#include "stdafx.h"
#include "Sprite_Marker.h"


CSprite_Marker::CSprite_Marker()
{
}


CSprite_Marker::~CSprite_Marker()
{
}

void CSprite_Marker::Initialize(CObj * _pObj)
{
	m_pOwner = _pObj;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Effect/Marker.bmp", L"Marker");
	m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Marker");


	m_iCurr = 0;
	m_iMax = 10;

	m_fCX = 32.0f;
	m_fCY = 32.0f;

	m_SpriteTime = GetTickCount();
	m_DelayTime = 20;
	m_SpriteDelay = 2000;

	m_SpriteState = SPRITE_STATE::END;

	m_PrevSpriteTime = GetTickCount();
}

void CSprite_Marker::Update(void)
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

void CSprite_Marker::LateUpdate(void)
{
}

void CSprite_Marker::Render(HDC _hDC)
{
	float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
	float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();



	GdiTransparentBlt(_hDC,
		(int)(m_vPos.fX - m_fCX * 0.5f) + fScrollX, // 복사받을 x위치의 좌표
		(int)(m_vPos.fY - m_fCY * 0.5f) + fScrollY, // 복사 받을 y위치의 좌표)
		(int)m_fCX, // 복사 받을 가로 길이
		(int)m_fCY, // 복사 받을 세로 길이
		m_hCurrDC,	// 복사할 비트맵 이미지 dc
		0,		// 비트맵을 출력할 시작 x좌표
		(int)(m_iCurr * m_fCY),		// 비트맵을 출력할 시작 y좌표
		(int)m_fCX, // 복사할 비트맵의 가로 사이즈
		(int)m_fCY,// 복사할 비트맵의 세로 사이즈
		(RGB(0, 0, 0))); //제거하고자 하는 색상
}

void CSprite_Marker::Set_Size(void)
{

}
