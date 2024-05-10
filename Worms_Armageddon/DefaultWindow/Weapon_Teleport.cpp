#include "stdafx.h"
#include "Weapon_Teleport.h"
#include "KeyMgr.h"
#include "SoundMgr.h"
#include "Obj_Worm.h"
#include "Sprite_TeleportDraw.h"
#include "Sprite_TeleWork.h"
#include "GameMgr.h"


CWeapon_Teleport::CWeapon_Teleport()
	:m_bStop(false)
{
}


CWeapon_Teleport::~CWeapon_Teleport()
{
	Release();
}

void CWeapon_Teleport::Update(void)
{
	switch (m_WeaponState)
	{
	case WEAPON_STATE::IDLE:
		if (CCameraMgr::Get_Inst()->Is_Mouse() == false)
		{
			CCameraMgr::Get_Inst()->ShowMouse();
		}
		Key_Input();

		m_pDraw->Update();
		break;
	case WEAPON_STATE::SHOOT:
		m_pTeleWork->Update();

		if (static_cast<CSprite_TeleWork*>(m_pTeleWork)->Get_Reverse() == false && m_pTeleWork->Get_SpriteState() == SPRITE_STATE::END)
		{
			static_cast<CSprite_TeleWork*>(m_pTeleWork)->Set_Reverse();
			m_pOwner->Get_Pos().fX = m_vTargetPos.fX;
			m_pOwner->Get_Pos().fY = m_vTargetPos.fY;

			CCameraMgr::Get_Inst()->Go_Target(m_vTargetPos);
			
			m_bStop = true;
		}

		if (static_cast<CSprite_TeleWork*>(m_pTeleWork)->Get_Reverse() && m_pTeleWork->Get_SpriteState() == SPRITE_STATE::END)
		{
			static_cast<CObj_Worm*>(m_pOwner)->Set_State(WORM_STATE::JUMP);
			static_cast<CObj_Worm*>(m_pOwner)->Set_JumpState(WORM_JUMP_STATE::FLYDOWN);
			static_cast<CObj_Worm*>(m_pOwner)->Put_Weapon();
			CGameMgr::Get_Inst()->Set_TurnEnd();
			m_bStop = false;
		}

		if (m_bStop)
			m_pOwner->Get_Mover()->Stop();

		break;
	}
	
}

void CWeapon_Teleport::Initialize(CObj * _pOwner)
{
	m_WeaponType = WEAPON_TYPE::TELEPORT;
	m_WeaponState = WEAPON_STATE::IDLE;


	m_pOwner = _pOwner;


	m_pDraw = new CSprite_TeleportDraw;
	m_pDraw->Initialize(m_pOwner);

	m_pTeleWork = new CSprite_TeleWork;
	m_pTeleWork->Initialize(m_pOwner);

	m_pAim = nullptr;


	return;
}

void CWeapon_Teleport::LateUpdate(void)
{
}

void CWeapon_Teleport::Render(HDC _hDC)
{
	switch (m_WeaponState)
	{
	case WEAPON_STATE::IDLE:
		m_pDraw->Render(_hDC);
		break;
	case WEAPON_STATE::SHOOT:
		m_pTeleWork->Render(_hDC);
		break;
	}
}

void CWeapon_Teleport::Release(void)
{

	Safe_Delete(m_pDraw);
	Safe_Delete(m_pTeleWork);
}

void CWeapon_Teleport::Key_Input(void)
{
	if (CKeyMgr::Get_Inst()->Key_Down(VK_LBUTTON))
	{
		CSoundMgr::Get_Instance()->StopSound(CHANNELID::GAMESOUND);
		CSoundMgr::Get_Instance()->PlaySoundW(L"Communicator.wav", CHANNELID::GAMESOUND, g_fVolume);


		CSoundMgr::Get_Instance()->StopSound(CHANNELID::WEAPONSOUND);
		CSoundMgr::Get_Instance()->PlaySoundW(L"TELEPORT.WAV", CHANNELID::WEAPONSOUND, g_fVolume);

		POINT* pt = CCameraMgr::Get_Inst()->Get_Mouse();

		float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
		float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();

		m_vTargetPos = { pt->x - fScrollX , pt->y - fScrollY };

		Shoot();

		

		if (CCameraMgr::Get_Inst()->Is_Mouse() == true)
		{
			CCameraMgr::Get_Inst()->PutMouse();
		}
	}

}

void CWeapon_Teleport::Shoot(void)
{
	m_WeaponState = WEAPON_STATE::SHOOT;
}

void CWeapon_Teleport::ResetWeapon(void)
{
}

void CWeapon_Teleport::Sprite_Reset(void)
{
	static_cast<CSprite_TeleportDraw*>(m_pDraw)->Draw_Reset();
}
