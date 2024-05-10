#include "stdafx.h"
#include "Image_WeaponAim.h"
#include "BmpMgr.h"


CImage_WeaponAim::CImage_WeaponAim()
	:m_fAimDistance(88.0f)
{
	m_fLength = 10.0f;
}


CImage_WeaponAim::~CImage_WeaponAim()
{
}

void CImage_WeaponAim::Initialize(CObj * _pObj)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/AimLeft.bmp", L"AimLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/AimRight.bmp", L"AimRight");

	
	m_fAngle = 0.0f;
	m_fLength = 0.0f;
	
	m_pOwner = _pObj;
}

void CImage_WeaponAim::Update(void)
{
	Set_TargetWeaponAngle();

	m_iCurr = (int)(m_fAngle / 5.625f);
	if (m_iCurr >= m_iMax)
		m_iCurr = m_iMax - 1;


	if (m_fAimDistance != m_fLength)
	{
		m_fLength += 5.5f;

		if (abs(m_fAimDistance - m_fLength) < 2)
			m_fLength = m_fAimDistance;
	}

	if (m_fLength > 30.0f)
	{
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

}

void CImage_WeaponAim::LateUpdate(void)
{
}

void CImage_WeaponAim::Render(HDC _hDC)
{
	float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
	float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();


	float fX = (m_fLength * sinf(DEG2RAD(m_fTargetAngle)));
	float fY = (m_fLength * cosf(DEG2RAD(m_fTargetAngle)));

	if (m_pOwner->Get_ObjDir() == OBJ_DIR::LEFT)
		fX *= -1;

	int fOwnerX = (int)(m_pOwner->Get_Pos().fX);
	int fOwnerY = (int)(m_pOwner->Get_Pos().fY);

	if (m_fLength > 30.0f)
	{
		GdiTransparentBlt(_hDC,
			(int)(((fOwnerX + fX) - m_fCX * 0.5f) + fScrollX), // 복사받을 x위치의 좌표
			(int)(((fOwnerY + fY) - m_fCY * 0.5f) + fScrollY), // 복사 받을 y위치의 좌표)
			(int)m_fCX, // 복사 받을 가로 길이
			(int)m_fCY, // 복사 받을 세로 길이
			m_hCurrDC,	// 복사할 비트맵 이미지 dc
			0,		// 비트맵을 출력할 시작 x좌표
			(int)(m_iCurr * m_fCY),		// 비트맵을 출력할 시작 y좌표
			(int)m_fCX, // 복사할 비트맵의 가로 사이즈
			(int)m_fCY,// 복사할 비트맵의 세로 사이즈
			(RGB(128, 128, 192))); //제거하고자 하는 색상
	}
}

void CImage_WeaponAim::Set_Size(void)
{
}

void CImage_WeaponAim::Reset(void)
{
	m_iMax = 32;
	m_fAngle = 0.0f;
	m_iCurr = 0;

	m_fCX = 60.0f;
	m_fCY = 60.0f;

	m_iR = 128;
	m_iG = 128;
	m_iB = 192;

	m_fLength = 0.0f;

	if (m_pOwner->Get_ObjDir() == OBJ_DIR::LEFT)
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"AimLeft");

	else if (m_pOwner->Get_ObjDir() == OBJ_DIR::RIGHT)
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"AimRight");

}
