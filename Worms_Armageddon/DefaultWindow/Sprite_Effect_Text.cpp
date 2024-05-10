#include "stdafx.h"
#include "Sprite_Effect_Text.h"


CSprite_Effect_Text::CSprite_Effect_Text()
{
}


CSprite_Effect_Text::~CSprite_Effect_Text()
{
}

void CSprite_Effect_Text::Initialize(CObj * _pObj)
{
	m_pOwner = _pObj;





	m_SpriteState = SPRITE_STATE::END;

	m_PrevSpriteTime = GetTickCount();
	m_SpriteTime = GetTickCount();
}

void CSprite_Effect_Text::Update(void)
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

void CSprite_Effect_Text::LateUpdate(void)
{
}

void CSprite_Effect_Text::Render(HDC _hDC)
{
	float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
	float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();


	GdiTransparentBlt(_hDC,
		int((m_fX - m_fCX * 0.5f) + fScrollX), // 복사받을 x위치의 좌표
		int((m_fY - m_fCY * 0.5f) + fScrollY), // 복사 받을 y위치의 좌표)
		m_fCX, // 복사 받을 가로 길이
		m_fCY, // 복사 받을 세로 길이
		m_hCurrDC,	// 복사할 비트맵 이미지 dc
		0,		// 비트맵을 출력할 시작 x좌표
		m_iCurr * m_fCY,		// 비트맵을 출력할 시작 y좌표
		(int)m_fCX, // 복사할 비트맵의 가로 사이즈
		(int)m_fCY,// 복사할 비트맵의 세로 사이즈
		RGB(128, 128, 192)); //제거하고자 하는 색상
}

void CSprite_Effect_Text::Set_Size(void)
{
}

void CSprite_Effect_Text::Random_Text(CMyVector2 _vPos)
{
	int iTemp = rand() % 4;

	switch (iTemp)
	{
	case 0:
		Set_Text(TEXT_EFFECT_TYPE::BIFF, _vPos);
		break;
	case 1:
		Set_Text(TEXT_EFFECT_TYPE::POOT, _vPos);
		break;
	case 2:
		Set_Text(TEXT_EFFECT_TYPE::POW, _vPos);
		break;
	case 3:
		Set_Text(TEXT_EFFECT_TYPE::FOOM, _vPos);
		break;
	}
}

void CSprite_Effect_Text::Set_Text(TEXT_EFFECT_TYPE _TextType, CMyVector2 _vPos)
{
	switch (_TextType)
	{
	case TEXT_EFFECT_TYPE::BIFF:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"TextBiff");
		m_iCurr = 0;
		m_iMax = 12;
		m_DelayTime = 15;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 60.0f;
		m_fCY = 60.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	case TEXT_EFFECT_TYPE::POOT:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"TextPoot");
		m_iCurr = 0;
		m_iMax = 18;
		m_DelayTime = 15;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 70.0f;
		m_fCY = 70.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	case TEXT_EFFECT_TYPE::POW:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"TextPow");
		m_iCurr = 0;
		m_iMax = 12;
		m_DelayTime = 15;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 60.0f;
		m_fCY = 60.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	case TEXT_EFFECT_TYPE::FOOM:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"TextFoom");
		m_iCurr = 0;
		m_iMax = 20;
		m_DelayTime = 15;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 100.0f;
		m_fCY = 100.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	}

	
}
