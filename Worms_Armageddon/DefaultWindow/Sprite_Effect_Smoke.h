#pragma once
#include "Sprite.h"
class CSprite_Effect_Smoke : public CSprite
{
public:
	CSprite_Effect_Smoke();
	virtual ~CSprite_Effect_Smoke();

	virtual void Initialize(CObj * _pObj) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Set_Size(void) override;


	void						Set_Smoke(SMOKE_EFFECT_TYPE _SmokeType, CMyVector2 _vPos);
private:
	float						m_fSpeedX;
	float						m_fSpeedY;

};

