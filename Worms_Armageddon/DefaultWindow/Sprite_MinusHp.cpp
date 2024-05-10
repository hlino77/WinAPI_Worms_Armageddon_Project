#include "stdafx.h"
#include "Sprite_MinusHp.h"
#include "Image_HpBox.h"
#include "Image_Font.h"

CSprite_MinusHp::CSprite_MinusHp()
	:m_iStartTime(0), m_iDelay(500)
{
}


CSprite_MinusHp::~CSprite_MinusHp()
{
	Release();
}

void CSprite_MinusHp::Initialize(CObj * _pObj)
{
	m_pOwner = _pObj;





	m_SpriteState = SPRITE_STATE::END;


	m_fSpeedY = 1.0f;

	m_DelayTime = 0;

	m_pHpBox = new CImage_HpBox;
	m_pHpBox->Initialize(nullptr);
	m_pFont = new CImage_Font;
	m_pFont->Initialize(nullptr);
}

void CSprite_MinusHp::Update(void)
{
	if (m_iStartTime + m_iDelay < GetTickCount())
	{
		m_SpriteState = SPRITE_STATE::END;
	}
	else
	{
		m_vPos.fY -= m_fSpeedY;
	}
}

void CSprite_MinusHp::LateUpdate(void)
{

}

void CSprite_MinusHp::Render(HDC _hDC)
{
	Render_Hp(_hDC);
}

void CSprite_MinusHp::Set_Size(void)
{

}

void CSprite_MinusHp::Release(void)
{
	Safe_Delete(m_pHpBox);
	Safe_Delete(m_pFont);
}

void CSprite_MinusHp::Reset_MinusHp(CMyVector2 _pPos, int _iNum, int _iTeamNum)
{
	m_iStartTime = GetTickCount();

	m_vPos.fX = _pPos.fX;
	m_vPos.fY = _pPos.fY - 30.0f;


	m_SpriteState = SPRITE_STATE::START;

	m_iHp = _iNum;
	m_iTeamNum = _iTeamNum;
}

void CSprite_MinusHp::Render_Hp(HDC _hDC)
{
	int iSize = 3;
	int iFirst = m_iHp / 100;
	int iSecond = (m_iHp % 100) / 10;
	int iThird = m_iHp % 10;

	if (iFirst == 0)
		--iSize;


	m_vPos.fCX = iSize * 10.0f + 6.0f;

	static_cast<CImage_HpBox*>(m_pHpBox)->Size_Render(_hDC, m_vPos, iSize);


	for (int i = 0; iSize > i; ++i)
	{
		CMyVector2 vPos = { (m_vPos.fX + m_vPos.fCX * 0.5f) - 8.0f - (10.0f * i),m_vPos.fY - 1.0f };

		if (i == 0)
			static_cast<CImage_Font*>(m_pFont)->Render_Num(_hDC, iThird, m_iTeamNum, vPos);
		if (i == 1)
			static_cast<CImage_Font*>(m_pFont)->Render_Num(_hDC, iSecond, m_iTeamNum, vPos);
		if (i == 2)
			static_cast<CImage_Font*>(m_pFont)->Render_Num(_hDC, iFirst, m_iTeamNum, vPos);
	}
}
