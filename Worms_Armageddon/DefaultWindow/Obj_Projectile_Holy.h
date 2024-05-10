#pragma once
#include "Obj_Projectile.h"
#include "Sprite.h"

class CObj_Projectile_Holy : public CObj_Projectile
{
public:
	CObj_Projectile_Holy();
	virtual ~CObj_Projectile_Holy();



	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Release(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void MapOut(void) override;
	virtual void Set_Projectile(CObj * _pOwner, CMyVector2 _Pos, float _fPower, CMyVector2 _Dir) override;
	virtual void MapCollision(void) override;


private:
	void				Angle_Update(void);

	bool				m_bTimer;
	float				m_fTimer;

	void				Bomb(void);

	void				MakeStar(void);

	//Ω∫≈∏¿Ã∆Â∆Æ
	list<CSprite*>								m_StarList;
	list<CSprite*>::iterator					m_Stariter;
	void										Initialize_Star(void);

	list<CSprite*>								m_RenderList;

	float				m_fEffectTime;
	DWORD				m_iEffectDelay;
	DWORD				m_iEffectTime;
	bool				m_bEffect;


	void				EffectUpdate(void);

	void				ResetEffect(void) { m_bEffect = true; m_fEffectTime = 1.0f; }

	bool				m_bSound;
};

