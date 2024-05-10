#include "stdafx.h"
#include "Image_Structure.h"
#include "BmpMgr.h"

CImage_Structure::CImage_Structure()
{
}


CImage_Structure::~CImage_Structure()
{
	DeleteObject(SelectObject(m_hMemDC, m_OldMap));
	DeleteDC(m_hMemDC);
}

void CImage_Structure::Initialize(CObj * _pObj)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Structure.bmp", L"Structure");
	m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Structure");
	m_pOwner = _pObj;


	m_fCX = 70.0f;
	m_fCY = 20.0f;

	HDC m_DC = GetDC(g_hWnd);

	m_hMemDC = CreateCompatibleDC(m_DC);
	HBITMAP m_hBitmap = CreateCompatibleBitmap(m_DC, 70, 20);
	m_OldMap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	DeleteDC(m_DC);

	BitBlt(m_hMemDC, 0, 0, 70, 20, m_hCurrDC, 0, 0, SRCCOPY);
}

void CImage_Structure::Update(void)
{

}

void CImage_Structure::LateUpdate(void)
{

}

void CImage_Structure::Render(HDC _hDC)
{
	float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
	float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();



	GdiTransparentBlt(_hDC,
		(int)((m_pPos->fX - (m_fCX * 0.5f)) + fScrollX), // 복사받을 x위치의 좌표
		(int)((m_pPos->fY - (m_fCY * 0.5f)) + fScrollY), // 복사 받을 y위치의 좌표)
		(int)m_fCX, // 복사 받을 가로 길이
		m_fCY, // 복사 받을 세로 길이
		m_hMemDC,	// 복사할 비트맵 이미지 dc
		0,		// 비트맵을 출력할 시작 x좌표
		0,		// 비트맵을 출력할 시작 y좌표
		(int)m_fCX, // 복사할 비트맵의 가로 사이즈
		(int)m_fCY,// 복사할 비트맵의 세로 사이즈
		(RGB(128, 128, 192))); //제거하고자 하는 색상
}

void CImage_Structure::Set_Size(void)
{

}

void CImage_Structure::Reset(void)
{

}

void CImage_Structure::Delete_Structure(CMyVector2 _vExplosion)
{
	int iExplosionX = (int)_vExplosion.fX - m_pPos->fX;
	int iExplosionY = (int)_vExplosion.fY - m_pPos->fY;

	int iPixelX = 0;
	int iPixelY = 0;

	bool bMapDelete = false;

	COLORREF PixelColor;
	COLORREF ChangeColor = RGB(128, 128, 192);

	int fLength = int(_vExplosion.fCX * 0.5f);

	for (int x = 0; _vExplosion.fCX > x; ++x)
	{
		for (int y = 0; _vExplosion.fCX > y; ++y)
		{
			iPixelX = (iExplosionX - fLength + x);
			iPixelY = (iExplosionY - fLength + y);

			if (iPixelX >= 0 && iPixelY >= 0)
			{
				if (sqrt(pow(iPixelX - iExplosionX, 2) + pow(iPixelY - iExplosionY, 2)) < fLength)
				{
					SetPixel(m_hMemDC, iPixelX, iPixelY, ChangeColor);
				}
			}
		}
	}


}
