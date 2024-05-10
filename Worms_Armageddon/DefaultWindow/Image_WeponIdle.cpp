#include "stdafx.h"
#include "Image_WeponIdle.h"
#include "Obj_Worm.h"

CImage_WeaponIdle::CImage_WeaponIdle()
{
}


CImage_WeaponIdle::~CImage_WeaponIdle()
{

}

void CImage_WeaponIdle::Initialize(CObj * _pObj)
{
	m_pOwner = _pObj;

	
	Insert_Image();
}

void CImage_WeaponIdle::Update(void)
{
	Set_TargetWeaponAngle();

	if (m_fAngle != m_fTargetAngle)
	{
		float fSpeed = (m_fTargetAngle - m_fAngle) * 0.2f;
		m_fAngle += fSpeed;

		if (abs(m_fTargetAngle - m_fAngle) < 2)
		{
			m_fAngle = m_fTargetAngle;
		}
	}
}

void CImage_WeaponIdle::LateUpdate(void)
{
	m_iCurr = (int)(m_fAngle / 5.625f);
	if (m_iCurr >= m_iMax)
		m_iCurr = m_iMax - 1;
}

void CImage_WeaponIdle::Render(HDC _hDC)
{
	float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
	float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();


	GdiTransparentBlt(_hDC,
		(int)((m_pOwner->Get_Pos().fX - m_fCX * 0.5f) + fScrollX), // 복사받을 x위치의 좌표
		(int)((m_pOwner->Get_Pos().fY - m_fCY * 0.5f) + fScrollY), // 복사 받을 y위치의 좌표)
		(int)m_fCX, // 복사 받을 가로 길이
		(int)m_fCY, // 복사 받을 세로 길이
		m_hCurrDC,	// 복사할 비트맵 이미지 dc
		0,		// 비트맵을 출력할 시작 x좌표
		(int)(m_iCurr * m_fCY),		// 비트맵을 출력할 시작 y좌표
		(int)m_fCX, // 복사할 비트맵의 가로 사이즈
		(int)m_fCY,// 복사할 비트맵의 세로 사이즈
		(RGB(m_iR, m_iG, m_iB))); //제거하고자 하는 색상
}


void CImage_WeaponIdle::Set_Weapon(void)
{
	switch (static_cast<CObj_Worm*>(m_pOwner)->Get_Weapon()->Get_WeaponType())
	{
	case WEAPON_TYPE::BAZOOKA:
		Set_Bazooka();
		break;
	case WEAPON_TYPE::HMISSILE:
		Set_Bazooka();
		break;
	case WEAPON_TYPE::BASEBALL:
		Set_Base();
		break;
	}
}





void CImage_WeaponIdle::Insert_Image(void)
{
	//바주카
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Bazooka/Bazooka_Left.bmp", L"Bazooka_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Bazooka/Bazooka_Right.bmp", L"Bazooka_Right");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Bazooka/Bazooka_LeftUp.bmp", L"Bazooka_LeftUp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Bazooka/Bazooka_RightUp.bmp", L"Bazooka_RightUp");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Bazooka/Bazooka_LeftDown.bmp", L"Bazooka_LeftDown");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Bazooka/Bazooka_RightDown.bmp", L"Bazooka_RightDown");

	//야구
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Baseball/BaseIdleLeft.bmp", L"BaseIdleLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Baseball/BaseIdleLeftUp.bmp", L"BaseIdleLeftUp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Baseball/BaseIdleLeftDown.bmp", L"BaseIdleLeftDown");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Baseball/BaseIdleRight.bmp", L"BaseIdleRight");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Baseball/BaseIdleRightUp.bmp", L"BaseIdleRightUp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Baseball/BaseIdleRightDown.bmp", L"BaseIdleRightDown");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Baseball/BaseEndLeft.bmp", L"BaseEndLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Baseball/BaseEndLeftUp.bmp", L"BaseEndLeftUp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Baseball/BaseEndLeftDown.bmp", L"BaseEndLeftDown");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Baseball/BaseEndRight.bmp", L"BaseEndRight");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Baseball/BaseEndRightUp.bmp", L"BaseEndRightUp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Baseball/BaseEndRightDown.bmp", L"BaseEndRightDown");
}

