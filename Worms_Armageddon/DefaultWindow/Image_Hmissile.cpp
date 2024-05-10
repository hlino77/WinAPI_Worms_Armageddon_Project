#include "stdafx.h"
#include "Image_Hmissile.h"
#include "BmpMgr.h"
#include "Obj_Projectile.h"
#include "Obj_Projectile_Hmissile.h"

CImage_Hmissile::CImage_Hmissile()
{
}


CImage_Hmissile::~CImage_Hmissile()
{
}

void CImage_Hmissile::Initialize(CObj * _pObj)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Hmissile1.bmp", L"Hmissile1");
	m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Hmissile1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Hmissile2.bmp", L"Hmissile2");

	m_fAngle = 0.0f;
	m_fLength = 0.0f;
	m_iCurr = 0;
	m_iMax = 32;

	m_pOwner = _pObj;

	m_pOwnerAngle = static_cast<CObj_Projectile*>(m_pOwner)->Get_pAngle();

	m_pOwnerHmissile = static_cast<CObj_Projectile_Hmissile*>(m_pOwner)->Get_pHmissileType();


	Set_Size();
	Set_Angle();

	m_bChange = false;
}

void CImage_Hmissile::Update(void)
{
	Set_Angle();

	m_iCurr = (int)(m_fAngle / 11.25f);

	if (m_fAngle == 360.0f)
		m_iCurr = 0;

	if (m_iCurr >= m_iMax)
		m_iCurr = m_iMax - 1;
}

void CImage_Hmissile::LateUpdate(void)
{
	if (m_bChange == false && * m_pOwnerHmissile == HMISSILE_TYPE::H2)
	{
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Hmissile2");
	}
}

void CImage_Hmissile::Render(HDC _hDC)
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
		(RGB(192, 192, 128))); //제거하고자 하는 색상
}

void CImage_Hmissile::Set_Size(void)
{
	m_fCX = m_pOwner->Get_Pos().fCX;
	m_fCY = m_pOwner->Get_Pos().fCY;
}

void CImage_Hmissile::Reset(void)
{
}

void CImage_Hmissile::Set_Angle(void)
{
	m_fAngle = round(*m_pOwnerAngle);
}
