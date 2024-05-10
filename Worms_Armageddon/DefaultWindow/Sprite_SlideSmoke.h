#pragma once
#include "Sprite.h"
class CSprite_SlideSmoke : public CSprite
{
public:
	CSprite_SlideSmoke();
	virtual ~CSprite_SlideSmoke();


	virtual void Initialize(CObj * _pObj) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Set_Size(void) override;


	void						Set_Smoke(CMyVector2 _vPos);
private:
	float			m_fSpeedY;

};

