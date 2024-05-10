#pragma once
#include "Weapon.h"
class CWeapon_Baseball : public CWeapon
{
public:
	CWeapon_Baseball();
	virtual ~CWeapon_Baseball();

	virtual void Update(void) override;
	virtual void Initialize(CObj * _pOwner) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;
	virtual void Key_Input(void) override;
	virtual void Shoot(void) override;
	virtual void ResetWeapon(void) override;

private:
	float		m_fEndDelay;
};

