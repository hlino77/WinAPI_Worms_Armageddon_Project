#pragma once
#include "Obj.h"
#include "MyImage.h"

class CObj_Projectile : public CObj
{
public:
	CObj_Projectile();
	virtual ~CObj_Projectile();

	virtual void			Initialize(void) PURE;
	virtual void			Update(void) PURE;
	virtual void			LateUpdate(void) PURE;
	virtual void			Release(void) PURE;
	virtual void			Render(HDC _hDC) PURE;
	virtual void			MapOut(void) PURE;
	
	virtual void			Set_Projectile(CObj* _pOwner , CMyVector2 _Pos, float _fPower, CMyVector2 _Dir) PURE;
	
	float					Get_Angle(void) { return m_fAngle; }
	float*					Get_pAngle(void) { return &m_fAngle; }


	PROJECTILE_STATE		Get_ProjectileState(void) { return m_ProjectileState; }
	CMyVector2&				Get_Explosion(void) { return m_vExplosion; }
	WEAPON_TYPE				Get_WeaponType(void) { return m_WeaponType; }

	int						Get_Damage(void) { return m_iDamage; }
protected:
	CObj*					m_pOwner;
	float					m_fPower;

	float					m_fAngle;

	CMyImage*				m_pImage;

	PROJECTILE_STATE		m_ProjectileState;
	virtual void			MapCollision(void) PURE;
	CMyVector2				m_vExplosion;

	WEAPON_TYPE				m_WeaponType;

	virtual void			ExplosionSmoke(SMOKE_EFFECT_TYPE _SmokeType, int iCount);


	void					Set_Angle(void) 
	{
		if (m_pMover->Get_Velocity().fX != 0 && m_pMover->Get_Velocity().fY != 0)
		{
			float fRadian = acosf((m_pMover->Get_Velocity().fY * -1) / m_pMover->Get_Velocity().Get_Magnitude());

			if (m_pMover->Get_Velocity().fX < 0)
				fRadian = (2 * PI) - fRadian;

			m_fAngle = RAD2DEG(fRadian);
		}
	}

	int						m_iDamage;

	WIND_DIR				m_WindDir;
	int						m_iWindSpeed;
	void					Set_Wind(void);

	void					WindMove(void);
};

