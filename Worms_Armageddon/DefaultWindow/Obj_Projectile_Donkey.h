#pragma once
#include "Obj_Projectile.h"
class CObj_Projectile_Donkey : public CObj_Projectile
{
public:
	CObj_Projectile_Donkey();
	virtual ~CObj_Projectile_Donkey();


	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Release(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void MapOut(void) override;
	virtual void Set_Projectile(CObj * _pOwner, CMyVector2 _Pos, float _fPower, CMyVector2 _Dir) override;
	virtual void MapCollision(void) override;

private:

};

