#pragma once
#include "Sprite.h"
class CSprite_Effect_Ellipse : public CSprite
{
public:
	CSprite_Effect_Ellipse();
	virtual ~CSprite_Effect_Ellipse();

	virtual void Initialize(CObj * _pObj) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Set_Size(void) override;


	void						Set_Ellipse(ELLIPSE_EFFECT_TYPE _EllipseType, CMyVector2 _vPos);
private:
};

