#include "stdafx.h"
#include "Image_Holy.h"
#include "BmpMgr.h"
#include "Obj_Projectile.h"

CImage_Holy::CImage_Holy()
{
}


CImage_Holy::~CImage_Holy()
{
}

void CImage_Holy::Initialize(CObj * _pObj)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Holy.bmp", L"Holy");
	m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Holy");

	m_fAngle = 0.0f;
	m_fLength = 0.0f;
	m_iCurr = 0;
	m_iMax = 32;

	m_pOwner = _pObj;
	m_pOwnerAngle = static_cast<CObj_Projectile*>(m_pOwner)->Get_pAngle();

	Set_Size();
	Set_Angle();
}

void CImage_Holy::Update(void)
{
	Set_Angle();

	m_iCurr = (int)(m_fAngle / 11.25f);

	if (m_fAngle == 360.0f)
		m_iCurr = 0;

	if (m_iCurr >= m_iMax)
		m_iCurr = m_iMax - 1;
}

void CImage_Holy::LateUpdate(void)
{
}

void CImage_Holy::Render(HDC _hDC)
{
	float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
	float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();


	GdiTransparentBlt(_hDC,
		(int)((m_pOwner->Get_Pos().fX - (m_pOwner->Get_Pos().fCX * 0.5f)) + fScrollX), // ������� x��ġ�� ��ǥ
		(int)((m_pOwner->Get_Pos().fY - (m_pOwner->Get_Pos().fCY * 0.5f)) + fScrollY), // ���� ���� y��ġ�� ��ǥ)
		(int)m_fCX, // ���� ���� ���� ����
		(int)m_fCY, // ���� ���� ���� ����
		m_hCurrDC,	// ������ ��Ʈ�� �̹��� dc
		0,		// ��Ʈ���� ����� ���� x��ǥ
		(int)(m_iCurr * m_fCY),		// ��Ʈ���� ����� ���� y��ǥ
		(int)m_fCX, // ������ ��Ʈ���� ���� ������
		(int)m_fCY,// ������ ��Ʈ���� ���� ������
		(RGB(128, 128, 192))); //�����ϰ��� �ϴ� ����
}

void CImage_Holy::Set_Size(void)
{
	m_fCX = m_pOwner->Get_Pos().fCX;
	m_fCY = m_pOwner->Get_Pos().fCY;
}

void CImage_Holy::Reset(void)
{
	
}

void CImage_Holy::Set_Angle(void)
{
	m_fAngle = round(*m_pOwnerAngle);
}
