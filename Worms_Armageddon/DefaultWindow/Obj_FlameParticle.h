#pragma once
#include "Obj.h"
#include "Sprite.h"
class CObj_FlameParticle : public CObj
{
public:
	CObj_FlameParticle();
	virtual ~CObj_FlameParticle();


	virtual void			Initialize(void) override;
	virtual void			Update(void) override;
	virtual void			LateUpdate(void) override;
	virtual void			Release(void) override;
	virtual void			Render(HDC _hDC) override;
	virtual void			MapOut(void) override;

	void					Reset(CMyVector2 _vPos);
private:
	void					MakeMove(void);

	CSprite*				m_pSprite;

	DWORD					m_iSmokeTime;
	DWORD					m_iSmokeDelay;
};

