#include "stdafx.h"
#include "Image_Donkey.h"
#include "BmpMgr.h"


CImage_Donkey::CImage_Donkey()
{
}


CImage_Donkey::~CImage_Donkey()
{
}

void CImage_Donkey::Initialize(CObj * _pObj)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Donkey.bmp", L"Donkey");
	m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Donkey");

	m_fAngle = 0.0f;
	m_fLength = 0.0f;
	m_iCurr = 0;
	m_iMax = 0;

	m_pOwner = _pObj;


	Set_Size();
}

void CImage_Donkey::Update(void)
{
}

void CImage_Donkey::LateUpdate(void)
{
}

void CImage_Donkey::Render(HDC _hDC)
{
	float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
	float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();


	GdiTransparentBlt(_hDC,
		(int)((m_pOwner->Get_Pos().fX - (m_pOwner->Get_Pos().fCX * 0.5f)) + fScrollX), // 복사받을 x위치의 좌표
		(int)((m_pOwner->Get_Pos().fY - 73.0f - (m_pOwner->Get_Pos().fCY * 0.5f)) + fScrollY), // 복사 받을 y위치의 좌표)
		(int)m_fCX, // 복사 받을 가로 길이
		(int)m_fCY, // 복사 받을 세로 길이
		m_hCurrDC,	// 복사할 비트맵 이미지 dc
		0,		// 비트맵을 출력할 시작 x좌표
		(int)(m_iCurr * m_fCY),		// 비트맵을 출력할 시작 y좌표
		(int)m_fCX, // 복사할 비트맵의 가로 사이즈
		(int)m_fCY,// 복사할 비트맵의 세로 사이즈
		(RGB(192, 192, 128))); //제거하고자 하는 색상
}

void CImage_Donkey::Set_Size(void)
{
	m_fCX = 158.0f;
	m_fCY = 147.0f;
}

void CImage_Donkey::Reset(void)
{
}
