#pragma once
#include "Obj_Projectile.h"
#include "Sprite.h"

class CObj_Projectile_Meteor : public CObj_Projectile
{
public:
	CObj_Projectile_Meteor();
	virtual ~CObj_Projectile_Meteor();


	virtual void			Initialize(void) override;
	virtual void			Update(void) override;
	virtual void			LateUpdate(void) override;
	virtual void			Release(void) override;
	virtual void			Render(HDC _hDC) override;
	virtual void			MapOut(void) override;
	virtual void			Set_Projectile(CObj * _pOwner, CMyVector2 _Pos, float _fPower, CMyVector2 _Dir) override;
	virtual void			MapCollision(void) override;

	void					Set_Meteor(int _iNum);
private:
	CSprite*				m_pSprite;

	void					Exhaust(void);
	DWORD					m_ExhaustTime;
	DWORD					m_ExhaustDelay;

	int						m_iNum;
	DWORD					m_iStartTime;
	DWORD					m_iDelay;

	CMyVector2				m_vTargetPos;

	bool					m_bShooted;

	void					Shoot(void);
};

