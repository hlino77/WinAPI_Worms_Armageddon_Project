#pragma once
#include "Sprite.h"
class CSprite_Effect_Circle : public CSprite
{
public:
	CSprite_Effect_Circle();
	virtual ~CSprite_Effect_Circle();

	virtual void				Initialize(CObj * _pObj) override;
	virtual void				Update(void) override;
	virtual void				LateUpdate(void) override;
	virtual void				Render(HDC _hDC) override;
	virtual void				Set_Size(void) override;


	void						Set_Circle(CIRCLE_EFFECT_TYPE _CircleType, CMyVector2 _vPos);
private:
	

};

