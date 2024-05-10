#include "stdafx.h"
#include "State_Worm_Slide.h"
#include "EffectMgr.h"
#include "Sprite_Worm_Slide.h"
#include "SoundMgr.h"

CState_Worm_Slide::CState_Worm_Slide()
{
}


CState_Worm_Slide::~CState_Worm_Slide()
{
}

void CState_Worm_Slide::Initialize(CObj * _pOwner)
{
	Set_Owner(_pOwner);

	m_fCenterX = 7.0f;
	m_fLeftX = 4.0f;
	m_fRightX = 10.0f;
	m_fLeftY = -1.0f;
	m_fRightY = -1.0f;
	m_fBottomLength = 8.0f;

	m_SmokeDelay = 200;
	m_PrevSmokeTime = 0;
}

void CState_Worm_Slide::Update(void)
{
	m_pOwnerMover->Update();
}

void CState_Worm_Slide::LateUpdate(void)
{
	if (*m_pBombCollision)
		BombCollision();

	if (*m_pMapCollision)
		Worm_Map_Collision();
	else
	{
		*m_pLeftAngle = 0.0f;
		*m_pRightAngle = 0.0f;
	}

	m_pOwnerMover->LateUpdate();
	

}

void CState_Worm_Slide::Release(void)
{

}

void CState_Worm_Slide::Key_Input(void)
{
}


void CState_Worm_Slide::Worm_Map_Collision(void)
{
	float fX = m_pBottom->fX - m_pClosest->fX;
	float fY = m_pBottom->fY - m_pClosest->fY;
	float fLength = sqrt(fX * fX + fY * fY);



	for (int y = 0; m_pBottom->fCY > y; ++y)
	{
		for (int x = 0; m_pBottom->fCX > x; ++x)
		{

			if ((*m_pBoundingBox)[(UINT)(x + (y * m_pBottom->fCX))] == true)
			{
				if (x == m_fLeftX && m_fLeftY == -1.0f)
				{
					m_fLeftY = (float)y;

				}
				else if (x == m_fRightX && m_fRightY == -1.0f)
				{
					m_fRightY = (float)y;
				}
				else if (x == m_fCenterX && m_fCenterY == -1.0f)
				{
					m_fCenterY = (float)y;
				}
			}
		}
	}



	if (m_fLeftY == 0.0f && m_pOwnerMover->Get_Velocity().fX < 0)
	{
		m_pOwnerMover->Brake(0.8f);
		m_pOwnerMover->Get_Velocity().Set_fX(m_pOwnerMover->Get_Velocity().fX * -1);
		CSoundMgr::Get_Instance()->Random_WormHit();
	}

	if (m_fRightY == 0.0f && m_pOwnerMover->Get_Velocity().fX > 0)
	{
		m_pOwnerMover->Brake(0.8f);
		m_pOwnerMover->Get_Velocity().Set_fX(m_pOwnerMover->Get_Velocity().fX * -1);
		CSoundMgr::Get_Instance()->Random_WormHit();
	}


	if (m_fCenterY >= 0.0f && m_fCenterY < 7.0f && m_pOwnerMover->Get_Velocity().fY < 0)
	{
		m_pOwnerMover->Brake(0.8f);
		m_pOwnerMover->Get_Velocity().Set_fY(m_pOwnerMover->Get_Velocity().fY * -1);
		CSoundMgr::Get_Instance()->Random_WormHit();
	}

	if (m_fCenterY >= 7.0f && m_fCenterY < 15.0f && m_pOwnerMover->Get_Velocity().fY > 0)
	{
		m_pBottom->fY = (int)(m_pBottom->fY + (m_fCenterY - 14.0f));
		m_pPos->fY = m_pBottom->fY - m_fBottomLength;

		CSoundMgr::Get_Instance()->Random_WormOOFF();

		if (m_pOwnerMover->Get_Velocity().fY > 0)
			m_pOwnerMover->StopY();

		Set_BottomAngle();

		m_pOwnerMover->BrakeX(0.9f);
		Slide_Smoke();

		if (fabs(m_pOwnerMover->Get_Velocity().fX) < 0.1f)
			static_cast<CSprite_Worm_Slide*>(m_pAnimator->Get_CurrSprite())->Set_bSlideEnd();

		if (static_cast<CSprite_Worm_Slide*>(m_pAnimator->Get_CurrSprite())->Is_End())
		{
			*m_pWormState = WORM_STATE::IDLE;
			*m_pAction = false;
		}
			
	}


	if (*m_pRightAngle < -75.0f)
		*m_pRightMove = false;
	else
		*m_pRightMove = true;

	if (*m_pLeftAngle > 75.0f)
		*m_pLeftMove = false;
	else
		*m_pLeftMove = true;




	//¸®¼Â
	*m_pMapCollision = false;
	m_pClosest->fX = 0.0f;
	m_pClosest->fY = 0.0f;


	m_fLeftY = -1.0f;
	m_fRightY = -1.0f;
	m_fCenterY = -1.0f;

	fill(m_pBoundingBox->begin(), m_pBoundingBox->end(), false);
}

void CState_Worm_Slide::Set_BottomAngle(void)
{
	if (m_fLeftY == -1.0f)
		m_fLeftY = m_pBottom->fCY;

	if (m_fRightY == -1.0f)
		m_fRightY = m_pBottom->fCY;

	float fLeftRadian = Get_Radian(m_fCenterX - m_fLeftX, m_fCenterY - m_fLeftY);
	*m_pLeftAngle = RAD2DEG(fLeftRadian);

	if (m_fCenterY - m_fLeftY < 0)
		*m_pLeftAngle *= -1.0f;

	float fRightRadian = Get_Radian(m_fRightX - m_fCenterX, m_fRightY - m_fCenterY);
	*m_pRightAngle = RAD2DEG(fRightRadian);

	if (m_fRightY - m_fCenterY < 0)
		*m_pRightAngle *= -1.0f;
}

void CState_Worm_Slide::Slide_Smoke(void)
{
	if (m_PrevSmokeTime + m_SmokeDelay < GetTickCount())
	{
		CEffectMgr::Get_Inst()->Get_SlideSmoke(*m_pBottom);
		m_PrevSmokeTime = GetTickCount();
	}

	
}
