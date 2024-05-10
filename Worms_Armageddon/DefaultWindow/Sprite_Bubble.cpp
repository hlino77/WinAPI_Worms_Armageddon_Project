#include "stdafx.h"
#include "Sprite_Bubble.h"


CSprite_Bubble::CSprite_Bubble()
{
}


CSprite_Bubble::~CSprite_Bubble()
{
}

void CSprite_Bubble::Initialize(CObj * _pObj)
{
	m_pOwner = _pObj;





	m_SpriteState = SPRITE_STATE::END;

	m_PrevSpriteTime = GetTickCount();
	m_SpriteTime = GetTickCount();
}

void CSprite_Bubble::Update(void)
{
	m_fY -= 1.0f;
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

void CSprite_Bubble::LateUpdate(void)
{
}

void CSprite_Bubble::Render(HDC _hDC)
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
		RGB(0, 0, 0)); //제거하고자 하는 색상
}

void CSprite_Bubble::Set_Size(void)
{
}

void CSprite_Bubble::Random_Bubble(CMyVector2 _vPos)
{
	int iTemp = rand() % 4;

	switch (iTemp)
	{
	case 0:
		Set_Bubble(BUBBLE_TYPE::BUBBLE1, _vPos);
		break;
	case 1:
		Set_Bubble(BUBBLE_TYPE::BUBBLE2, _vPos);
		break;
	case 2:
		Set_Bubble(BUBBLE_TYPE::BUBBLE3, _vPos);
		break;
	case 3:
		Set_Bubble(BUBBLE_TYPE::BUBBLE4, _vPos);
		break;
	}
}

void CSprite_Bubble::Set_Bubble(BUBBLE_TYPE _BubbleType, CMyVector2 _vPos)
{
	switch (_BubbleType)
	{
	case BUBBLE_TYPE::BUBBLE1:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Bubble1");
		m_iCurr = 0;
		m_iMax = 16;
		m_DelayTime = 30;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 6.0f;
		m_fCY = 16.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	case BUBBLE_TYPE::BUBBLE2:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Bubble2");
		m_iCurr = 0;
		m_iMax = 16;
		m_DelayTime = 30;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 6.0f;
		m_fCY = 6.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	case BUBBLE_TYPE::BUBBLE3:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Bubble3");
		m_iCurr = 0;
		m_iMax = 16;
		m_DelayTime = 30;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 10.0f;
		m_fCY = 8.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	case BUBBLE_TYPE::BUBBLE4:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Bubble4");
		m_iCurr = 0;
		m_iMax = 16;
		m_DelayTime = 30;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 10.0f;
		m_fCY = 10.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	}
}
