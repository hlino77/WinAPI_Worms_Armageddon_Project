#include "stdafx.h"
#include "Sprite_DrawWeapon.h"
#include "Obj_Worm.h"

CSprite_DrawWeapon::CSprite_DrawWeapon()
	:m_iR(0), m_iG(0), m_iB(0), m_bUseIdle(false)
{
}


CSprite_DrawWeapon::~CSprite_DrawWeapon()
{
}

void CSprite_DrawWeapon::Initialize(CObj * _pObj)
{
	m_pOwner = _pObj;


	Insert_Image();

	


	m_SpriteState = SPRITE_STATE::START;

	m_PrevSpriteTime = GetTickCount();
}

void CSprite_DrawWeapon::Update(void)
{
	switch (m_SpriteState)
	{
	case SPRITE_STATE::START:
		if (m_SpriteTime + m_DelayTime < GetTickCount())
		{
			++m_iCurr;
			if (m_iCurr >= m_iMax)
			{
				m_iCurr = m_iMax - 1;
				m_SpriteState = SPRITE_STATE::END;
			}
			m_SpriteTime = GetTickCount();
		}
		break;
	}
}

void CSprite_DrawWeapon::LateUpdate(void)
{

}

void CSprite_DrawWeapon::Render(HDC _hDC)
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
		RGB(m_iR, m_iG, m_iB)); //제거하고자 하는 색상
}


void CSprite_DrawWeapon::Set_Bazooka(void)
{
	m_iCurr = 0;
	m_iMax = 7;

	m_SpriteTime = GetTickCount();
	m_DelayTime = 20;
	m_SpriteDelay = 0;

	m_fCX = 60.0f;
	m_fCY = 60.0f;

	m_iR = 128;
	m_iG = 128;
	m_iB = 192;

	m_bUseIdle = true;
	
	Set_Bazooka_Angle();
	m_SpriteState = SPRITE_STATE::START;
}

void CSprite_DrawWeapon::Set_Bazooka_Angle(void)
{
	float fLeftAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_LeftAngle();
	float fRightAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_RightAngle();
	m_CurrDir = m_pOwner->Get_ObjDir();

	if (m_CurrDir == OBJ_DIR::LEFT)
	{
		if (fLeftAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Draw_Bazooka_LeftDown");
		}
		else if (fLeftAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Draw_Bazooka_LeftUp");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Draw_Bazooka_Left");
		}

	}
	else if (m_CurrDir == OBJ_DIR::RIGHT)
	{
		if (fRightAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Draw_Bazooka_RightUp");
		}
		else if (fRightAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Draw_Bazooka_RightDown");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Draw_Bazooka_Right");
		}
	}
}

void CSprite_DrawWeapon::Set_Banana(void)
{
	m_iCurr = 0;
	m_iMax = 10;

	m_SpriteTime = GetTickCount();
	m_DelayTime = 20;
	m_SpriteDelay = 0;

	m_fCX = 60.0f;
	m_fCY = 60.0f;

	m_iR = 128;
	m_iG = 128;
	m_iB = 192;

	m_bUseIdle = false;

	Set_Banana_Angle();
	m_SpriteState = SPRITE_STATE::START;
}

void CSprite_DrawWeapon::Set_Banana_Angle(void)
{
	float fLeftAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_LeftAngle();
	float fRightAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_RightAngle();
	m_CurrDir = m_pOwner->Get_ObjDir();

	if (m_CurrDir == OBJ_DIR::LEFT)
	{
		if (fLeftAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Draw_BananaLeftDown");
		}
		else if (fLeftAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Draw_BananaLeftUp");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Draw_BananaLeft");
		}

	}
	else if (m_CurrDir == OBJ_DIR::RIGHT)
	{
		if (fRightAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Draw_BananaRightUp");
		}
		else if (fRightAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Draw_BananaRightDown");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Draw_BananaRight");
		}
	}
}

