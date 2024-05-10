#pragma once
#include "Weapon.h"
#include "Obj.h"

class CInventory
{
public:
	CInventory();
	~CInventory();

	void		Initialize(CObj* _pOwner);
	void		Update(void);
	void		LateUpdate(void);
	void		Release(void);

	
	CWeapon*			Get_Weapon(WEAPON_TYPE _WeaponType);
	void				Set_OwnerWeapon(WEAPON_TYPE _WeaponType);
private:
	vector<CWeapon*>		m_WeaponList;
	CObj*					m_pOwner;

	void					Insert_Weapon(void);
};

