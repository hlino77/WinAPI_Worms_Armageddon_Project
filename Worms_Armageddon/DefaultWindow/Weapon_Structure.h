#pragma once
#include "Weapon.h"
#include "Image_Structure.h"

class CWeapon_Structure : public CWeapon
{
public:
	CWeapon_Structure();
	virtual ~CWeapon_Structure();

	virtual void			Update(void) override;
	virtual void			Initialize(CObj * _pOwner) override;
	virtual void			LateUpdate(void) override;
	virtual void			Render(HDC _hDC) override;
	virtual void			Release(void) override;
	virtual void			Key_Input(void) override;
	virtual void			Shoot(void) override;
	virtual void			ResetWeapon(void) override;

private:
	CMyImage*				m_pStructure;

	CMyVector2				m_vMousePos;
	POINT*					m_pMousePoint;
};

