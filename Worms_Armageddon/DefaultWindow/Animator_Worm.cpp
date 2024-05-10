#include "stdafx.h"
#include "Animator_Worm.h"
#include "BmpMgr.h"
#include "Sprite_Worm_Idle.h"
#include "Sprite_Worm_Walk.h"
#include "Obj_Worm.h"
#include "Sprite_DrawWeapon.h"
#include "Image_WeponIdle.h"
#include "Sprite_Worm_Jump.h"
#include "Sprite_Worm_Slide.h"
#include "Image_Worm_Flying.h"
#include "Sprite_Worm_Dead.h"
#include "Sprite_Worm_Winner.h"
#include "Sprite_Worm_Swim.h"


CAnimator_Worm::CAnimator_Worm()
{
}


CAnimator_Worm::~CAnimator_Worm()
{
	Release();
}

void CAnimator_Worm::Initialize(CObj* _pObj)
{
	m_pOwner = _pObj;
	m_CurrState = static_cast<CObj_Worm*>(m_pOwner)->Get_State();

	Add_Sprite();

	Add_Bmp();

	Set_Idle();
}


void CAnimator_Worm::Update(void)
{
	if (m_CurrAniState == ANIMATOR_STATE::BMP)
	{
		m_pCurrBmp->Update();
	}
	else if (m_CurrAniState == ANIMATOR_STATE::SPRITE)
	{
		m_pCurrSprite->Update();
	}
}

void CAnimator_Worm::LateUpdate(void)
{
	if (m_CurrState != static_cast<CObj_Worm*>(m_pOwner)->Get_State())
	{
		m_CurrState = static_cast<CObj_Worm*>(m_pOwner)->Get_State();
		switch (m_CurrState)
		{
		case WORM_STATE::IDLE:
			Set_Idle();
			break;
		case WORM_STATE::WALK:
			Set_Walk();
			break;
		case WORM_STATE::WEAPON:
			Set_DrawWeapon();
			break;
		case WORM_STATE::JUMP:
			Set_Jump();
			break;
		case WORM_STATE::FlYING:
			Set_Flying();
			break;
		case WORM_STATE::SLIDE:
			Set_Slide();
			break;
		case WORM_STATE::DEAD:
			Set_Dead();
			break;
		case WORM_STATE::WINNER:
			Set_Winner();
			break;
		case WORM_STATE::SWIM:
			Set_Swim();
			break;
		case WORM_STATE::NOTTURN:
			Set_Idle();
			break;

		}
	}

	if (m_CurrAniState == ANIMATOR_STATE::BMP)
	{
		m_pCurrBmp->LateUpdate();
	}
	else if (m_CurrAniState == ANIMATOR_STATE::SPRITE)
	{
		m_pCurrSprite->LateUpdate();

		if (m_CurrState == WORM_STATE::WEAPON && m_pCurrSprite->Get_SpriteState() == SPRITE_STATE::END && static_cast<CSprite_DrawWeapon*>(m_pCurrSprite)->Is_Idle())
		{
			Set_WeaponIdle();
		}
	}
}

void CAnimator_Worm::Render(HDC _hDC)
{
	if (m_CurrAniState == ANIMATOR_STATE::BMP)
	{
		m_pCurrBmp->Render(_hDC);
	}
	else if (m_CurrAniState == ANIMATOR_STATE::SPRITE)
	{
		m_pCurrSprite->Render(_hDC);
	}
}

void CAnimator_Worm::Release(void)
{
	for (auto& iter : m_SpriteList)
	{
		Safe_Delete(iter.second);
	}
	m_SpriteList.clear();

	for (auto& iter : m_BmpList)
	{
		Safe_Delete(iter.second);
	}
	m_BmpList.clear();
}



void CAnimator_Worm::Set_Idle(void)
{
	m_CurrAniState = ANIMATOR_STATE::SPRITE;
	if(m_pCurrSprite)
		m_pCurrSprite->SpriteReset();
	m_pCurrSprite = m_SpriteList[L"Worm_Idle"];
}

void CAnimator_Worm::Set_Walk(void)
{
	m_CurrAniState = ANIMATOR_STATE::SPRITE;
	m_pCurrSprite->SpriteReset();
	m_pCurrSprite = m_SpriteList[L"Worm_Walk"];
	static_cast<CSprite_Worm_Walk*>(m_pCurrSprite)->Set_Pos();
	m_pCurrSprite->SpriteReset();
}

void CAnimator_Worm::Set_DrawWeapon(void)
{
	m_CurrAniState = ANIMATOR_STATE::SPRITE;
	m_pCurrSprite->SpriteReset();
	m_pCurrSprite = m_SpriteList[L"Worm_DrawWeapon"];
	static_cast<CSprite_DrawWeapon*>(m_pCurrSprite)->Set_Weapon();
}

