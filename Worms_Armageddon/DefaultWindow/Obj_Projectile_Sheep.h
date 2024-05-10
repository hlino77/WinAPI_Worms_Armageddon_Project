#pragma once
#include "Obj_Projectile.h"
#include "Sprite_Sheep.h"

class CObj_Projectile_Sheep : public CObj_Projectile
{
public:
	CObj_Projectile_Sheep();
	virtual ~CObj_Projectile_Sheep();


	virtual void		Initialize(void) override;
	virtual void		Update(void) override;
	virtual void		LateUpdate(void) override;
	virtual void		Release(void) override;
	virtual void		Render(HDC _hDC) override;
	virtual void		MapOut(void) override;
	virtual void		Set_Projectile(CObj * _pOwner, CMyVector2 _Pos, float _fPower, CMyVector2 _Dir) override;
	virtual void		MapCollision(void) override;

private:
	CSprite*			m_pSprite;

	void				DirMove(void);

	void				Key_Input(void);

	void				Bomb(void);
};

