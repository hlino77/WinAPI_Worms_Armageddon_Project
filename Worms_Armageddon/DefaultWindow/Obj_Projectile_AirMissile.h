#pragma once
#include "Obj_Projectile.h"
class Obj_Projectile_AirMissile : public CObj_Projectile
{
public:
	Obj_Projectile_AirMissile();
	virtual ~Obj_Projectile_AirMissile();


	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Release(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void MapOut(void) override;
	virtual void Set_Projectile(CObj * _pOwner, CMyVector2 _Pos, float _fPower, CMyVector2 _Dir) override;
	virtual void MapCollision(void) override;

	void				Set_TargetPos(CMyVector2 _vPos) { m_vTargetPos = _vPos; }
private:
	void					Exhaust(void);
	DWORD					m_ExhaustTime;
	DWORD					m_ExhaustDelay;

	float					m_fSpeed;

	float					m_fTargetAngle;
	CMyVector2				m_vTargetPos;


	void					MissileMove(void);

	float					m_fTargetLength;
	void					Set_TargetAngle(void);
};

