#include "stdafx.h"
#include "Obj_BackParticle.h"
#include "Sprite_BackPraticle.h"
#include "GameMgr.h"

CObj_BackParticle::CObj_BackParticle()
	:m_fPlusY(0.0f), m_YDelay(0), m_YTime(0)
{
}


CObj_BackParticle::~CObj_BackParticle()
{
	Release();
}

void CObj_BackParticle::Initialize(void)
{
	m_ObjType = OBJ_TYPE::BACKPARTICLE;

	m_pMover = new CMover;
	m_pMover->Initialize(&m_vPos);
	m_pMover->Set_Mass(0.1f);
	m_pMover->Set_Gravity(0.1f);
	
	m_vPos.fCX = 60.0f;
	m_vPos.fCY = 60.0f;
	//스프라이트
	m_pSprite = new CSprite_BackPraticle;
	m_pSprite->Initialize(this);

	Make_Particle();

	

	m_YDelay = 2000.f;
	m_YTime = GetTickCount();


	


	//테스트
	m_WindDir = CGameMgr::Get_Inst()->Get_WindDir();
	m_iWindSpeed = CGameMgr::Get_Inst()->Get_WindSpeed();


}

void CObj_BackParticle::Update(void)
{
	

	switch (m_WindDir)
	{
	case WIND_DIR::LEFT:
		m_pMover->AddForce(CMyVector2(-1.0f,0.0f));
		break;
	case WIND_DIR::MIDDLE:
		m_pMover->BrakeX(0.98f);
		break;
	case WIND_DIR::RIGHT:
		m_pMover->AddForce(CMyVector2(1.0f,0.0f));
		break;
	}
	
	if (m_WindDir == WIND_DIR::LEFT || m_WindDir == WIND_DIR::RIGHT)
	{
		if (m_YTime + m_YDelay < GetTickCount())
		{
			int iTemp = rand() % 2;
			m_fPlusY = iTemp * -0.02f;
			m_YTime = GetTickCount();
		}
		else
		{
			m_pMover->AddForce(CMyVector2(0.0f, m_fPlusY));
		}
	}

	m_pMover->Update();
	m_pSprite->Update();
}

void CObj_BackParticle::LateUpdate(void)
{
	if (m_pMover->Get_Velocity().fY < -0.01f)
		m_pMover->Get_Velocity().Set_fY(-0.01f);

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

void CObj_BackParticle::Release(void)
{
	Safe_Delete(m_pMover);
	Safe_Delete(m_pSprite);
}

void CObj_BackParticle::Render(HDC _hDC)
{
	RECT&	CameraRect = CCameraMgr::Get_Inst()->Get_CameraRect();
	float	fCX = m_vPos.fCX * 0.5f;
	float	fCY = m_vPos.fCY * 0.5f;

	if (m_vPos.fX < CameraRect.left - fCX || m_vPos.fX > CameraRect.right + fCX || m_vPos.fY < CameraRect.top - fCY || m_vPos.fY > CameraRect.bottom + fCY)
	{
		return;
	}
	else
	{
		m_pSprite->Render(_hDC);
	}
}

void CObj_BackParticle::MapOut(void)
{
	if (m_vPos.fX + m_vPos.fCX * 0.5f < -10)
	{
		m_vPos.fX = 4000 + m_vPos.fCX * 0.5f;
		Set_Speed();
	}
	else if (m_vPos.fX - m_vPos.fCX * 0.5f > 4010)
	{
		m_vPos.fX = 0 - m_vPos.fCX * 0.5f;
		Set_Speed();
	}

	if (m_vPos.fY - m_vPos.fCY * 0.5f > 1300)
	{
		Reset_Particle();
	}
}

void CObj_BackParticle::Set_Speed(void)
{
	int iSpeed = rand() % 5 + 5;

	float fSpeed = (iSpeed * 0.3f) * CGameMgr::Get_Inst()->Get_WindSpeed();
	m_pMover->Set_MaxVelocityX(fSpeed);
	m_pMover->Set_MaxVelocityY(iSpeed * 0.3f);
}

void CObj_BackParticle::Set_Pos(void)
{
	int iX = rand() % 4000;
	int iY = rand() % 100 + 430;

	m_vPos.fX = (float)iX;
	m_vPos.fY = (float)iY;
}

void CObj_BackParticle::Set_RandomPos(void)
{
	int iX = rand() % 4000;
	int iY = rand() % 900 + 500;

	m_vPos.fX = (float)iX;
	m_vPos.fY = (float)iY;
}

void CObj_BackParticle::Reset_Particle(void)
{
	Set_Speed();
	Set_Pos();
	m_pSprite->SpriteReset();
}

void CObj_BackParticle::Make_Particle(void)
{
	Set_Speed();
	Set_RandomPos();
	int iTemp = rand() % 128;
	m_pSprite->Set_Curr(iTemp);
}
