#include "stdafx.h"
#include "Image_Worm_Flying.h"
#include "BmpMgr.h"

CImage_Worm_Flying::CImage_Worm_Flying()
{
}


CImage_Worm_Flying::~CImage_Worm_Flying()
{
}

void CImage_Worm_Flying::Initialize(CObj * _pObj)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Fly/FlyLeft.bmp", L"FlyLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Fly/FlyRight.bmp", L"FlyRight");



	m_fAngle = 0.0f;
	m_fLength = 0.0f;
	m_iCurr = 0;
	m_iMax = 32;

	m_pOwner = _pObj;

	Set_Size();
	Set_Angle();
}

void CImage_Worm_Flying::Update(void)
{
	

	

}

void CImage_Worm_Flying::LateUpdate(void)
{
	Set_Angle();
	Set_Dir();

	m_iCurr = (int)(m_fAngle / 5.625f);
	if (m_iCurr >= m_iMax)
		m_iCurr = m_iMax - 1;
}

void CImage_Worm_Flying::Render(HDC _hDC)
{
	float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
	float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();


	GdiTransparentBlt(_hDC,
		(int)((m_pOwner->Get_Pos().fX - (m_pOwner->Get_Pos().fCX * 0.5f)) + fScrollX), // 복사받을 x위치의 좌표
		(int)((m_pOwner->Get_Pos().fY - (m_pOwner->Get_Pos().fCY * 0.5f)) + fScrollY), // 복사 받을 y위치의 좌표)
		(int)m_fCX, // 복사 받을 가로 길이
		(int)m_fCY, // 복사 받을 세로 길이
		m_hCurrDC,	// 복사할 비트맵 이미지 dc
		0,		// 비트맵을 출력할 시작 x좌표
		(int)(m_iCurr * m_fCY),		// 비트맵을 출력할 시작 y좌표
		(int)m_fCX, // 복사할 비트맵의 가로 사이즈
		(int)m_fCY,// 복사할 비트맵의 세로 사이즈
		(RGB(128, 128, 192))); //제거하고자 하는 색상
}

void CImage_Worm_Flying::Set_Size(void)
{
	m_fCX = 60.0f;
	m_fCY = 60.0f;
}

void CImage_Worm_Flying::Reset(void)
{
}

void CImage_Worm_Flying::Set_Dir(void)
{

	if (m_pOwner->Get_ObjDir() == OBJ_DIR::LEFT)
	{
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"FlyLeft");

		if (m_fAngle > 180)
		{
			m_fAngle = 360 - m_fAngle;
		}
	}
	else
	{
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"FlyRight");
	}
	
}
