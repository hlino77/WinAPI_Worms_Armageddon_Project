#pragma once
#include "Weapon.h"
#include "Sprite.h"

class CWeapon_Teleport : public CWeapon
{
public:
	CWeapon_Teleport();
	virtual ~CWeapon_Teleport();


	virtual void Update(void) override;
	virtual void Initialize(CObj * _pOwner) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;
	virtual void Key_Input(void) override;
	virtual void Shoot(void) override;
	virtual void ResetWeapon(void) override;


	void		Sprite_Reset(void);
private:
	CSprite*			m_pDraw;
	CSprite*			m_pTeleWork;

	CMyVector2			m_vTargetPos;

	bool				m_bStop;
};

