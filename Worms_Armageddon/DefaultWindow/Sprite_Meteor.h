#pragma once
#include "Sprite.h"
class CSprite_Meteor : public CSprite
{
public:
	CSprite_Meteor();
	virtual ~CSprite_Meteor();


	virtual void Initialize(CObj * _pObj) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Set_Size(void) override;

private:

};

