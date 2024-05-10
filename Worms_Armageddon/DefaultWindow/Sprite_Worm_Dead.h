#pragma once
#include "Sprite.h"
class CSprite_Worm_Dead : public CSprite
{
public:
	CSprite_Worm_Dead();
	virtual ~CSprite_Worm_Dead();

	virtual void Initialize(CObj * _pObj) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Set_Size(void) override;

private:

};

