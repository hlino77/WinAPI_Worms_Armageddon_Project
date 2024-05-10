#include "stdafx.h"
#include "Sprite_Star.h"


CSprite_Star::CSprite_Star()
{
}


CSprite_Star::~CSprite_Star()
{
}

void CSprite_Star::Initialize(CObj * _pObj)
{
	m_pOwner = _pObj;



	m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Star");

	m_SpriteState = SPRITE_STATE::END;

	m_PrevSpriteTime = GetTickCount();
	m_SpriteTime = GetTickCount();

	Make_Dir();
}

void CSprite_Star::Update(void)
{
	if (m_SpriteState == SPRITE_STATE::START)
	{
		m_fX += m_vDir.fX;
		m_fY += m_vDir.fY;
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

void CSprite_Star::LateUpdate(void)
{
}

void CSprite_Star::Render(HDC _hDC)
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
		RGB(192, 192, 128)); //제거하고자 하는 색상
}

void CSprite_Star::Set_Size(void)
{
}

void CSprite_Star::Set_Star(CMyVector2 _vPos)
{
	m_iCurr = rand() % 4;
	m_iMax = 10;
	m_DelayTime = 40;
	m_fX = _vPos.fX;
	m_fY = _vPos.fY;
	m_fCX = 60.0f;
	m_fCY = 60.0f;
	m_SpriteState = SPRITE_STATE::START;
}

void CSprite_Star::Make_Dir(void)
{
	float fAngle = rand() % 360;

	float fRadian = DEG2RAD(fAngle);


	m_vDir.fX = sinf(fRadian) * 1.0f;
	m_vDir.fY = cosf(fRadian) * 1.0f;
}
