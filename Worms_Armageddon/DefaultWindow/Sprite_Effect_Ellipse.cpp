#include "stdafx.h"
#include "Sprite_Effect_Ellipse.h"


CSprite_Effect_Ellipse::CSprite_Effect_Ellipse()
{
}


CSprite_Effect_Ellipse::~CSprite_Effect_Ellipse()
{
}

void CSprite_Effect_Ellipse::Initialize(CObj * _pObj)
{
	m_pOwner = _pObj;





	m_SpriteState = SPRITE_STATE::END;

	m_PrevSpriteTime = GetTickCount();
	m_SpriteTime = GetTickCount();
}

void CSprite_Effect_Ellipse::Update(void)
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

void CSprite_Effect_Ellipse::LateUpdate(void)
{
}

void CSprite_Effect_Ellipse::Render(HDC _hDC)
{
	float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
	float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();


	GdiTransparentBlt(_hDC,
		int(m_fX - m_fCX * 0.5f) + fScrollX, // 복사받을 x위치의 좌표
		(m_fY - m_fCY * 0.5f) + fScrollY, // 복사 받을 y위치의 좌표)
		m_fCX, // 복사 받을 가로 길이
		m_fCY, // 복사 받을 세로 길이
		m_hCurrDC,	// 복사할 비트맵 이미지 dc
		0,		// 비트맵을 출력할 시작 x좌표
		m_iCurr * m_fCY,		// 비트맵을 출력할 시작 y좌표
		(int)m_fCX, // 복사할 비트맵의 가로 사이즈
		(int)m_fCY,// 복사할 비트맵의 세로 사이즈
		RGB(32, 32, 248)); //제거하고자 하는 색상
}

void CSprite_Effect_Ellipse::Set_Size(void)
{
}

void CSprite_Effect_Ellipse::Set_Ellipse(ELLIPSE_EFFECT_TYPE _EllipseType, CMyVector2 _vPos)
{
	switch (_EllipseType)
	{
	case ELLIPSE_EFFECT_TYPE::ELLIPSE25:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Ellipse25");
		m_iCurr = 0;
		m_iMax = 20;
		m_DelayTime = 10;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 74.0f;
		m_fCY = 74.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	case ELLIPSE_EFFECT_TYPE::ELLIPSE50:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Ellipse50");
		m_iCurr = 0;
		m_iMax = 20;
		m_DelayTime = 10;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 150.0f;
		m_fCY = 150.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	case ELLIPSE_EFFECT_TYPE::ELLIPSE75:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Ellipse75");
		m_iCurr = 0;
		m_iMax = 10;
		m_DelayTime = 20;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 224.0f;
		m_fCY = 224.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	case ELLIPSE_EFFECT_TYPE::ELLIPSE100:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Ellipse100");
		m_iCurr = 0;
		m_iMax = 10;
		m_DelayTime = 20;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 300.0f;
		m_fCY = 300.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	}
}
