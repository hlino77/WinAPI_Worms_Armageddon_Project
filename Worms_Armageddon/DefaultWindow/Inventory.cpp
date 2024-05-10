#include "stdafx.h"
#include "Inventory.h"
#include "Weapon_Bazooka.h"
#include "Obj_Worm.h"
#include "Weapon_Banana.h"
#include "Weapon_Donkey.h"
#include "Weapon_Hmissile.h"
#include "Weapon_AirMissile.h"
#include "Weapon_Baseball.h"
#include "Weapon_Holy.h"
#include "Weapon_Structure.h"
#include "Weapon_Sheep.h"
#include "Weapon_Meteor.h"
#include "Weapon_Teleport.h"

CInventory::CInventory()
{
}


CInventory::~CInventory()
{
	Release();
}

void CInventory::Initialize(CObj* _pOwner)
{
	m_pOwner = _pOwner;

	Insert_Weapon();
}

void CInventory::Update(void)
{
}

void CInventory::LateUpdate(void)
{
}

void CInventory::Release(void)
{
	for (auto& iter : m_WeaponList)
	{
		Safe_Delete(iter);
	}
	m_WeaponList.clear();
}

CWeapon * CInventory::Get_Weapon(WEAPON_TYPE _WeaponType)
{
	m_WeaponList[(UINT)_WeaponType]->ResetWeapon();
	return m_WeaponList[(UINT)_WeaponType];
}

void CInventory::Set_OwnerWeapon(WEAPON_TYPE _WeaponType)
{
	m_WeaponList[(UINT)_WeaponType]->ResetWeapon();
	static_cast<CObj_Worm*>(m_pOwner)->Set_Weapon(m_WeaponList[(UINT)_WeaponType]);
	static_cast<CObj_Worm*>(m_pOwner)->Get_Weapon()->Reset_Aim();
}

void CInventory::Insert_Weapon(void)
{
	m_WeaponList.reserve(20);


	CWeapon* pNewWeapon = nullptr;
	pNewWeapon = new CWeapon_Bazooka;
	pNewWeapon->Initialize(m_pOwner);
	m_WeaponList.push_back(pNewWeapon);
	pNewWeapon = nullptr;


	pNewWeapon = nullptr;
	pNewWeapon = new CWeapon_Banana;
	pNewWeapon->Initialize(m_pOwner);
	m_WeaponList.push_back(pNewWeapon);
	pNewWeapon = nullptr;


	pNewWeapon = nullptr;
	pNewWeapon = new CWeapon_Donkey;
	pNewWeapon->Initialize(m_pOwner);
	m_WeaponList.push_back(pNewWeapon);
	pNewWeapon = nullptr;

	pNewWeapon = nullptr;
	pNewWeapon = new CWeapon_Hmissile;
	pNewWeapon->Initialize(m_pOwner);
	m_WeaponList.push_back(pNewWeapon);
	pNewWeapon = nullptr;

	pNewWeapon = nullptr;
	pNewWeapon = new CWeapon_AirMissile;
	pNewWeapon->Initialize(m_pOwner);
	m_WeaponList.push_back(pNewWeapon);
	pNewWeapon = nullptr;

	pNewWeapon = nullptr;
	pNewWeapon = new CWeapon_Baseball;
	pNewWeapon->Initialize(m_pOwner);
	m_WeaponList.push_back(pNewWeapon);
	pNewWeapon = nullptr;

	pNewWeapon = nullptr;
	pNewWeapon = new CWeapon_Holy;
	pNewWeapon->Initialize(m_pOwner);
	m_WeaponList.push_back(pNewWeapon);
	pNewWeapon = nullptr;

	pNewWeapon = nullptr;
	pNewWeapon = new CWeapon_Structure;
	pNewWeapon->Initialize(m_pOwner);
	m_WeaponList.push_back(pNewWeapon);
	pNewWeapon = nullptr;

	pNewWeapon = nullptr;
	pNewWeapon = new CWeapon_Sheep;
	pNewWeapon->Initialize(m_pOwner);
	m_WeaponList.push_back(pNewWeapon);
	pNewWeapon = nullptr;

	pNewWeapon = nullptr;
	pNewWeapon = new CWeapon_Meteor;
	pNewWeapon->Initialize(m_pOwner);
	m_WeaponList.push_back(pNewWeapon);
	pNewWeapon = nullptr;

	pNewWeapon = nullptr;
	pNewWeapon = new CWeapon_Teleport;
	pNewWeapon->Initialize(m_pOwner);
	m_WeaponList.push_back(pNewWeapon);
	pNewWeapon = nullptr;
}
