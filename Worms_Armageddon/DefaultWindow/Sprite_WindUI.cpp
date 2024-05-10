#include "stdafx.h"
#include "Sprite_WindUI.h"
#include "GameMgr.h"

CSprite_WindUI::CSprite_WindUI()
	:m_iSpeed(0)
{
}


CSprite_WindUI::~CSprite_WindUI()
{
}

void CSprite_WindUI::Initialize(CObj * _pObj)
{
	m_pOwner = _pObj;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Map/WindBorder2.bmp", L"WindBorder");
	m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"WindBorder");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Map/WindLeft.bmp", L"WindLeft");
	m_hLeftDC = CBmpMgr::Get_Instance()->Find_Image(L"WindLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Map/WindRight.bmp", L"WindRight");
	m_hRightDC = CBmpMgr::Get_Instance()->Find_Image(L"WindRight");


	m_iCurr = 0;
	m_iMax = 8;

	m_SpriteTime = GetTickCount();
	m_DelayTime = 10;
	m_SpriteDelay = 0;

	m_SpriteState = SPRITE_STATE::END;

	m_PrevSpriteTime = GetTickCount();

	Change_WindInfo();
	Set_Size();
}

void CSprite_WindUI::Update(void)
{
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


	if (m_fLength != m_fCX)
	{
		if (m_fLength > m_fCX)
			m_fCX += 1.0f;
		else if (m_fLength < m_fCX)
			m_fCX -= 1.0f;
	}
}

void CSprite_WindUI::LateUpdate(void)
{
	if (m_WindDir != CGameMgr::Get_Inst()->Get_WindDir())
		Change_WindInfo();

	if (m_iSpeed != CGameMgr::Get_Inst()->Get_WindSpeed())
		Set_Size();

	if (m_SpriteState == SPRITE_STATE::END)
	{
		m_SpriteState = SPRITE_STATE::START;
		m_SpriteTime = GetTickCount();
	}
}

void CSprite_WindUI::Render(HDC _hDC)
{
	GdiTransparentBlt(_hDC,
		1410, // 복사받을 x위치의 좌표
		850, // 복사 받을 y위치의 좌표)
		180, // 복사 받을 가로 길이
		19, // 복사 받을 세로 길이
		m_hCurrDC,	// 복사할 비트맵 이미지 dc
		0,		// 비트맵을 출력할 시작 x좌표
		0,		// 비트맵을 출력할 시작 y좌표
		180, // 복사할 비트맵의 가로 사이즈
		19,// 복사할 비트맵의 세로 사이즈
		RGB(128, 128, 192)); //제거하고자 하는 색상


	switch (m_WindDir)
	{
	case WIND_DIR::LEFT:
		Left_Render(_hDC);
		break;
	case WIND_DIR::RIGHT:
		Right_Render(_hDC);
		break;
	}
}

void CSprite_WindUI::Set_Size(void)
{
	m_iSpeed = CGameMgr::Get_Inst()->Get_WindSpeed();
	m_fLength = 28.0f * m_iSpeed;
	m_fCY = 13.0f;
}

void CSprite_WindUI::Left_Render(HDC _hDC)
{
	float fX = (float)1498 - m_fCX;
	float fY = 853.0f;

	GdiTransparentBlt(_hDC,
		fX, // 복사받을 x위치의 좌표
		fY, // 복사 받을 y위치의 좌표)
		m_fCX, // 복사 받을 가로 길이
		13, // 복사 받을 세로 길이
		m_hLeftDC,	// 복사할 비트맵 이미지 dc
		m_iCurr,		// 비트맵을 출력할 시작 x좌표
		0,		// 비트맵을 출력할 시작 y좌표
		m_fCX, // 복사할 비트맵의 가로 사이즈
		13,// 복사할 비트맵의 세로 사이즈
		RGB(0, 0, 0)); //제거하고자 하는 색상
}

void CSprite_WindUI::Right_Render(HDC _hDC)
{
	float fX = (float)1502;
	float fY = 853.0f;

	GdiTransparentBlt(_hDC,
		fX, // 복사받을 x위치의 좌표
		fY, // 복사 받을 y위치의 좌표)
		m_fCX, // 복사 받을 가로 길이
		13, // 복사 받을 세로 길이
		m_hRightDC,	// 복사할 비트맵 이미지 dc
		8 - m_iCurr,		// 비트맵을 출력할 시작 x좌표
		0,		// 비트맵을 출력할 시작 y좌표
		m_fCX, // 복사할 비트맵의 가로 사이즈
		13,// 복사할 비트맵의 세로 사이즈
		RGB(0, 0, 0)); //제거하고자 하는 색상
}

void CSprite_WindUI::Change_WindInfo(void)
{
	m_WindDir = CGameMgr::Get_Inst()->Get_WindDir();
	m_iSpeed = CGameMgr::Get_Inst()->Get_WindSpeed();

	m_fCX = 0.0f;
	Set_Size();
}
