#pragma once
#include "Obj_Projectile.h"
class CObj_Projectile_Baseball : public CObj_Projectile
{
public:
	CObj_Projectile_Baseball();
	virtual ~CObj_Projectile_Baseball();


	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Release(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void MapOut(void) override;
	virtual void Set_Projectile(CObj * _pOwner, CMyVector2 _Pos, float _fPower, CMyVector2 _Dir) override;
	virtual void MapCollision(void) override;


	void				Set_Owner(CObj* _pOwner) { m_pOwner = _pOwner; }

	float				Get_Power(void) { return m_fShootPower; }
	CMyVector2			Get_Dir(void) { return m_vDir; }
	CObj*				Get_Owner(void) { return m_pOwner; }
private:
	float				m_fShootPower;
	CMyVector2			m_vDir;

	CObj*				m_pOwner;
};

