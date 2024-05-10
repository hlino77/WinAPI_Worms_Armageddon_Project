#include "stdafx.h"
#include "Obj_Cloud.h"
#include "Template.h"
#include "Define.h"
#include "Sprite_Cloud.h"
#include "GameMgr.h"

CObj_Cloud::CObj_Cloud()
	:m_pSprite(nullptr)
{
}


CObj_Cloud::~CObj_Cloud()
{
	Release();
}

void CObj_Cloud::Initialize(void)
{
	m_ObjType = OBJ_TYPE::CLOUD;
	
	m_pMover = new CMover;
	m_pMover->Initialize(&m_vPos);
	m_pMover->Set_Gravity(0.0f);
	m_pMover->Set_Mass(0.1f);

	m_WindDir = CGameMgr::Get_Inst()->Get_WindDir();
	m_iWindSpeed = CGameMgr::Get_Inst()->Get_WindSpeed();

	Set_CloudType();
	Set_Speed();
	Set_Pos();

	//스프라이트
	m_pSprite = new CSprite_Cloud;
	m_pSprite->Initialize(this);


	//테스트
	
}

void CObj_Cloud::Update(void)
{
	switch (m_WindDir)
	{
	case WIND_DIR::LEFT:
		m_pMover->AddForce(CMyVector2(-1.0f, 0.0f));
		break;
	case WIND_DIR::MIDDLE:
		m_pMover->Brake(0.98f);
		break;
	case WIND_DIR::RIGHT:
		m_pMover->AddForce(CMyVector2(1.0f, 0.0f));
		break;
	}

	m_pMover->Update();
	m_pSprite->Update();
}

void CObj_Cloud::LateUpdate(void)
{
	m_pMover->LateUpdate();
	
	MapOut();

	m_pSprite->LateUpdate();

	if (m_WindDir != CGameMgr::Get_Inst()->Get_WindDir())
	{
		m_WindDir = CGameMgr::Get_Inst()->Get_WindDir();
		Set_Speed();
	}

	if (m_iWindSpeed != CGameMgr::Get_Inst()->Get_WindSpeed())
	{
		m_iWindSpeed = CGameMgr::Get_Inst()->Get_WindSpeed();
		Set_Speed();
	}
}

void CObj_Cloud::Release(void)
{
	Safe_Delete(m_pMover);
	Safe_Delete(m_pSprite);
}

void CObj_Cloud::Render(HDC _hDC)
{
	RECT&	CameraRect = CCameraMgr::Get_Inst()->Get_CameraRect();
	float	fCX = m_vPos.fCX * 0.5f;


	if (m_vPos.fX < CameraRect.left - fCX || m_vPos.fX > CameraRect.right + fCX)
	{
		return;
	}
	else
	{
		m_pSprite->Render(_hDC);
	}
}

void CObj_Cloud::MapOut(void)
{
	if (m_vPos.fX + m_vPos.fCX * 0.5f < -10)
	{
		Reset_Cloud();
		m_vPos.fX = 4000 + m_vPos.fCX * 0.5f;
	}
	else if (m_vPos.fX - m_vPos.fCX * 0.5f > 4010)
	{
		Reset_Cloud();
		m_vPos.fX = 0 - m_vPos.fCX * 0.5f;
	}
}

void CObj_Cloud::Set_CloudType(void)
{
	int iType = rand() % 3;

	switch (iType)
	{
	case 0:
		m_CloudType = CLOUD_TYPE::BLACK;
		m_vPos.fCX = 160.0f;
		m_vPos.fCY = 160.0f;
		break;
	case 1:
		m_CloudType = CLOUD_TYPE::NORMAL;
		m_vPos.fCX = 128.0f;
		m_vPos.fCY = 128.0f;
		break;
	case 2:
		m_CloudType = CLOUD_TYPE::SMALL;
		m_vPos.fCX = 60.0f;
		m_vPos.fCY = 60.0f;
		break;

	}
}

void CObj_Cloud::Set_Speed(void)
{

	int iSpeed = rand() % 4 + 1;
	float fSpeed = (iSpeed * 0.07f * m_iWindSpeed) * CGameMgr::Get_Inst()->Get_WindSpeed();

	m_pMover->Set_MaxVelocity(fSpeed);

}

void CObj_Cloud::Set_Pos(void)
{
	int iX = rand() % 4000;
	int iY = rand() % 100 + 430;
	
	m_vPos.fX = (float)iX;
	m_vPos.fY = (float)iY;
}

void CObj_Cloud::Reset_Cloud(void)
{
	Set_CloudType();
	Set_Speed();
}
