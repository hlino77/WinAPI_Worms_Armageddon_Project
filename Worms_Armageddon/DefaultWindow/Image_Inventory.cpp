#include "stdafx.h"
#include "Image_Inventory.h"
#include "BmpMgr.h"

CImage_Inventory::CImage_Inventory()
{
}


CImage_Inventory::~CImage_Inventory()
{
}

void CImage_Inventory::Initialize(CObj * _pObj)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Map/WeaponIcons/Inventory.bmp", L"Inventory");
	m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Inventory");

	m_pOwner = _pObj;


	m_fCX = 180.0f;
	m_fCY = 380.0f;
}

void CImage_Inventory::Update(void)
{
}

void CImage_Inventory::LateUpdate(void)
{
}

void CImage_Inventory::Render(HDC _hDC)
{
	GdiTransparentBlt(_hDC,
		(int)(m_pPos->fX), // 복사받을 x위치의 좌표
		(int)(m_pPos->fY), // 복사 받을 y위치의 좌표)
		(int)m_fCX, // 복사 받을 가로 길이
		m_fCY, // 복사 받을 세로 길이
		m_hCurrDC,	// 복사할 비트맵 이미지 dc
		0,		// 비트맵을 출력할 시작 x좌표
		0,		// 비트맵을 출력할 시작 y좌표
		(int)m_fCX, // 복사할 비트맵의 가로 사이즈
		(int)m_fCY,// 복사할 비트맵의 세로 사이즈
		(RGB(128, 128, 192))); //제거하고자 하는 색상
}

void CImage_Inventory::Set_Size(void)
{
}

void CImage_Inventory::Reset(void)
{
}
