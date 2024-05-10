#include "stdafx.h"
#include "Image_Font.h"
#include "BmpMgr.h"

CImage_Font::CImage_Font()
{
}


CImage_Font::~CImage_Font()
{
}

void CImage_Font::Initialize(CObj * _pObj)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Font/Font1.bmp", L"Font1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Font/Font2.bmp", L"Font2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Font/Font3.bmp", L"Font3");
	m_pOwner = _pObj;


	m_fCX = 10.0f;
	m_fCY = 16.0f;
}

void CImage_Font::Update(void)
{
}

void CImage_Font::LateUpdate(void)
{
}

void CImage_Font::Render(HDC _hDC)
{
}

void CImage_Font::Set_Size(void)
{
}

void CImage_Font::Reset(void)
{
}

void CImage_Font::Render_Num(HDC _hDC, int _iNum, int _iFont, CMyVector2 _pInfo)
{
	m_iCurr = _iNum + 52;

	switch (_iFont)
	{
	case 1:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Font1");
		break;
	case 2:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Font2");
		break;
	case 3:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Font3");
		break;
	}


	CMyVector2& vPos = _pInfo;


	float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
	float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();



	GdiTransparentBlt(_hDC,
		(int)((vPos.fX - (m_fCX * 0.5f)) + fScrollX), // ������� x��ġ�� ��ǥ
		(int)((vPos.fY - (m_fCY * 0.5f)) + fScrollY), // ���� ���� y��ġ�� ��ǥ)
		m_fCX, // ���� ���� ���� ����
		m_fCY, // ���� ���� ���� ����
		m_hCurrDC,	// ������ ��Ʈ�� �̹��� dc
		0,		// ��Ʈ���� ����� ���� x��ǥ
		m_iCurr * m_fCY,		// ��Ʈ���� ����� ���� y��ǥ
		(int)m_fCX, // ������ ��Ʈ���� ���� ������
		(int)m_fCY,// ������ ��Ʈ���� ���� ������
		(RGB(0, 0, 0))); //�����ϰ��� �ϴ� ����
}
