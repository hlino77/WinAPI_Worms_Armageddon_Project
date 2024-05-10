#include "stdafx.h"
#include "Image_Jet.h"
#include "BmpMgr.h"

CImage_Jet::CImage_Jet()
{
}


CImage_Jet::~CImage_Jet()
{
}

void CImage_Jet::Initialize(CObj * _pObj)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/AirJet.bmp", L"AirJet");
	m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"AirJet");

	m_fAngle = 0.0f;
	m_fLength = 0.0f;
	m_iCurr = 0;
	m_iMax = 0;

	m_pOwner = _pObj;


	Set_Size(); 
}

void CImage_Jet::Update(void)
{

}

void CImage_Jet::LateUpdate(void)
{
}

void CImage_Jet::Render(HDC _hDC)
{
	float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
	float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();


	GdiTransparentBlt(_hDC,
		(int)((m_pJetPos->fX - (m_fCX * 0.5f)) + fScrollX), // ������� x��ġ�� ��ǥ
		(int)((m_pJetPos->fY - (m_fCY * 0.5f)) + fScrollY), // ���� ���� y��ġ�� ��ǥ)
		(int)m_fCX, // ���� ���� ���� ����
		(int)m_fCY, // ���� ���� ���� ����
		m_hCurrDC,	// ������ ��Ʈ�� �̹��� dc
		0,		// ��Ʈ���� ����� ���� x��ǥ
		(int)(m_iCurr * m_fCY),		// ��Ʈ���� ����� ���� y��ǥ
		(int)m_fCX, // ������ ��Ʈ���� ���� ������
		(int)m_fCY,// ������ ��Ʈ���� ���� ������
		(RGB(128, 128, 192))); //�����ϰ��� �ϴ� ����
}

void CImage_Jet::Set_Size(void)
{
	m_fCX = 60.0f;
	m_fCY = 60.0f;
}

void CImage_Jet::Reset(void)
{
}