void CSprite_DrawWeapon::Set_Radio(void)
{
	m_iCurr = 0;
	m_iMax = 10;

	m_SpriteTime = GetTickCount();
	m_DelayTime = 20;
	m_SpriteDelay = 0;

	m_fCX = 60.0f;
	m_fCY = 60.0f;

	m_iR = 128;
	m_iG = 128;
	m_iB = 192;

	m_bUseIdle = false;

	Set_Radio_Angle();
	m_SpriteState = SPRITE_STATE::START;
}

void CSprite_DrawWeapon::Set_Radio_Angle(void)
{
	float fLeftAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_LeftAngle();
	float fRightAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_RightAngle();
	m_CurrDir = m_pOwner->Get_ObjDir();

	if (m_CurrDir == OBJ_DIR::LEFT)
	{
		if (fLeftAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Radio_LeftDown");
		}
		else if (fLeftAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Radio_LeftUp");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Radio_Left");
		}

	}
	else if (m_CurrDir == OBJ_DIR::RIGHT)
	{
		if (fRightAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Radio_RightUp");
		}
		else if (fRightAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Radio_RightDown");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Radio_Right");
		}
	}
}

void CSprite_DrawWeapon::Set_Base(void)
{
	m_iCurr = 0;
	m_iMax = 10;

	m_SpriteTime = GetTickCount();
	m_DelayTime = 20;
	m_SpriteDelay = 0;

	m_fCX = 60.0f;
	m_fCY = 60.0f;

	m_iR = 192;
	m_iG = 192;
	m_iB = 128;

	m_bUseIdle = true;

	Set_Base_Angle();
	m_SpriteState = SPRITE_STATE::START;
}

void CSprite_DrawWeapon::Set_Base_Angle(void)
{
	float fLeftAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_LeftAngle();
	float fRightAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_RightAngle();
	m_CurrDir = m_pOwner->Get_ObjDir();

	if (m_CurrDir == OBJ_DIR::LEFT)
	{
		if (fLeftAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"DrawBaseLeftDown");
		}
		else if (fLeftAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"DrawBaseLeftUp");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"DrawBaseLeft");
		}

	}
	else if (m_CurrDir == OBJ_DIR::RIGHT)
	{
		if (fRightAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"DrawBaseRightUp");
		}
		else if (fRightAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"DrawBaseRightDown");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"DrawBaseRight");
		}
	}
}

void CSprite_DrawWeapon::Set_Holy(void)
{
	m_iCurr = 0;
	m_iMax = 10;

	m_SpriteTime = GetTickCount();
	m_DelayTime = 20;
	m_SpriteDelay = 0;

	m_fCX = 60.0f;
	m_fCY = 60.0f;

	m_iR = 128;
	m_iG = 128;
	m_iB = 192;

	m_bUseIdle = false;

	Set_Holy_Angle();
	m_SpriteState = SPRITE_STATE::START;
}

void CSprite_DrawWeapon::Set_Holy_Angle(void)
{
	float fLeftAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_LeftAngle();
	float fRightAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_RightAngle();
	m_CurrDir = m_pOwner->Get_ObjDir();

	if (m_CurrDir == OBJ_DIR::LEFT)
	{
		if (fLeftAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"HolyLeftDown");
		}
		else if (fLeftAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"HolyLeftUp");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"HolyLeft");
		}

	}
	else if (m_CurrDir == OBJ_DIR::RIGHT)
	{
		if (fRightAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"HolyRightUp");
		}
		else if (fRightAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"HolyRightDown");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"HolyRight");
		}
	}
}

void CSprite_DrawWeapon::Set_Hat(void)
{
	m_iCurr = 0;
	m_iMax = 15;

	m_SpriteTime = GetTickCount();
	m_DelayTime = 20;
	m_SpriteDelay = 0;

	m_fCX = 60.0f;
	m_fCY = 60.0f;

	m_iR = 128;
	m_iG = 128;
	m_iB = 192;

	m_bUseIdle = false;

	Set_Hat_Angle();
	m_SpriteState = SPRITE_STATE::START;
}

