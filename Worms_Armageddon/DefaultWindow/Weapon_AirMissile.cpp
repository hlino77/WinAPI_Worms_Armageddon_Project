#include "stdafx.h"
#include "Weapon_AirMissile.h"
#include "BmpMgr.h"
#include "Image_WeaponAim.h"
#include "KeyMgr.h"
#include "Obj_Projectile_AirMissile.h"
#include "ObjMgr.h"
#include "GameMgr.h"
#include "Image_Jet.h"
#include "EffectMgr.h"
#include "SoundMgr.h"


CWeapon_AirMissile::CWeapon_AirMissile()
{
}


CWeapon_AirMissile::~CWeapon_AirMissile()
{
	Release();
}

void CWeapon_AirMissile::Update(void)
{

	switch (m_WeaponState)
	{
	case WEAPON_STATE::IDLE:
		if (CCameraMgr::Get_Inst()->Is_Mouse() == false && m_WeaponState == WEAPON_STATE::IDLE)
		{
			CCameraMgr::Get_Inst()->ShowMouse();
		}
		Key_Input();
		break;
	case WEAPON_STATE::SHOOT:
		JetUpdate();
		break;
	case WEAPON_STATE::SHOOTEND:
		m_vJetPos.fX += 20.0f;
		if (m_vJetPos.fX > 4000.0f)
		{
			m_vJetPos.fX = 4000.0f;
			static_cast<CObj_Worm*>(m_pOwner)->Set_State(WORM_STATE::IDLE);
			static_cast<CObj_Worm*>(m_pOwner)->Put_Weapon();
		}
		break;
	}
	

	
}

void CWeapon_AirMissile::Initialize(CObj * _pOwner)
{
	m_WeaponType = WEAPON_TYPE::AIRMISSILE;
	m_WeaponState = WEAPON_STATE::IDLE;

	m_fLength = 10.0f;

	m_pOwner = _pOwner;



	m_pAim = nullptr;



	m_vJetPos = { 0.0f, 400.0f };
	m_pJet = new CImage_Jet;
	m_pJet->Initialize(nullptr);
	static_cast<CImage_Jet*>(m_pJet)->Set_JetPos(&m_vJetPos);
}

void CWeapon_AirMissile::LateUpdate(void)
{
}

void CWeapon_AirMissile::Render(HDC _hDC)
{
	m_pJet->Render(_hDC);
}

void CWeapon_AirMissile::Release(void)
{
	Safe_Delete(m_pJet);
}

void CWeapon_AirMissile::Key_Input(void)
{
	if (CKeyMgr::Get_Inst()->Key_Down(VK_LBUTTON))
	{
		CSoundMgr::Get_Instance()->StopSound(CHANNELID::WEAPONSOUND);
		CSoundMgr::Get_Instance()->PlaySoundW(L"CursorSelect.wav", CHANNELID::WEAPONSOUND, g_fVolume);
		
		CSoundMgr::Get_Instance()->StopSound(CHANNELID::PROJECTILE);
		CSoundMgr::Get_Instance()->PlaySoundW(L"Airstrike.wav", CHANNELID::PROJECTILE, g_fVolume);

		CSoundMgr::Get_Instance()->StopSound(CHANNELID::WORMSPEECH);
		CSoundMgr::Get_Instance()->PlaySoundW(L"INCOMING.WAV", CHANNELID::WORMSPEECH, g_fVolume);


		POINT* pt = CCameraMgr::Get_Inst()->Get_Mouse();

		float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
		float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();

		m_vTargetPos = { pt->x - fScrollX , pt->y - fScrollY };

		cout << m_vTargetPos.fX << endl;
		cout << m_vTargetPos.fY << endl;

		m_vShootPos = { m_vTargetPos.fX - 190.0f , 400.0f };

		CEffectMgr::Get_Inst()->Get_Marker(m_vTargetPos);

		m_fShootPower = 0.0f;

		if (CCameraMgr::Get_Inst()->Is_Mouse() == true)
		{
			CCameraMgr::Get_Inst()->PutMouse();
		}

		m_WeaponState = WEAPON_STATE::SHOOT;
		CCameraMgr::Get_Inst()->Go_Target(m_vShootPos);

		
	}
}

void CWeapon_AirMissile::Shoot(void)
{
	CMyVector2  ShootPos = { m_vTargetPos.fX - 190.0f , 400.0f };
	CMyVector2  TargetPos = { m_vTargetPos.fX - 90.0f , m_vTargetPos.fY };

	CObj*		pNewProjectile = nullptr;

	for (int i = 0; 5 > i; ++i)
	{
		pNewProjectile = new Obj_Projectile_AirMissile;
		pNewProjectile->Initialize();


		ShootPos.fX += 30.0f;
		TargetPos.fX += 30.0f;

		static_cast<Obj_Projectile_AirMissile*>(pNewProjectile)->Set_Projectile(m_pOwner, ShootPos, 0.0f, ShootPos);
		static_cast<Obj_Projectile_AirMissile*>(pNewProjectile)->Set_TargetPos(TargetPos);

		CObjMgr::Get_Inst()->Add_Obj(pNewProjectile->Get_ObjTyep(), pNewProjectile);

		if(i == 4)
			CGameMgr::Get_Inst()->Set_TurnEnd();

		if (i == 2)
			CCameraMgr::Get_Inst()->Follow_Target(pNewProjectile);
	}


}

void CWeapon_AirMissile::ResetWeapon(void)
{
	m_WeaponState = WEAPON_STATE::IDLE;
	m_vJetPos = { 0.0f, 400.0f };
}

void CWeapon_AirMissile::JetUpdate(void)
{
	m_vJetPos.fX += 20.0f;

	if (m_vJetPos.fX > m_vShootPos.fX + 150.0f)
	{
		Shoot();
		m_WeaponState = WEAPON_STATE::SHOOTEND;
	}
}
