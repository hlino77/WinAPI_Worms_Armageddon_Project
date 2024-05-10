#include "stdafx.h"
#include "Image_Donkey.h"
#include "BmpMgr.h"


CImage_Donkey::CImage_Donkey()
{
}


CImage_Donkey::~CImage_Donkey()
{
}

void CImage_Donkey::Initialize(CObj * _pObj)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Donkey.bmp", L"Donkey");
	m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Donkey");

	m_fAngle = 0.0f;
	m_fLength = 0.0f;
	m_iCurr = 0;
	m_iMax = 0;

	m_pOwner = _pObj;


	Set_Size();
}

void CImage_Donkey::Update(void)
{
}

void CImage_Donkey::LateUpdate(void)
{
}

void CImage_Donkey::Render(HDC _hDC)
{
	float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
	float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();


	GdiTransparentBlt(_hDC,
		(int)((m_pOwner->Get_Pos().fX - (m_pOwner->Get_Pos().fCX * 0.5f)) + fScrollX), // ������� x��ġ�� ��ǥ
		(int)((m_pOwner->Get_Pos().fY - 73.0f - (m_pOwner->Get_Pos().fCY * 0.5f)) + fScrollY), // ���� ���� y��ġ�� ��ǥ)
		(int)m_fCX, // ���� ���� ���� ����
		(int)m_fCY, // ���� ���� ���� ����
		m_hCurrDC,	// ������ ��Ʈ�� �̹��� dc
		0,		// ��Ʈ���� ����� ���� x��ǥ
		(int)(m_iCurr * m_fCY),		// ��Ʈ���� ����� ���� y��ǥ
		(int)m_fCX, // ������ ��Ʈ���� ���� ������
		(int)m_fCY,// ������ ��Ʈ���� ���� ������
		(RGB(192, 192, 128))); //�����ϰ��� �ϴ� ����
}

void CImage_Donkey::Set_Size(void)
{
	m_fCX = 158.0f;
	m_fCY = 147.0f;
}

void CImage_Donkey::Reset(void)
{
}
