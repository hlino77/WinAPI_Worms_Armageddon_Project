#include "stdafx.h"
#include "Button_Single.h"
#include "BmpMgr.h"

CButton_Single::CButton_Single()
{
}


CButton_Single::~CButton_Single()
{
	Release();
}

void CButton_Single::Initialize(POINT * _pMouse)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/MainMenu/Single.bmp", L"SingleButton");
	m_Button = CBmpMgr::Get_Instance()->Find_Image(L"SingleButton");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/MainMenu/Border.bmp", L"Border");
	m_Border = CBmpMgr::Get_Instance()->Find_Image(L"Border");

	m_vPos.fX = 460.0f;
	m_vPos.fY = 300.0f;
	m_vPos.fCX = 240.0f;
	m_vPos.fCY = 150.0f;

	m_pMouse = _pMouse;


}

void CButton_Single::Update(void)
{
	MouseUpdate();
}

void CButton_Single::LateUpdate(void)
{

}

void CButton_Single::Release(void)
{

}

void CButton_Single::Render(HDC _hDC)
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
