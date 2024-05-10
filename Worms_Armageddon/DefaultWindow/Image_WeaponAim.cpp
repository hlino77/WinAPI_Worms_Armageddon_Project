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
			(int)(((fOwnerX + fX) - m_fCX * 0.5f) + fScrollX), // ������� x��ġ�� ��ǥ
			(int)(((fOwnerY + fY) - m_fCY * 0.5f) + fScrollY), // ���� ���� y��ġ�� ��ǥ)
			(int)m_fCX, // ���� ���� ���� ����
			(int)m_fCY, // ���� ���� ���� ����
			m_hCurrDC,	// ������ ��Ʈ�� �̹��� dc
			0,		// ��Ʈ���� ����� ���� x��ǥ
			(int)(m_iCurr * m_fCY),		// ��Ʈ���� ����� ���� y��ǥ
			(int)m_fCX, // ������ ��Ʈ���� ���� ������
			(int)m_fCY,// ������ ��Ʈ���� ���� ������
			(RGB(128, 128, 192))); //�����ϰ��� �ϴ� ����
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
