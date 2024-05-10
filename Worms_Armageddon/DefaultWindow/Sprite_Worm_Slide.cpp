#include "stdafx.h"
#include "Sprite_Worm_Slide.h"
#include "Obj_Worm.h"


CSprite_Worm_Slide::CSprite_Worm_Slide()
	:m_bEnd(false), m_bSlideEnd(false)
{
}


CSprite_Worm_Slide::~CSprite_Worm_Slide()
{
}

void CSprite_Worm_Slide::Initialize(CObj * _pObj)
{
	m_pOwner = _pObj;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Fly/SlideLeft.bmp", L"SlideLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Fly/SlideLeftUp.bmp", L"SlideLeftUp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Fly/SlideLeftDown.bmp", L"SlideLeftDown");


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Fly/SlideRight.bmp", L"SlideRight");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Fly/SlideRightUp.bmp", L"SlideRightUp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Fly/SlideRightDown.bmp", L"SlideRightDown");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Fly/SlideEndLeft.bmp", L"SlideEndLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Fly/SlideEndLeftUp.bmp", L"SlideEndLeftUp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Fly/SlideEndLeftDown.bmp", L"SlideEndLeftDown");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Fly/SlideEndRight.bmp", L"SlideEndRight");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Fly/SlideEndRightUp.bmp", L"SlideEndRightUp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Fly/SlideEndRightDown.bmp", L"SlideEndRightDown");


	m_SlideState = WORM_SLIDE_STATE::SLIDE;

	m_CurrDir = m_pOwner->Get_ObjDir();
	Change_Dir();


	

	m_fCX = 60.0f;
	m_fCY = 60.0f;

	

	m_SpriteState = SPRITE_STATE::START;

	m_PrevSpriteTime = GetTickCount();
}

void CSprite_Worm_Slide::Update(void)
{
	if (m_bSlideEnd && m_SlideState == WORM_SLIDE_STATE::SLIDE)
		Set_SlideEnd();

	Change_Dir();
	
	if (m_SlideState == WORM_SLIDE_STATE::SLIDE)
	{
		Set_SlideAngle();
	}
	else if (m_SlideState == WORM_SLIDE_STATE::END)
	{
		Set_SlideEndAngle();
	}

	++m_iCurr;
	if (m_iCurr >= m_iMax)
	{
		m_iCurr = m_iMax - 1;

		if (m_SlideState == WORM_SLIDE_STATE::END)
		{
			m_bEnd = true;
		}
			
	}
		
}

void CSprite_Worm_Slide::LateUpdate(void)
{

}

void CSprite_Worm_Slide::Render(HDC _hDC)
{
	float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
	float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();

	

	GdiTransparentBlt(_hDC,
		(int)(m_pOwner->Get_Pos().fX - m_fCX * 0.5f) + fScrollX, // 복사받을 x위치의 좌표
		(int)(m_pOwner->Get_Pos().fY - m_fCY * 0.5f) + fScrollY, // 복사 받을 y위치의 좌표)
		(int)m_fCX, // 복사 받을 가로 길이
		(int)m_fCY, // 복사 받을 세로 길이
		m_hCurrDC,	// 복사할 비트맵 이미지 dc
		0,		// 비트맵을 출력할 시작 x좌표
		(int)(m_iCurr * m_fCY),		// 비트맵을 출력할 시작 y좌표
		(int)m_fCX, // 복사할 비트맵의 가로 사이즈
		(int)m_fCY,// 복사할 비트맵의 세로 사이즈
		RGB(128, 128, 192)); //제거하고자 하는 색상
}

void CSprite_Worm_Slide::Set_Size(void)
{

}

void CSprite_Worm_Slide::Reset_Slide(void)
{
	m_CurrDir = m_pOwner->Get_ObjDir();
	Change_Dir();

	m_SpriteState = SPRITE_STATE::START;

	m_bSlideEnd = false;
	m_bEnd = false;
	Set_Slide();
}

void CSprite_Worm_Slide::Change_Dir(void)
{
	if (m_CurrDir != m_pOwner->Get_ObjDir())
	{
		m_CurrDir = m_pOwner->Get_ObjDir();
	}

}

void CSprite_Worm_Slide::Set_SlideAngle(void)
{
	float fLeftAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_LeftAngle();
	float fRightAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_RightAngle();

	if (m_CurrDir == OBJ_DIR::LEFT)
	{
		if (fLeftAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"SlideLeftDown");
		}
		else if (fLeftAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"SlideLeftUp");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"SlideLeft");

		}

	}
	else if (m_CurrDir == OBJ_DIR::RIGHT)
	{
		if (fRightAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"SlideRightUp");

		}
		else if (fRightAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"SlideRightDown");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"SlideRight");
		}
	}
}

void CSprite_Worm_Slide::Set_Slide(void)
{
	m_iCurr = 0;
	m_iMax = 3;

	m_DelayTime = 150;

	m_SpriteDelay = 0;

	m_SlideState = WORM_SLIDE_STATE::SLIDE;

	m_SpriteState = SPRITE_STATE::START;

	Set_SlideAngle();
}

void CSprite_Worm_Slide::Set_SlideEnd(void)
{
	m_iCurr = 0;
	m_iMax = 22;

	m_DelayTime = 10;

	m_SpriteDelay = 0;

	m_SlideState = WORM_SLIDE_STATE::END;

	m_SpriteState = SPRITE_STATE::START;

	Set_SlideEndAngle();
}

void CSprite_Worm_Slide::Set_SlideEndAngle(void)
{
	float fLeftAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_LeftAngle();
	float fRightAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_RightAngle();





	if (m_CurrDir == OBJ_DIR::LEFT)
	{
		if (fLeftAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"SlideEndLeftDown");
		}
		else if (fLeftAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"SlideEndLeftUp");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"SlideEndLeft");

		}

	}
	else if (m_CurrDir == OBJ_DIR::RIGHT)
	{
		if (fRightAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"SlideEndRightUp");

		}
		else if (fRightAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"SlideEndRightDown");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"SlideEndRight");
		}
	}
}
