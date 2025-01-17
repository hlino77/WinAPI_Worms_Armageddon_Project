#include "stdafx.h"
#include "Sprite_Effect_Circle.h"


CSprite_Effect_Circle::CSprite_Effect_Circle()
{
}


CSprite_Effect_Circle::~CSprite_Effect_Circle()
{
}

void CSprite_Effect_Circle::Initialize(CObj * _pObj)
{
	m_pOwner = _pObj;





	m_SpriteState = SPRITE_STATE::END;

	m_PrevSpriteTime = GetTickCount();
	m_SpriteTime = GetTickCount();
}

void CSprite_Effect_Circle::Update(void)
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

void CSprite_Effect_Circle::LateUpdate(void)
{
}

void CSprite_Effect_Circle::Render(HDC _hDC)
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
		RGB(128, 128, 192)); //제거하고자 하는 색상
}

void CSprite_Effect_Circle::Set_Size(void)
{

}


void CSprite_Effect_Circle::Set_Circle(CIRCLE_EFFECT_TYPE _CircleType, CMyVector2 _vPos)
{
	switch (_CircleType)
	{
	case CIRCLE_EFFECT_TYPE::CIRCLE25:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Circle25");
		m_iCurr = 0;
		m_iMax = 8;
		m_DelayTime = 10;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 50.0f;
		m_fCY = 50.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	case CIRCLE_EFFECT_TYPE::CIRCLE50:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Circle50");
		m_iCurr = 0;
		m_iMax = 8;
		m_DelayTime = 10;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 100.0f;
		m_fCY = 100.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	case CIRCLE_EFFECT_TYPE::CIRCLE75:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Circle75");
		m_iCurr = 0;
		m_iMax = 4;
		m_DelayTime = 20;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 150.0f;
		m_fCY = 150.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	case CIRCLE_EFFECT_TYPE::CIRCLE100:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Circle100");
		m_iCurr = 0;
		m_iMax = 4;
		m_DelayTime = 20;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 200.0f;
		m_fCY = 200.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	}
}
