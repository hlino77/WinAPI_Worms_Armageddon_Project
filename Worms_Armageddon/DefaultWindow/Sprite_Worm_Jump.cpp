#include "stdafx.h"
#include "Sprite_Worm_Jump.h"
#include "Obj_Worm.h"

CSprite_Worm_Jump::CSprite_Worm_Jump()
{
}


CSprite_Worm_Jump::~CSprite_Worm_Jump()
{
}

void CSprite_Worm_Jump::Initialize(CObj * _pObj)
{
	m_pOwner = _pObj;
	Insert_Bmp();

	m_CurrDir = m_pOwner->Get_ObjDir();

	m_iCurr = 0;
	m_iMax = 0;

	m_fCX = 60.0f;
	m_fCY = 60.0f;

	m_SpriteTime = GetTickCount();
	m_DelayTime = 0;
	m_SpriteDelay = 0;

	m_fLeftAngle = 0.0f;
	m_fRightAngle = 0.0f;

	m_SpriteState = SPRITE_STATE::END;

	m_PrevSpriteTime = GetTickCount();

	m_WormJumpState = WORM_JUMP_STATE::TYPEEND;
}

void CSprite_Worm_Jump::Update(void)
{
	if (m_SpriteTime + m_DelayTime < GetTickCount())
	{
		++m_iCurr;
		if (m_iCurr >= m_iMax)
		{
			if (m_WormJumpState == WORM_JUMP_STATE::FLYUP || m_WormJumpState == WORM_JUMP_STATE::FLYDOWN)
			{
				m_iCurr = 0;
			}
			else
			{
				m_iCurr = m_iMax - 1;
			}

			if(m_WormJumpState == WORM_JUMP_STATE::LAND || m_WormJumpState == WORM_JUMP_STATE::FLY)
				m_SpriteState = SPRITE_STATE::END;

			
		}
		m_SpriteTime = GetTickCount();
	}

}

void CSprite_Worm_Jump::LateUpdate(void)
{



	if (m_WormJumpState != static_cast<CObj_Worm*>(m_pOwner)->Get_JumpState())
	{
		m_WormJumpState = static_cast<CObj_Worm*>(m_pOwner)->Get_JumpState();
		Change_State();
	}
}

void CSprite_Worm_Jump::Render(HDC _hDC)
{
	float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
	float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();


	if (m_WormJumpState == WORM_JUMP_STATE::LAND)
		int i = 0;

	GdiTransparentBlt(_hDC,
		int(m_pOwner->Get_Pos().fX - m_fCX * 0.5f) + fScrollX, // 복사받을 x위치의 좌표
		(m_pOwner->Get_Pos().fY - m_fCY * 0.5f) + fScrollY, // 복사 받을 y위치의 좌표)
		m_fCX, // 복사 받을 가로 길이
		m_fCY, // 복사 받을 세로 길이
		m_hCurrDC,	// 복사할 비트맵 이미지 dc
		0,		// 비트맵을 출력할 시작 x좌표
		m_iCurr * m_fCY,		// 비트맵을 출력할 시작 y좌표
		(int)m_fCX, // 복사할 비트맵의 가로 사이즈
		(int)m_fCY,// 복사할 비트맵의 세로 사이즈
		RGB(128, 128, 192)); //제거하고자 하는 색상
}

void CSprite_Worm_Jump::Set_Size(void)
{
}

void CSprite_Worm_Jump::Change_State(void)
{
	switch (m_WormJumpState)
	{
	case WORM_JUMP_STATE::START:
		Set_Jump();
		break;
	case WORM_JUMP_STATE::READY:
		Set_JumpReady();
		break;
	case WORM_JUMP_STATE::FLYUP:
		Set_FlyUp();
		break;
	case WORM_JUMP_STATE::FLY:
		Set_Fly();
		break;
	case WORM_JUMP_STATE::FLYDOWN:
		Set_FlyDown();
		break;
	case WORM_JUMP_STATE::LAND:
		Set_Land();
		break;
	case WORM_JUMP_STATE::END:
		m_SpriteState = SPRITE_STATE::END;
		break;
	}
}

