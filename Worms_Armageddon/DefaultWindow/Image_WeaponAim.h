#pragma once
#include "MyImage.h"
#include "Obj_Worm.h"


class CImage_WeaponAim : public CMyImage
{
public:
	CImage_WeaponAim();
	virtual ~CImage_WeaponAim();

	virtual void			Initialize(CObj * _pObj) override;
	virtual void			Update(void) override;
	virtual void			LateUpdate(void) override;
	virtual void			Render(HDC _hDC) override;
	virtual void			Set_Size(void) override;
	virtual void			Reset(void) override;
	
	
private:
	void					Set_TargetWeaponAngle(void) { m_fTargetAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_Weapon()->Get_Angle(); }


	float					m_fAimDistance;

	int						m_iTargetCurr;
};

