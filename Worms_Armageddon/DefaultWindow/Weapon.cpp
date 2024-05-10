#include "stdafx.h"
#include "Weapon.h"
#include "Image_WeaponAim.h"

CWeapon::CWeapon()
	:m_fAngle(90.0f), m_pOwner(nullptr), m_fLength(90.0f), m_fShootPower(0.0f), m_pAim(nullptr)
{
}


CWeapon::~CWeapon()
{
}

void CWeapon::Gage_Render(HDC _hDC)
{
	float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
	float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();


	float fCX = 64.0f;
	float fCY = 64.0f;
	float fDir = 1.0f;
	int iLength = (int)(m_fShootPower / 10.0f);

	if (m_pOwner->Get_ObjDir() == OBJ_DIR::LEFT)
		fDir = -1.0f;

	float fGageLength = (m_fShootPower * 0.5f) + 10.0f;
	
	int iOwnerX = (int)(m_pOwner->Get_Pos().fX);
	int iOwnerY = (int)(m_pOwner->Get_Pos().fY);

	for (int i = 0; i < iLength; ++i)
	{
		float fX = iOwnerX + ((fGageLength - (i * 5.0f)) * sinf(DEG2RAD(m_fAngle) * fDir));
		float fY = iOwnerY + ((fGageLength - (i * 5.0f)) * cosf(DEG2RAD(m_fAngle)));

		GdiTransparentBlt(_hDC,
			(int)((fX - fCX * 0.5f) + fScrollX), // 복사받을 x위치의 좌표
			(int)((fY - fCY * 0.5f) + fScrollY), // 복사 받을 y위치의 좌표)
			(int)fCX, // 복사 받을 가로 길이
			(int)fCY, // 복사 받을 세로 길이
			m_hGageDC,	// 복사할 비트맵 이미지 dc
			0,		// 비트맵을 출력할 시작 x좌표
			(int)((iLength - i) * fCY),		// 비트맵을 출력할 시작 y좌표
			(int)fCX, // 복사할 비트맵의 가로 사이즈
			(int)fCY,// 복사할 비트맵의 세로 사이즈
			(RGB(128, 128, 192))); //제거하고자 하는 색상
	}

	m_pAim->Render(_hDC);
}
void CWeapon::Reset_Aim(void)
{
	m_fAngle = 90.0f;
	if (m_pAim)
		m_pAim->Reset();
}

