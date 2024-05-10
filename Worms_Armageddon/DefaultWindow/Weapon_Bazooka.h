#pragma once
#include "Weapon.h"
class CWeapon_Bazooka : public CWeapon
{
public:
	CWeapon_Bazooka();
	virtual ~CWeapon_Bazooka();

	virtual void			Update(void) override;
	virtual void			Initialize(CObj* _pOwner) override;
	virtual void			LateUpdate(void) override;
	virtual void			Render(HDC _hDC) override;
	virtual void			Release(void) override;
	virtual void			Key_Input(void) override;
	virtual void			Shoot(void) override;
	virtual void			ResetWeapon(void) override;
private:
	float					m_fAimAngle;
	float					m_fAimDistance;
	HDC						m_hAimDC;
};