void CSprite_DrawWeapon::Set_Hat_Angle(void)
{
	float fLeftAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_LeftAngle();
	float fRightAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_RightAngle();
	m_CurrDir = m_pOwner->Get_ObjDir();

	if (m_CurrDir == OBJ_DIR::LEFT)
	{
		if (fLeftAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"HatLeftDown");
		}
		else if (fLeftAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"HatLeftUp");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"HatLeft");
		}

	}
	else if (m_CurrDir == OBJ_DIR::RIGHT)
	{
		if (fRightAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"HatRightUp");
		}
		else if (fRightAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"HatRightDown");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"HatRight");
		}
	}
}

void CSprite_DrawWeapon::Set_Sheep(void)
{
	m_iCurr = 0;
	m_iMax = 10;

	m_SpriteTime = GetTickCount();
	m_DelayTime = 20;
	m_SpriteDelay = 0;

	m_fCX = 60.0f;
	m_fCY = 60.0f;

	m_iR = 192;
	m_iG = 192;
	m_iB = 128;

	m_bUseIdle = false;

	Set_Sheep_Angle();
	m_SpriteState = SPRITE_STATE::START;
}

void CSprite_DrawWeapon::Set_Sheep_Angle(void)
{
	float fLeftAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_LeftAngle();
	float fRightAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_RightAngle();
	m_CurrDir = m_pOwner->Get_ObjDir();

	if (m_CurrDir == OBJ_DIR::LEFT)
	{
		if (fLeftAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"SheepLeftDown");
		}
		else if (fLeftAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"SheepLeftUp");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"SheepLeft");
		}

	}
	else if (m_CurrDir == OBJ_DIR::RIGHT)
	{
		if (fRightAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"SheepRightUp");
		}
		else if (fRightAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"SheepRightDown");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"SheepRight");
		}
	}
}

void CSprite_DrawWeapon::Set_Meteor(void)
{
	m_iCurr = 0;
	m_iMax = 1;

	m_SpriteTime = GetTickCount();
	m_DelayTime = 20;
	m_SpriteDelay = 0;

	m_fCX = 60.0f;
	m_fCY = 60.0f;

	m_iR = 128;
	m_iG = 128;
	m_iB = 192;

	m_bUseIdle = false;

	Set_Meteor_Angle();
	m_SpriteState = SPRITE_STATE::START;
}

void CSprite_DrawWeapon::Set_Meteor_Angle(void)
{
	float fLeftAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_LeftAngle();
	float fRightAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_RightAngle();
	m_CurrDir = m_pOwner->Get_ObjDir();

	if (m_CurrDir == OBJ_DIR::LEFT)
	{
		if (fLeftAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Left_Down_Idle");
		}
		else if (fLeftAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Left_Up_Idle");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Left_Idle");
		}

	}
	else if (m_CurrDir == OBJ_DIR::RIGHT)
	{
		if (fRightAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Right_Up_Idle");
		}
		else if (fRightAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Right_Down_Idle");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Right_Idle");
		}
	}
}




