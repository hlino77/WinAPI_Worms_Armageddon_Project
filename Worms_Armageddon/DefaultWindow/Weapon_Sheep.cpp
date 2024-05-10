#include "stdafx.h"
#include "Weapon_Sheep.h"
#include "KeyMgr.h"
#include "Obj_Projectile_Sheep.h"
#include "ObjMgr.h"
#include "Obj_Worm.h"
#include "SoundMgr.h"


CWeapon_Sheep::CWeapon_Sheep()
{
}


CWeapon_Sheep::~CWeapon_Sheep()
{
	Release();
}

void CWeapon_Sheep::Update(void)
{
	Key_Input();
}

void CWeapon_Sheep::Initialize(CObj * _pOwner)
{
	m_WeaponType = WEAPON_TYPE::SHEEP;
	m_WeaponState = WEAPON_STATE::IDLE;

	m_pOwner = _pOwner;


	return;
}

void CWeapon_Sheep::LateUpdate(void)
{

}

void CWeapon_Sheep::Render(HDC _hDC)
{
}

void CWeapon_Sheep::Release(void)
{
}

void CWeapon_Sheep::Key_Input(void)
{
	if (m_WeaponState == WEAPON_STATE::IDLE)
	{
		if (CKeyMgr::Get_Inst()->Key_Down(VK_SPACE))
		{
			m_WeaponState = WEAPON_STATE::SHOOT;
			Shoot();

			CSoundMgr::Get_Instance()->StopSound(CHANNELID::WEAPONSOUND);
			CSoundMgr::Get_Instance()->PlaySoundW(L"LAUGH.WAV", CHANNELID::WEAPONSOUND, g_fVolume);

			CSoundMgr::Get_Instance()->StopSound(CHANNELID::PROJECTILE);
			CSoundMgr::Get_Instance()->PlaySoundW(L"SHEEPBAA.WAV", CHANNELID::PROJECTILE, g_fVolume);
		}
	}
}

void CWeapon_Sheep::Shoot(void)
{
	CObj*		pNewProjectile = new CObj_Projectile_Sheep;
	pNewProjectile->Initialize();

	CMyVector2	ShootDir;

	if (m_pOwner->Get_ObjDir() == OBJ_DIR::LEFT)
	{
		ShootDir = { -1.0f, 0.0f };
	}
	else if (m_pOwner->Get_ObjDir() == OBJ_DIR::RIGHT)
	{
		ShootDir = { 1.0f, 0.0f };
	}

	CMyVector2  ShootPos = { m_pOwner->Get_Pos().fX, m_pOwner->Get_Pos().fY};


	static_cast<CObj_Projectile_Sheep*>(pNewProjectile)->Set_Projectile(m_pOwner, ShootPos, m_fShootPower, ShootDir);

	CObjMgr::Get_Inst()->Add_Obj(pNewProjectile->Get_ObjTyep(), pNewProjectile);


	CCameraMgr::Get_Inst()->Follow_Target(pNewProjectile);

	static_cast<CObj_Worm*>(m_pOwner)->Set_State(WORM_STATE::IDLE);
	static_cast<CObj_Worm*>(m_pOwner)->Put_Weapon();
}

void CWeapon_Sheep::ResetWeapon(void)
{
}
