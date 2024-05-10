#include "stdafx.h"
#include "Image_HpBox.h"
#include "BmpMgr.h"

CImage_HpBox::CImage_HpBox()
{
}


CImage_HpBox::~CImage_HpBox()
{
}

void CImage_HpBox::Initialize(CObj * _pObj)
{

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Font/HpBox.bmp", L"HpBox");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Font/HpBox2.bmp", L"HpBox2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Font/HpBox3.bmp", L"HpBox3");
	m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"HpBox");
	m_pOwner = _pObj;


	m_fCX = 21.0f;
	m_fCY = 19.0f;
}

void CImage_HpBox::Update(void)
{
}

void CImage_HpBox::LateUpdate(void)
{
}

void CImage_HpBox::Render(HDC _hDC)
{
}

void CImage_HpBox::Set_Size(void)
{
}

void CImage_HpBox::Reset(void)
{
}


void CImage_HpBox::Size_Render(HDC _hDC, CMyVector2 _pInfo, int _iSize)
{
	CMyVector2& vPos = _pInfo;


	float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
	float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();


	if (_iSize == 2)
	{
		m_fCX = 26.0f;
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"HpBox2");
	}
	else
	{
		m_fCX = 36.0f;
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"HpBox3");
	}


	GdiTransparentBlt(_hDC,
		(int)((vPos.fX - (vPos.fCX * 0.5f)) + fScrollX), // 복사받을 x위치의 좌표
		(int)((vPos.fY - (m_fCY * 0.5f)) + fScrollY), // 복사 받을 y위치의 좌표)
		(int)m_fCX, // 복사 받을 가로 길이
		m_fCY, // 복사 받을 세로 길이
		m_hCurrDC,	// 복사할 비트맵 이미지 dc
		0,		// 비트맵을 출력할 시작 x좌표
		0,		// 비트맵을 출력할 시작 y좌표
		(int)m_fCX, // 복사할 비트맵의 가로 사이즈
		(int)m_fCY,// 복사할 비트맵의 세로 사이즈
		(RGB(128, 128, 192))); //제거하고자 하는 색상


}