void CSprite_Worm_Jump::Insert_Bmp(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Jump/BackFlipLeft.bmp", L"BackFlipLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Jump/BackFlipRight.bmp", L"BackFlipRight");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Jump/FlyDownLeft.bmp", L"FlyDownLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Jump/FlyDownRight.bmp", L"FlyDownRight");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Jump/FlyLinkLeft.bmp", L"FlyLinkLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Jump/FlyLinkRight.bmp", L"FlyLinkRight");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Jump/FlyUpLeft.bmp", L"FlyUpLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Jump/FlyUpRight.bmp", L"FlyUpRight");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Jump/JumpDownLeft.bmp", L"JumpDownLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Jump/JumpDownRight.bmp", L"JumpDownRight");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Jump/JumpLeft.bmp", L"JumpLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Jump/JumpRight.bmp", L"JumpRight");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Jump/JumpUpLeft.bmp", L"JumpUpLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Jump/JumpUpRight.bmp", L"JumpUpRight");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Jump/LandDownLeft.bmp", L"LandDownLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Jump/LandDownRight.bmp", L"LandDownRight");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Jump/LandLeft.bmp", L"LandLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Jump/LandRight.bmp", L"LandRight");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Jump/LandUpRight.bmp", L"LandUpRight");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Jump/LandUpLeft.bmp", L"LandUpLeft");


}

void CSprite_Worm_Jump::Set_Jump(void)
{
	Set_Angle();
	m_CurrDir = m_pOwner->Get_ObjDir();

	Set_Angle();
	m_CurrDir = m_pOwner->Get_ObjDir();


	if (m_CurrDir == OBJ_DIR::LEFT)
	{
		if (m_fLeftAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"JumpDownLeft");
		}
		else if (m_fLeftAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"JumpUpLeft");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"JumpLeft");
		}

	}
	else if (m_CurrDir == OBJ_DIR::RIGHT)
	{
		if (m_fRightAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"JumpUpRight");
		}
		else if (m_fRightAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"JumpDownRight");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"JumpRight");
		}
	}

	m_iCurr = 0;
	m_iMax = 1;


	m_SpriteTime = GetTickCount();
	m_DelayTime = 0;
	m_SpriteDelay = 40;

	m_SpriteState = SPRITE_STATE::START;

}

void CSprite_Worm_Jump::Set_JumpReady(void)
{
	Set_Angle();
	m_CurrDir = m_pOwner->Get_ObjDir();
	

	if (m_CurrDir == OBJ_DIR::LEFT)
	{
		if (m_fLeftAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"JumpDownLeft");
		}
		else if (m_fLeftAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"JumpUpLeft");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"JumpLeft");
		}

	}
	else if (m_CurrDir == OBJ_DIR::RIGHT)
	{
		if (m_fRightAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"JumpUpRight");
		}
		else if (m_fRightAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"JumpDownRight");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"JumpRight");
		}
	}

	m_iCurr = 1;
	m_iMax = 10;


	m_SpriteTime = GetTickCount();
	m_DelayTime = 20;

	m_SpriteState = SPRITE_STATE::START;

}

void CSprite_Worm_Jump::Set_FlyUp(void)
{

	if (m_CurrDir == OBJ_DIR::LEFT)
	{
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"FlyUpLeft");
	}
	else if (m_CurrDir == OBJ_DIR::RIGHT)
	{
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"FlyUpRight");
	}


	m_iCurr = 0;
	m_iMax = 2;


	m_SpriteTime = GetTickCount();
	m_DelayTime = 20;

	m_SpriteState = SPRITE_STATE::START;
}

void CSprite_Worm_Jump::Set_Fly(void)
{

	if (m_CurrDir == OBJ_DIR::LEFT)
	{
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"FlyLinkLeft");
	}
	else if (m_CurrDir == OBJ_DIR::RIGHT)
	{
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"FlyLinkRight");
	}


	m_iCurr = 0;
	m_iMax = 7;


	m_SpriteTime = GetTickCount();
	m_DelayTime = 50;


	m_SpriteState = SPRITE_STATE::START;
}

void CSprite_Worm_Jump::Set_FlyDown(void)
{
	if (m_CurrDir == OBJ_DIR::LEFT)
	{
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"FlyDownLeft");
	}
	else if (m_CurrDir == OBJ_DIR::RIGHT)
	{
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"FlyDownRight");
	}


	m_iCurr = 0;
	m_iMax = 2;


	m_SpriteTime = GetTickCount();
	m_DelayTime = 100;


	m_SpriteState = SPRITE_STATE::START;
}

void CSprite_Worm_Jump::Set_Land(void)
{
	Set_Angle();



	if (m_CurrDir == OBJ_DIR::LEFT)
	{
		if (m_fLeftAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"LandDownLeft");
		}
		else if (m_fLeftAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"LandUpLeft");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"LandLeft");
		}

	}
	else if (m_CurrDir == OBJ_DIR::RIGHT)
	{
		if (m_fRightAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"LandUpRight");
		}
		else if (m_fRightAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"LandDownRight");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"LandRight");
		}
	}

	m_iCurr = 0;
	m_iMax = 6;


	m_SpriteTime = GetTickCount();
	m_DelayTime = 40;

	m_SpriteState = SPRITE_STATE::START;
}

void CSprite_Worm_Jump::Set_Angle(void)
{
	m_fLeftAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_LeftAngle();
	m_fRightAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_RightAngle();
}
