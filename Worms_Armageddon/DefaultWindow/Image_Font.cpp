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
		(int)((vPos.fX - (m_fCX * 0.5f)) + fScrollX), // 복사받을 x위치의 좌표
		(int)((vPos.fY - (m_fCY * 0.5f)) + fScrollY), // 복사 받을 y위치의 좌표)
		m_fCX, // 복사 받을 가로 길이
		m_fCY, // 복사 받을 세로 길이
		m_hCurrDC,	// 복사할 비트맵 이미지 dc
		0,		// 비트맵을 출력할 시작 x좌표
		m_iCurr * m_fCY,		// 비트맵을 출력할 시작 y좌표
		(int)m_fCX, // 복사할 비트맵의 가로 사이즈
		(int)m_fCY,// 복사할 비트맵의 세로 사이즈
		(RGB(0, 0, 0))); //제거하고자 하는 색상
}
