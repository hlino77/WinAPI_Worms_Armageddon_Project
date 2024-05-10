#include "stdafx.h"
#include "State_Worm_Idle.h"
#include "KeyMgr.h"
#include "Weapon_Bazooka.h"
#include "EffectMgr.h"
#include "UIMgr.h"
#include "Weapon_Teleport.h"

CState_Worm_Idle::CState_Worm_Idle()
{
}


CState_Worm_Idle::~CState_Worm_Idle()
{
	Release();
}

void CState_Worm_Idle::Initialize(CObj * _pOwner)
{
	Set_Owner(_pOwner);


	m_fCenterX = 7.0f;
	m_fLeftX = 4.0f;
	m_fRightX = 10.0f;
	m_fLeftY = -1.0f;
	m_fRightY = -1.0f;
	m_fBottomLength = 8.0f;

}

void CState_Worm_Idle::Update(void)
{

	m_pOwnerMover->Update();


	Key_Input();

	if (*m_pWeapon && *m_pTurn)
	{
		*m_pWormState = WORM_STATE::WEAPON;
		(*m_pWeapon)->Reset_Aim();

		if ((*m_pWeapon)->Get_WeaponType() == WEAPON_TYPE::TELEPORT)
			static_cast<CWeapon_Teleport*>(*m_pWeapon)->Sprite_Reset();
	}
}

void CState_Worm_Idle::LateUpdate(void)
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

void CState_Worm_Idle::Release(void)
{
}

void CState_Worm_Idle::Key_Input(void)
{
	if (CKeyMgr::Get_Inst()->Key_Pressing(VK_LEFT))
	{
		m_pOwner->Set_ObjDir(OBJ_DIR::LEFT);
		*m_pWormState = WORM_STATE::WALK;
	}
	if (CKeyMgr::Get_Inst()->Key_Pressing(VK_RIGHT))
	{
		m_pOwner->Set_ObjDir(OBJ_DIR::RIGHT);
		*m_pWormState = WORM_STATE::WALK;
	}

	if (CKeyMgr::Get_Inst()->Key_Down(VK_RETURN))
	{
		*m_pWormState = WORM_STATE::JUMP;
		*m_pJumpState = WORM_JUMP_STATE::START;
	}

	if (CKeyMgr::Get_Inst()->Key_Down('1'))
	{
		(*m_pWeapon) = m_pInventory->Get_Weapon(WEAPON_TYPE::BAZOOKA);

		(*m_pWeapon)->Reset_Aim();

		static_cast<CObj_Worm*>(m_pOwner)->Set_State(WORM_STATE::WEAPON);
	}

	if (CKeyMgr::Get_Inst()->Key_Down(VK_RBUTTON))
		CUIMgr::Get_Inst()->Get_Inventory(m_pInventory);
}



void CState_Worm_Idle::Worm_Map_Collision(void)
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
		m_pPos->fY = (int)(m_pBottom->fY - m_fBottomLength);

		if (m_pOwnerMover->Get_Velocity().fY > 0)
			m_pOwnerMover->Stop();

		Set_BottomAngle();

		if (*m_pTurn == false)
			*m_pWormState = WORM_STATE::NOTTURN;
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

void CState_Worm_Idle::Set_BottomAngle(void)
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

