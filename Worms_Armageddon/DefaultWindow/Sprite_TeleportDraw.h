#pragma once
#include "Sprite.h"
class CSprite_TeleportDraw : public CSprite
{
public:
	CSprite_TeleportDraw();
	virtual ~CSprite_TeleportDraw();


	virtual void Initialize(CObj * _pObj) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Set_Size(void) override;


	void			Draw_Reset(void) { m_iCurr = 0; m_SpriteState = SPRITE_STATE::START; }
private:
	void			Set_SpriteAngle(void);
};

