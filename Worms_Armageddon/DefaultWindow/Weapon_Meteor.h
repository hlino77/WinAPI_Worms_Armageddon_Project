#pragma once
#include "Weapon.h"


class CWeapon_Meteor : public CWeapon
{
public:
	CWeapon_Meteor();
	virtual ~CWeapon_Meteor();

	// CWeapon을(를) 통해 상속됨
	virtual void Update(void) override;
	virtual void Initialize(CObj * _pOwner) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;
	virtual void Key_Input(void) override;
	virtual void Shoot(void) override;
	virtual void ResetWeapon(void) override;

private:
	HDC			m_MeteorIcon;
	

	void		IconRender(HDC _hDC);


	vector<CObj*>	m_vecMeteors;
};