void CAnimator_Worm::Set_WeaponIdle(void)
{
	m_CurrAniState = ANIMATOR_STATE::BMP;
	m_pCurrBmp = m_BmpList[L"Worm_WeaponIdle"];
	static_cast<CImage_WeaponIdle*>(m_pCurrBmp)->Set_Weapon();
}

void CAnimator_Worm::Set_Jump(void)
{
	m_CurrAniState = ANIMATOR_STATE::SPRITE;
	m_pCurrSprite->SpriteReset();
	m_pCurrSprite = m_SpriteList[L"Worm_Jump"];
	m_pCurrSprite->SpriteReset();
}

void CAnimator_Worm::Set_Flying(void)
{
	m_CurrAniState = ANIMATOR_STATE::BMP;
	m_pCurrBmp = m_BmpList[L"Worm_Flying"];
}

void CAnimator_Worm::Set_Slide(void)
{
	m_CurrAniState = ANIMATOR_STATE::SPRITE;
	m_pCurrSprite->SpriteReset();
	m_pCurrSprite = m_SpriteList[L"Worm_Slide"];
	static_cast<CSprite_Worm_Slide*>(m_pCurrSprite)->Reset_Slide();
}

void CAnimator_Worm::Set_Dead(void)
{
	m_CurrAniState = ANIMATOR_STATE::SPRITE;
	m_pCurrSprite->SpriteReset();
	m_pCurrSprite = m_SpriteList[L"Worm_Dead"];
}

void CAnimator_Worm::Set_Winner(void)
{
	m_CurrAniState = ANIMATOR_STATE::SPRITE;
	m_pCurrSprite->SpriteReset();
	m_pCurrSprite = m_SpriteList[L"Worm_Winner"];
}

void CAnimator_Worm::Set_Swim(void)
{
	m_CurrAniState = ANIMATOR_STATE::SPRITE;
	m_pCurrSprite->SpriteReset();
	m_pCurrSprite = m_SpriteList[L"Worm_Swim"];
	m_pCurrSprite->SpriteReset();
}



void CAnimator_Worm::Add_Sprite(void)
{
	//스프라이트 추가
	CSprite* pNewSprite = nullptr;
	pNewSprite = new CSprite_Worm_Idle;
	m_SpriteList.emplace(L"Worm_Idle", pNewSprite);

	pNewSprite = nullptr;
	pNewSprite = new CSprite_Worm_Walk;
	m_SpriteList.emplace(L"Worm_Walk", pNewSprite);

	pNewSprite = nullptr;
	pNewSprite = new CSprite_DrawWeapon;
	m_SpriteList.emplace(L"Worm_DrawWeapon", pNewSprite);


	pNewSprite = nullptr;
	pNewSprite = new CSprite_Worm_Jump;
	m_SpriteList.emplace(L"Worm_Jump", pNewSprite);

	pNewSprite = nullptr;
	pNewSprite = new CSprite_Worm_Slide;
	m_SpriteList.emplace(L"Worm_Slide", pNewSprite);

	pNewSprite = nullptr;
	pNewSprite = new CSprite_Worm_Dead;
	m_SpriteList.emplace(L"Worm_Dead", pNewSprite);

	pNewSprite = nullptr;
	pNewSprite = new CSprite_Worm_Winner;
	m_SpriteList.emplace(L"Worm_Winner", pNewSprite);

	pNewSprite = nullptr;
	pNewSprite = new CSprite_Worm_Swim;
	m_SpriteList.emplace(L"Worm_Swim", pNewSprite);
	//


	for (auto& iter : m_SpriteList)
	{
		iter.second->Initialize(m_pOwner);
	}
}

void CAnimator_Worm::Add_Bmp(void)
{
	//이미지 추가
	CMyImage* pNewImage = nullptr;
	pNewImage = new CImage_WeaponIdle;
	m_BmpList.emplace(L"Worm_WeaponIdle", pNewImage);

	pNewImage = nullptr;
	pNewImage = new CImage_Worm_Flying;
	m_BmpList.emplace(L"Worm_Flying", pNewImage);
	//


	for (auto& iter : m_BmpList)
	{
		iter.second->Initialize(m_pOwner);
	}
}

void CAnimator_Worm::Reset_WeaponIdle(void)
{
	m_CurrAniState = ANIMATOR_STATE::BMP;
	m_pCurrBmp = m_BmpList[L"Worm_WeaponIdle"];
	static_cast<CImage_WeaponIdle*>(m_pCurrBmp)->Set_Weapon();
}
