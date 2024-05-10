#pragma once
#include "Weapon.h"
class CWeapon_Hmissile : public CWeapon
{
public:
	CWeapon_Hmissile();
	virtual ~CWeapon_Hmissile();

	virtual void			Update(void) override;
	virtual void			Initialize(CObj * _pOwner) override;
	virtual void			LateUpdate(void) override;
	virtual void			Render(HDC _hDC) override;
	virtual void			Release(void) override;
	virtual void			Key_Input(void) override;
	virtual void			Shoot(void) override;
	virtual void			ResetWeapon(void) override;
private:
	CMyVector2			m_vTargetPos;

	bool				m_bTarget;
};

