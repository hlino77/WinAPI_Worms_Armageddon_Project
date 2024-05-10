#pragma once
#include "Sprite.h"
class CSprite_Effect_Exhaust : public CSprite
{
public:
	CSprite_Effect_Exhaust();
	virtual ~CSprite_Effect_Exhaust();
	

	virtual void Initialize(CObj * _pObj) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Set_Size(void) override;

	void						Set_Exhaust(EXHAUST_EFFECT_TYPE _ExhaustType, CMyVector2 _vPos);

private:
	
};

