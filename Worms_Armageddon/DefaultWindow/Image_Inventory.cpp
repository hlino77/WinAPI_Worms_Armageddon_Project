#include "stdafx.h"
#include "Image_Inventory.h"
#include "BmpMgr.h"

CImage_Inventory::CImage_Inventory()
{
}


CImage_Inventory::~CImage_Inventory()
{
}

void CImage_Inventory::Initialize(CObj * _pObj)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Map/WeaponIcons/Inventory.bmp", L"Inventory");
	m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Inventory");

	m_pOwner = _pObj;


	m_fCX = 180.0f;
	m_fCY = 380.0f;
}

void CImage_Inventory::Update(void)
{
}

void CImage_Inventory::LateUpdate(void)
{
}

void CImage_Inventory::Render(HDC _hDC)
{
	GdiTransparentBlt(_hDC,
		(int)(m_pPos->fX), // ������� x��ġ�� ��ǥ
		(int)(m_pPos->fY), // ���� ���� y��ġ�� ��ǥ)
		(int)m_fCX, // ���� ���� ���� ����
		m_fCY, // ���� ���� ���� ����
		m_hCurrDC,	// ������ ��Ʈ�� �̹��� dc
		0,		// ��Ʈ���� ����� ���� x��ǥ
		0,		// ��Ʈ���� ����� ���� y��ǥ
		(int)m_fCX, // ������ ��Ʈ���� ���� ������
		(int)m_fCY,// ������ ��Ʈ���� ���� ������
		(RGB(128, 128, 192))); //�����ϰ��� �ϴ� ����
}

void CImage_Inventory::Set_Size(void)
{
}

void CImage_Inventory::Reset(void)
{
}
