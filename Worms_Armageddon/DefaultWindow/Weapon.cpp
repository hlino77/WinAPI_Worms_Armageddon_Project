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
			(int)((fX - fCX * 0.5f) + fScrollX), // ������� x��ġ�� ��ǥ
			(int)((fY - fCY * 0.5f) + fScrollY), // ���� ���� y��ġ�� ��ǥ)
			(int)fCX, // ���� ���� ���� ����
			(int)fCY, // ���� ���� ���� ����
			m_hGageDC,	// ������ ��Ʈ�� �̹��� dc
			0,		// ��Ʈ���� ����� ���� x��ǥ
			(int)((iLength - i) * fCY),		// ��Ʈ���� ����� ���� y��ǥ
			(int)fCX, // ������ ��Ʈ���� ���� ������
			(int)fCY,// ������ ��Ʈ���� ���� ������
			(RGB(128, 128, 192))); //�����ϰ��� �ϴ� ����
	}

	m_pAim->Render(_hDC);
}
void CWeapon::Reset_Aim(void)
{
	m_fAngle = 90.0f;
	if (m_pAim)
		m_pAim->Reset();
}

