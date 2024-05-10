#include "stdafx.h"
#include "State_Worm_Flying.h"
#include "TimeMgr.h"
#include "SoundMgr.h"


CState_Worm_Flying::CState_Worm_Flying()
{
}


CState_Worm_Flying::~CState_Worm_Flying()
{
	Release();
}

void CState_Worm_Flying::Initialize(CObj * _pOwner)
{
	Set_Owner(_pOwner);

	m_fCenterX = 7.0f;
	m_fLeftX = 0.0f;
	m_fRightX = 15.0f;
	m_fLeftY = -1.0f;
	m_fRightY = -1.0f;
	m_fBottomLength = 8.0f;
	m_fBaseDelay = 1.0f;
}

void CState_Worm_Flying::Update(void)
{
	

	m_pOwnerMover->Update();
	if (m_pOwnerMover->Get_Velocity().fX < 0)
	{
		*m_pObjDir = OBJ_DIR::LEFT;
	}
	else if (m_pOwnerMover->Get_Velocity().fX > 0)
	{
		*m_pObjDir = OBJ_DIR::RIGHT;
	}
	
	if (*m_pBaseHit)
	{
		m_fBaseDelay -= CTimeMgr::Get_Inst()->Get_DeltaTime();

		if (m_fBaseDelay < 0.0f)
		{
			CSoundMgr::Get_Instance()->PlaySoundW(L"BaseBallBatJingle.wav", CHANNELID::GAMESOUND2, g_fVolume);
			m_fBaseDelay = 1.0f;
			*m_pBaseHit = false;
		}
	}

}

void CState_Worm_Flying::LateUpdate(void)
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

void CState_Worm_Flying::Release(void)
{

}

void CState_Worm_Flying::Key_Input(void)
{

}




void CState_Worm_Flying::Worm_Map_Collision(void)
{
	float fX = m_pPos->fX;
	float fY = m_pPos->fY;

	int	iCenter = (*m_pLineLength * 0.5f)+ 0.5f;

	bool bUpMove = true;
	bool bDownMove = true;
	bool bLeftMove = true;
	bool bRightMove = true;


	for (auto iter : *m_pLeftBox)
	{
		if (iter == true)
		{
			bLeftMove = false;
			break;
		}
	}

	for (auto iter : *m_pTopBox)
	{
		if (iter == true)
		{
			bUpMove = false;
			break;
		}
	}

	for (auto iter : *m_pRightBox)
	{
		if (iter == true)
		{
			bRightMove = false;
			break;
		}
	}

	for (auto iter : *m_pBottomBox)
	{
		if (iter == true)
		{
			bDownMove = false;
			break;
		}
	}


	


	if (!bUpMove && m_pOwnerMover->Get_Velocity().fY < 0.0f)
	{
		m_pOwnerMover->Brake(0.8f);
		m_pOwnerMover->Get_Velocity().Set_fY(m_pOwnerMover->Get_Velocity().fY * -1);
		CSoundMgr::Get_Instance()->Random_WormHit();
	}

	if (!bLeftMove && m_pOwnerMover->Get_Velocity().fX < 0.0f)
	{
		m_pOwnerMover->Brake(0.8f);
		m_pOwnerMover->Get_Velocity().Set_fX(m_pOwnerMover->Get_Velocity().fX * -1);
		CSoundMgr::Get_Instance()->Random_WormHit();
	}

	if (!bRightMove && m_pOwnerMover->Get_Velocity().fX > 0.0f)
	{
		m_pOwnerMover->Brake(0.8f);
		m_pOwnerMover->Get_Velocity().Set_fX(m_pOwnerMover->Get_Velocity().fX * -1);
		CSoundMgr::Get_Instance()->Random_WormHit();
	}

	if (!bDownMove)
	{
		if (m_pOwnerMover->Get_Velocity().fY > 0.0f)
		{
			m_pOwnerMover->StopY();
			*m_pWormState = WORM_STATE::SLIDE;
			CSoundMgr::Get_Instance()->Random_WormHit();
		}
	}




	//¸®¼Â
	*m_pMapCollision = false;


	fill(m_pLeftBox->begin(), m_pLeftBox->end(), false);
	fill(m_pRightBox->begin(), m_pRightBox->end(), false);
	fill(m_pTopBox->begin(), m_pTopBox->end(), false);
	fill(m_pBottomBox->begin(), m_pBottomBox->end(), false);
}

void CState_Worm_Flying::Set_BottomAngle(void)
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
