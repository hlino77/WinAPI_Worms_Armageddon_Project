#pragma once
#include "Sprite.h"
class CSprite_BackPraticle : public CSprite
{
public:
	CSprite_BackPraticle();
	virtual ~CSprite_BackPraticle();



	virtual void Initialize(CObj * _pObj) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Set_Size(void) override;


private:

};

