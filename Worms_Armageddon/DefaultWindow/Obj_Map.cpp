#include "stdafx.h"
#include "Obj_Map.h"
#include "BmpMgr.h"
#include "CameraMgr.h"
#include "Sprite_Sea.h"
#include "ObjMgr.h"

CObj_Map::CObj_Map()
{
}


CObj_Map::~CObj_Map()
{
	Release();
}

void CObj_Map::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Map/SpongeBob4.bmp", L"MainMap");
	m_hMapDC = CBmpMgr::Get_Instance()->Find_Image(L"MainMap");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Map/BlueWaterBack.bmp", L"BlueWaterBack");
	m_hWaterBackDC = CBmpMgr::Get_Instance()->Find_Image(L"BlueWaterBack");

	

	m_vPos.fCX = 1310.0f;
	m_vPos.fCY = 403.0f;


	m_vecMapInfo.resize(4000 * 1300, false);

	
	//BackDC생성, MainDC 생성
	/*HDC NewDC = GetDC(g_hWnd);
	m_hBackDC = CreateCompatibleDC(NewDC);

	HBITMAP hBackBitMap = CreateCompatibleBitmap(NewDC, 4000, 1300);

	m_BackOldMap = (HBITMAP)SelectObject(m_hBackDC, hBackBitMap);
	DeleteDC(NewDC);*/
	

	Set_BackDC();

	Make_Sea();

	m_fMapX = 1310.0f;
	m_fMapY = 780.0f;

}

void CObj_Map::Update(void)
{
	for (auto& Veciter : m_vecSeaList)
	{
		for (auto& Listiter : Veciter)
		{
			Listiter->Update();
		}
	}
}

void CObj_Map::LateUpdate(void)
{
	for (auto& Veciter : m_vecSeaList)
	{
		for (auto& Listiter : Veciter)
		{
			Listiter->LateUpdate();
		}
	}
}

void CObj_Map::Release(void)
{
	


	for (auto& Veciter : m_vecSeaList)
	{
		for (auto& Listiter : Veciter)
		{
			Safe_Delete(Listiter);
		}
		Veciter.clear();
	}

}

void CObj_Map::Render(HDC _hDC)
{
	float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
	float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();


	BitBlt(_hDC, fScrollX, 1125 + fScrollY, 4000, 400, m_hWaterBackDC, 0, 0, SRCCOPY);

	for (int i = 0; 2 > i; ++i)
	{
		for (auto& iter : m_vecSeaList[i])
		{
			iter->Render(_hDC);
		}
	}

	

	GdiTransparentBlt(_hDC,
		1310 + fScrollX, // 복사받을 x위치의 좌표
		780 + fScrollY, // 복사 받을 y위치의 좌표)
		m_vPos.fCX, // 복사 받을 가로 길이
		m_vPos.fCY, // 복사 받을 세로 길이
		m_hMapDC,	// 복사할 비트맵 이미지 dc
		0,		// 비트맵을 출력할 시작 x좌표
		0,		// 비트맵을 출력할 시작 y좌표
		m_vPos.fCX, // 복사할 비트맵의 가로 사이즈
		m_vPos.fCY,// 복사할 비트맵의 세로 사이즈
		RGB(128, 128, 192)); //제거하고자 하는 색상





	BitBlt(_hDC, fScrollX, 1125 + 40 + fScrollY, 4000, 400, m_hWaterBackDC, 0, 0, SRCCOPY);


	for (int i = 2; 4 > i; ++i)
	{
		for (auto& iter : m_vecSeaList[i])
		{
			iter->Render(_hDC);
		}
	}

}




void CObj_Map::Delete_Map(CMyVector2 _vExplosion)
{
	int iExplosionX = (int)_vExplosion.fX;
	int iExplosionY = (int)_vExplosion.fY;

	int iPixelX = 0;
	int iPixelY = 0;

	COLORREF PixelColor;
	COLORREF ChangeColor = RGB(128, 128, 192);

	int fLength = int(_vExplosion.fCX * 0.5f);

	for (int x = 0; _vExplosion.fCX > x; ++x)
	{
		for (int y = 0; _vExplosion.fCX > y; ++y)
		{
			iPixelX = (iExplosionX - fLength + x);
			iPixelY = (iExplosionY - fLength + y);

			if (m_vecMapInfo[iPixelX + iPixelY * 4000] == true)
			{
				if (sqrt(pow(iPixelX - iExplosionX, 2) + pow(iPixelY - iExplosionY, 2)) < fLength)
				{
					SetPixel(m_hMapDC, iPixelX - MAPPOSX, iPixelY - MAPPOSY, ChangeColor);
					m_vecMapInfo[iPixelX + iPixelY * 4000] = false;
				}
			}
		}
	}

	CObjMgr::Get_Inst()->Delete_Structure(_vExplosion);

}

void CObj_Map::Make_Sea(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Map/BlueWater.bmp", L"BlueWater");

	m_vecSeaList.resize(4, list<CSprite*>());
	
	CSprite* pNewSea = nullptr;

	int iY = 1100;
	int iX = 0;
	int iCurr = 0;

	for (int y = 0; 4 > y; ++y)
	{
		iX = (rand() % 20) * 12;
		iCurr = rand() % 150;
		for (int x = 0; 17 > x; ++x)
		{
			pNewSea = new CSprite_Sea;
			pNewSea->Initialize(nullptr);
			pNewSea->Set_Curr(iCurr);
			static_cast<CSprite_Sea*>(pNewSea)->Set_Pos(CMyVector2((x * 256) - iX, (y * 20) + iY));
			m_vecSeaList[y].push_back(pNewSea);
			pNewSea = nullptr;
		}
	}

}

void CObj_Map::Set_BackDC(void)
{
	COLORREF Exception = RGB(128, 128, 192);
	COLORREF PixelColor;

	for (int x = 0; (int)m_vPos.fCX > x; ++x)
	{
		for (int y = 0; (int)m_vPos.fCY > y; ++y)
		{
			PixelColor = GetPixel(m_hMapDC, x, y);

			if (PixelColor != Exception)
			{
				m_vecMapInfo[(x + MAPPOSX) + ((y + MAPPOSY) * 4000)] = true;
			}
		}
	}

}
