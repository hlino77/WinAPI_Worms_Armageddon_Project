#include "stdafx.h"
#include "State_Worm_Jump.h"
#include "SoundMgr.h"

CState_Worm_Jump::CState_Worm_Jump()
{
}


CState_Worm_Jump::~CState_Worm_Jump()
{
	Release();
}

void CState_Worm_Jump::Initialize(CObj * _pOwner)
{
	Set_Owner(_pOwner);

	m_fCenterX = 7.0f;
	m_fLeftX = 4.0f;
	m_fRightX = 10.0f;
	m_fLeftY = -1.0f;
	m_fRightY = -1.0f;
	m_fBottomLength = 8.0f;

	m_JumpDelay = 300.0f;
}

void CState_Worm_Jump::Update(void)
{
	switch (*m_pJumpState)
	{
	case WORM_JUMP_STATE::START:
		*m_pJumpState = WORM_JUMP_STATE::READY;
		m_JumpStartTime = GetTickCount();
		break;
	case WORM_JUMP_STATE::READY:
		if (m_JumpStartTime + m_JumpDelay < GetTickCount())
		{
			if (*m_pObjDir == OBJ_DIR::LEFT)
			{
				m_pOwnerMover->Stop();
				m_pOwnerMover->AddForce(CMyVector2(-1000.0f, -2000.0f));
				CSoundMgr::Get_Instance()->StopSound(CHANNELID::WORMSPEECH);
				CSoundMgr::Get_Instance()->PlaySoundW(L"JUMP1.WAV", CHANNELID::WORMSPEECH, g_fVolume);
			}
			else if (*m_pObjDir == OBJ_DIR::RIGHT)
			{
				m_pOwnerMover->Stop();
				m_pOwnerMover->AddForce(CMyVector2(1000.0f, -2000.0f));
				CSoundMgr::Get_Instance()->StopSound(CHANNELID::WORMSPEECH);
				CSoundMgr::Get_Instance()->PlaySoundW(L"JUMP1.WAV", CHANNELID::WORMSPEECH, g_fVolume);
			}
			*m_pJumpState = WORM_JUMP_STATE::FLYUP;
		}
		break;
	case WORM_JUMP_STATE::FLYUP:
		if (m_pOwnerMover->Get_Velocity().fY > -0.5f)
			*m_pJumpState = WORM_JUMP_STATE::FLY;
	case WORM_JUMP_STATE::FLY:
		if (*m_pMapCollision)
			Worm_Map_Collision();

		if (static_cast<CObj_Worm*>(m_pOwner)->Get_Animator()->Get_CurrSprite()->Get_SpriteState() == SPRITE_STATE::END)
			*m_pJumpState = WORM_JUMP_STATE::FLYDOWN;
		break;
	case WORM_JUMP_STATE::FLYDOWN:
		if (*m_pMapCollision)
			Worm_Map_Collision();
		break;
	case WORM_JUMP_STATE::LAND:
		if (static_cast<CObj_Worm*>(m_pOwner)->Get_Animator()->Get_CurrSprite()->Get_SpriteState() == SPRITE_STATE::END)
			*m_pJumpState = WORM_JUMP_STATE::END;
		break;
	case WORM_JUMP_STATE::END:
		*m_pWormState = WORM_STATE::IDLE;
		*m_pJumpState = WORM_JUMP_STATE::TYPEEND;
		break;
	}


	m_pOwnerMover->Update();

}

void CState_Worm_Jump::LateUpdate(void)
{
	if (*m_pMapCollision)
		Worm_Map_Collision();
	else
	{
		*m_pLeftAngle = 0.0f;
		*m_pRightAngle = 0.0f;
	}

	if (*m_pBombCollision)
		BombCollision();

	m_pOwnerMover->LateUpdate();
}

void CState_Worm_Jump::Release(void)
{

}

void CState_Worm_Jump::Key_Input(void)
{
}


void CState_Worm_Jump::Worm_Map_Collision(void)
{
	if (*m_pJumpState == WORM_JUMP_STATE::FLY || *m_pJumpState == WORM_JUMP_STATE::FLYUP || *m_pJumpState == WORM_JUMP_STATE::FLYDOWN)
		RoundCollision();
	else
		DownCollision();
}

void CState_Worm_Jump::DownCollision(void)
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

	if (m_fCenterY >= 0.0f && m_fCenterY < 15.0f)
	{
		m_pBottom->fY = (int)(m_pBottom->fY + (m_fCenterY - 14.0f));
		m_pPos->fY = m_pBottom->fY - m_fBottomLength;

		if (m_pOwnerMover->Get_Velocity().fY > 0)
			m_pOwnerMover->StopY();

		Set_BottomAngle();

		if (*m_pJumpState == WORM_JUMP_STATE::FLY || *m_pJumpState == WORM_JUMP_STATE::FLYDOWN)
		{
			*m_pJumpState = WORM_JUMP_STATE::LAND;
			m_pOwnerMover->StopX();
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






	//리셋
	*m_pMapCollision = false;
	m_pClosest->fX = 0.0f;
	m_pClosest->fY = 0.0f;


	m_fLeftY = -1.0f;
	m_fRightY = -1.0f;
	m_fCenterY = -1.0f;

	fill(m_pBoundingBox->begin(), m_pBoundingBox->end(), false);
}

void CState_Worm_Jump::RoundCollision(void)
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
	}

	if (m_fRightY == 0.0f && m_pOwnerMover->Get_Velocity().fX > 0)
	{
		m_pOwnerMover->Brake(0.8f);
		m_pOwnerMover->Get_Velocity().Set_fX(m_pOwnerMover->Get_Velocity().fX * -1);
	}


	if (m_fCenterY >= 0.0f && m_fCenterY < 7.0f && m_pOwnerMover->Get_Velocity().fY < 0)
	{
		m_pOwnerMover->Brake(0.8f);
		m_pOwnerMover->Get_Velocity().Set_fY(m_pOwnerMover->Get_Velocity().fY * -1);
	}

	if (m_fCenterY >= 7.0f && m_fCenterY < 15.0f && m_pOwnerMover->Get_Velocity().fY > 0)
	{
		m_pBottom->fY = (int)(m_pBottom->fY + (m_fCenterY - 14.0f));
		m_pPos->fY = m_pBottom->fY - m_fBottomLength;

		if (m_pOwnerMover->Get_Velocity().fY > 0)
			m_pOwnerMover->StopY();

		Set_BottomAngle();

		if (*m_pJumpState == WORM_JUMP_STATE::FLY || *m_pJumpState == WORM_JUMP_STATE::FLYDOWN)
		{
			*m_pJumpState = WORM_JUMP_STATE::LAND;
			m_pOwnerMover->StopX();
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




	//리셋
	*m_pMapCollision = false;
	m_pClosest->fX = 0.0f;
	m_pClosest->fY = 0.0f;


	m_fLeftY = -1.0f;
	m_fRightY = -1.0f;
	m_fCenterY = -1.0f;

	fill(m_pBoundingBox->begin(), m_pBoundingBox->end(), false);
}

void CState_Worm_Jump::Set_BottomAngle(void)
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
