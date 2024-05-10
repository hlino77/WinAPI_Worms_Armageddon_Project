#pragma once
#include "MyImage.h"
#include "Obj_Worm.h"

class CImage_WeaponIdle : public CMyImage
{
public:
	CImage_WeaponIdle();
	virtual ~CImage_WeaponIdle();

	virtual void				Initialize(CObj * _pObj) override;
	virtual void				Update(void) override;
	virtual void				LateUpdate(void) override;
	virtual void				Render(HDC _hDC) override;
	virtual void				Set_Size(void) override {};
	virtual void				Reset(void) override {};


	void						Set_Weapon(void);
private:
	void						Set_TargetWeaponAngle(void) { m_fTargetAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_Weapon()->Get_Angle(); }

	void						Insert_Image(void);


	


	//바주카
	void						Set_Bazooka(void);
	void						Set_Bazooka_Angle(void);

	//야구
	void						Set_Base(void);
	void						Set_Base_Angle(void);
};

