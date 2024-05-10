#include "stdafx.h"
#include "Button_Net.h"
#include "BmpMgr.h"


CButton_Net::CButton_Net()
{
}


CButton_Net::~CButton_Net()
{
	Release();
}

void CButton_Net::Initialize(POINT * _pMouse)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/MainMenu/Net.bmp", L"Net");
	m_Button = CBmpMgr::Get_Instance()->Find_Image(L"Net");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/MainMenu/Border.bmp", L"Border");
	m_Border = CBmpMgr::Get_Instance()->Find_Image(L"Border");

	m_vPos.fX = 460.0;
	m_vPos.fY =	500.0f;
	m_vPos.fCX = 240.0f;
	m_vPos.fCY = 150.0f;

	m_pMouse = _pMouse;
}

void CButton_Net::Update(void)
{
	MouseUpdate();
}

void CButton_Net::LateUpdate(void)
{
}

void CButton_Net::Release(void)
{
}

void CButton_Net::Render(HDC _hDC)
{
	BitBlt(_hDC,
		m_vPos.fX, // ������� x��ġ�� ��ǥ
		m_vPos.fY, // ���� ���� y��ġ�� ��ǥ)
		m_vPos.fCX, // ���� ���� ���� ����
		m_vPos.fCY, // ���� ���� ���� ����
		m_Button,	// ������ ��Ʈ�� �̹��� dc
		0,		// ��Ʈ���� ����� ���� x��ǥ
		0,		// ��Ʈ���� ����� ���� y��ǥ
		SRCCOPY); //�����ϰ��� �ϴ� ����

	if (m_bMouseIn)
	{
		GdiTransparentBlt(_hDC,
			m_vPos.fX, // ������� x��ġ�� ��ǥ
			m_vPos.fY, // ���� ���� y��ġ�� ��ǥ)
			m_vPos.fCX, // ���� ���� ���� ����
			m_vPos.fCY, // ���� ���� ���� ����
			m_Border,	// ������ ��Ʈ�� �̹��� dc
			0,		// ��Ʈ���� ����� ���� x��ǥ
			0,		// ��Ʈ���� ����� ���� y��ǥ
			m_vPos.fCX, // ������ ��Ʈ���� ���� ������
			m_vPos.fCY,// ������ ��Ʈ���� ���� ������
			RGB(0, 0, 0)); //�����ϰ��� �ϴ� ����
	}
}
