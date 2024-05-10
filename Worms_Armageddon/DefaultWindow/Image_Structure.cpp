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
		(int)((m_pPos->fX - (m_fCX * 0.5f)) + fScrollX), // ������� x��ġ�� ��ǥ
		(int)((m_pPos->fY - (m_fCY * 0.5f)) + fScrollY), // ���� ���� y��ġ�� ��ǥ)
		(int)m_fCX, // ���� ���� ���� ����
		m_fCY, // ���� ���� ���� ����
		m_hMemDC,	// ������ ��Ʈ�� �̹��� dc
		0,		// ��Ʈ���� ����� ���� x��ǥ
		0,		// ��Ʈ���� ����� ���� y��ǥ
		(int)m_fCX, // ������ ��Ʈ���� ���� ������
		(int)m_fCY,// ������ ��Ʈ���� ���� ������
		(RGB(128, 128, 192))); //�����ϰ��� �ϴ� ����
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