void CImage_WeaponIdle::Set_Bazooka(void)
{
	Set_TargetWeaponAngle();

	m_iMax = 32;
	m_fAngle = 90.0f;

	m_iCurr = (int)(m_fAngle / 5.625f);
	if (m_iCurr >= m_iMax)
		m_iCurr = m_iMax - 1;

	

	m_fCX = 60.0f;
	m_fCY = 60.0f;

	m_iR = 128;
	m_iG = 128;
	m_iB = 192;

	Set_Bazooka_Angle();
}

void CImage_WeaponIdle::Set_Bazooka_Angle(void)
{
	float fLeftAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_LeftAngle();
	float fRightAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_RightAngle();
	m_CurrDir = m_pOwner->Get_ObjDir();

	if (m_CurrDir == OBJ_DIR::LEFT)
	{
		if (fLeftAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Bazooka_LeftDown");
		}
		else if (fLeftAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Bazooka_LeftUp");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Bazooka_Left");
		}

	}
	else if (m_CurrDir == OBJ_DIR::RIGHT)
	{
		if (fRightAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Bazooka_RightUp");
		}
		else if (fRightAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Bazooka_RightDown");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Bazooka_Right");
		}
	}
}

void CImage_WeaponIdle::Set_Base(void)
{
	Set_TargetWeaponAngle();

	m_iMax = 32;
	m_fAngle = 90.0f;

	m_iCurr = (int)(m_fAngle / 5.625f);
	if (m_iCurr >= m_iMax)
		m_iCurr = m_iMax - 1;



	m_fCX = 60.0f;
	m_fCY = 60.0f;

	m_iR = 192;
	m_iG = 192;
	m_iB = 128;

	Set_Base_Angle();
}

void CImage_WeaponIdle::Set_Base_Angle(void)
{
	float fLeftAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_LeftAngle();
	float fRightAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_RightAngle();
	m_CurrDir = m_pOwner->Get_ObjDir();

	switch (static_cast<CObj_Worm*>(m_pOwner)->Get_Weapon()->Get_WeaponState())
	{
	case WEAPON_STATE::IDLE:
		if (m_CurrDir == OBJ_DIR::LEFT)
		{
			if (fLeftAngle < -23.0f)
			{
				m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"BaseIdleLeftDown");
			}
			else if (fLeftAngle > 23.0f)
			{
				m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"BaseIdleLeftUp");
			}
			else
			{
				m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"BaseIdleLeft");
			}

		}
		else if (m_CurrDir == OBJ_DIR::RIGHT)
		{
			if (fRightAngle < -23.0f)
			{
				m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"BaseIdleRightUp");
			}
			else if (fRightAngle > 23.0f)
			{
				m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"BaseIdleRightDown");
			}
			else
			{
				m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"BaseIdleRight");
			}
		}
		break;
	case WEAPON_STATE::SHOOT:
		if (m_CurrDir == OBJ_DIR::LEFT)
		{
			if (fLeftAngle < -23.0f)
			{
				m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"BaseEndLeftDown");
			}
			else if (fLeftAngle > 23.0f)
			{
				m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"BaseEndLeftUp");
			}
			else
			{
				m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"BaseEndLeft");
			}

		}
		else if (m_CurrDir == OBJ_DIR::RIGHT)
		{
			if (fRightAngle < -23.0f)
			{
				m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"BaseEndRightUp");
			}
			else if (fRightAngle > 23.0f)
			{
				m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"BaseEndRightDown");
			}
			else
			{
				m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"BaseEndRight");
			}
		}
		break;
	}
	
}



