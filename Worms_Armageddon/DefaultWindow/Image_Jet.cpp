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
		(int)((m_pJetPos->fX - (m_fCX * 0.5f)) + fScrollX), // 복사받을 x위치의 좌표
		(int)((m_pJetPos->fY - (m_fCY * 0.5f)) + fScrollY), // 복사 받을 y위치의 좌표)
		(int)m_fCX, // 복사 받을 가로 길이
		(int)m_fCY, // 복사 받을 세로 길이
		m_hCurrDC,	// 복사할 비트맵 이미지 dc
		0,		// 비트맵을 출력할 시작 x좌표
		(int)(m_iCurr * m_fCY),		// 비트맵을 출력할 시작 y좌표
		(int)m_fCX, // 복사할 비트맵의 가로 사이즈
		(int)m_fCY,// 복사할 비트맵의 세로 사이즈
		(RGB(128, 128, 192))); //제거하고자 하는 색상
}

void CImage_Jet::Set_Size(void)
{
	m_fCX = 60.0f;
	m_fCY = 60.0f;
}

void CImage_Jet::Reset(void)
{
}
