#pragma once
#include "Sprite.h"
class CSprite_TeleWork : public CSprite
{
public:
	CSprite_TeleWork();
	virtual ~CSprite_TeleWork();


	virtual void Initialize(CObj * _pObj) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Set_Size(void) override;

	bool			Get_Reverse(void) { return m_bReverse; }
	void			Set_Reverse(void) { m_bReverse = true; m_SpriteState = SPRITE_STATE::START; }
private:
	bool			m_bReverse;

	void			Set_SpriteAngle(void);
};