void CSprite_DrawWeapon::Insert_Image(void)
{
	//바주카
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Bazooka/Draw_Bazooka_Left.bmp", L"Draw_Bazooka_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Bazooka/Draw_Bazooka_LeftDown.bmp", L"Draw_Bazooka_LeftDown");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Bazooka/Draw_Bazooka_LeftUp.bmp", L"Draw_Bazooka_LeftUp");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Bazooka/Draw_Bazooka_Right.bmp", L"Draw_Bazooka_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Bazooka/Draw_Bazooka_RightDown.bmp", L"Draw_Bazooka_RightDown");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Bazooka/Draw_Bazooka_RightUp.bmp", L"Draw_Bazooka_RightUp");
	//

	//바나나
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Banana/Draw_BananaLeft.bmp", L"Draw_BananaLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Banana/Draw_BananaLeftUp.bmp", L"Draw_BananaLeftUp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Banana/Draw_BananaLeftDown.bmp", L"Draw_BananaLeftDown");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Banana/Draw_BananaRight.bmp", L"Draw_BananaRight");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Banana/Draw_BananaRightDown.bmp", L"Draw_BananaRightDown");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Banana/Draw_BananaRightUp.bmp", L"Draw_BananaRightUp");

	//무전기
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Radio/Radio_Left.bmp", L"Radio_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Radio/Radio_LeftDown.bmp", L"Radio_LeftDown");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Radio/Radio_LeftUp.bmp", L"Radio_LeftUp");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Radio/Radio_Right.bmp", L"Radio_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Radio/Radio_RightDown.bmp", L"Radio_RightDown");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Radio/Radio_RightUp.bmp", L"Radio_RightUp");

	//야구
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Baseball/DrawBaseLeft.bmp", L"DrawBaseLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Baseball/DrawBaseLeftUp.bmp", L"DrawBaseLeftUp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Baseball/DrawBaseLeftDown.bmp", L"DrawBaseLeftDown");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Baseball/DrawBaseRight.bmp", L"DrawBaseRight");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Baseball/DrawBaseRightUp.bmp", L"DrawBaseRightUp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Baseball/DrawBaseRightDown.bmp", L"DrawBaseRightDown");

	//홀리
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Holy/HolyLeft.bmp", L"HolyLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Holy/HolyLeftUp.bmp", L"HolyLeftUp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Holy/HolyLeftDown.bmp", L"HolyLeftDown");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Holy/HolyRight.bmp", L"HolyRight");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Holy/HolyRightUp.bmp", L"HolyRightUp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Holy/HolyRightDown.bmp", L"HolyRightDown");

	//구조물
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Structure/HatLeft.bmp", L"HatLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Structure/HatLeftDown.bmp", L"HatLeftDown");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Structure/HatLeftUp.bmp", L"HatLeftUp");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Structure/HatRight.bmp", L"HatRight");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Structure/HatRightDown.bmp", L"HatRightDown");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Structure/HatRightUp.bmp", L"HatRightUp");


	//양
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Sheep/SheepLeft.bmp", L"SheepLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Sheep/SheepLeftDown.bmp", L"SheepLeftDown");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Sheep/SheepLeftUp.bmp", L"SheepLeftUp");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Sheep/SheepRight.bmp", L"SheepRight");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Sheep/SheepRightUp.bmp", L"SheepRightUp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Sheep/SheepRightDown.bmp", L"SheepRightDown");


	//텔레포트
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Teleport/TeleportLeft.bmp", L"TeleportLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Teleport/TeleportLeftDown.bmp", L"TeleportLeftDown");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Teleport/TeleportLeftUp.bmp", L"TeleportLeftUp");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Teleport/TeleportRight.bmp", L"TeleportRight");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Teleport/TeleportRightDown.bmp", L"TeleportRightDown");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Teleport/TeleportRightUp.bmp", L"TeleportRightUp");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Teleport/TeleWorkLeft.bmp", L"TeleWorkLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Teleport/TeleWorkLeftDown.bmp", L"TeleWorkLeftDown");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Teleport/TeleWorkLeftUp.bmp", L"TeleWorkLeftUp");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Teleport/TeleWorkRight.bmp", L"TeleWorkRight");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Teleport/TeleWorkRightDown.bmp", L"TeleWorkRightDown");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Teleport/TeleWorkRightUp.bmp", L"TeleWorkRightUp");

}

void CSprite_DrawWeapon::Set_Weapon(void)
{
	switch (static_cast<CObj_Worm*>(m_pOwner)->Get_Weapon()->Get_WeaponType())
	{
	case WEAPON_TYPE::BAZOOKA:
		Set_Bazooka();
		break;

	case WEAPON_TYPE::BANANA:
		Set_Banana();
		break;

	case WEAPON_TYPE::DONKEY:
		Set_Radio();
		break;

	case WEAPON_TYPE::HMISSILE:
		Set_Bazooka();
		break;

	case WEAPON_TYPE::AIRMISSILE:
		Set_Radio();
		break;

	case WEAPON_TYPE::BASEBALL:
		Set_Base();
		break;

	case WEAPON_TYPE::HOLY:
		Set_Holy();
		break;

	case WEAPON_TYPE::STRUCTURE:
		Set_Hat();
		break;

	case WEAPON_TYPE::SHEEP:
		Set_Sheep();
		break;

	case WEAPON_TYPE::METEOR:
		Set_Meteor();
		break;

	case WEAPON_TYPE::TELEPORT:
		m_hCurrDC = nullptr;
		m_bUseIdle = false;
		break;
	}
}
