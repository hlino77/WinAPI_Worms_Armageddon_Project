#pragma once
#include "Define.h"
#include "Obj.h"
#include "MyImage.h"


class CWeapon
{
public:
	CWeapon();
	virtual ~CWeapon();

	virtual void			Update(void) PURE;
	virtual void			Initialize(CObj* _pOwner) PURE;
	virtual void			LateUpdate(void) PURE;
	virtual void			Render(HDC _hDC) PURE;
	virtual void			Release(void) PURE;
	virtual void			Key_Input(void) PURE;
	virtual void			Shoot(void) PURE;
	virtual void			ResetWeapon(void) PURE;
	virtual void			Gage_Render(HDC _hDC);


	WEAPON_STATE			Get_WeaponState(void) { return m_WeaponState; }
	WEAPON_TYPE				Get_WeaponType(void) { return m_WeaponType; }
	float					Get_Angle(void) { return m_fAngle; }



	void					Reset_Aim(void); 



	virtual void			UpAngle(void) 
	{ 
		m_fAngle += 1.5f;  
		if (m_fAngle > 180.0f)
			m_fAngle = 180.0f;
	};
	virtual void			DownAngle(void) 
	{
		m_fAngle -= 1.5f;
		if (m_fAngle < 0)
			m_fAngle = 0.0f;
	};
	
protected:
	float					m_fAngle;
	float					m_fLength;

	CObj*					m_pOwner;

	WEAPON_TYPE				m_WeaponType;
	WEAPON_STATE			m_WeaponState;


	//게이지
	float					m_fShootPower;
	HDC						m_hGageDC;


	//조준점
	CMyImage*				m_pAim;
private:
	
};

