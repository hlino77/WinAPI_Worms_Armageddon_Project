#pragma once
#include "Weapon.h"
class CWeapon_Donkey : public CWeapon
{
public:
	CWeapon_Donkey();
	virtual ~CWeapon_Donkey();

	virtual void			Update(void) override;
	virtual void			Initialize(CObj * _pOwner) override;
	virtual void			LateUpdate(void) override;
	virtual void			Render(HDC _hDC) override;
	virtual void			Release(void) override;
	virtual void			Key_Input(void) override;
	virtual void			Shoot(void) override;
	virtual void			ResetWeapon(void) override;
private:

};

