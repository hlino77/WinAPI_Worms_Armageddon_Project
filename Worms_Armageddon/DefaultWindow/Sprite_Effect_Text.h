#pragma once
#include "Sprite.h"
class CSprite_Effect_Text : public CSprite
{
public:
	CSprite_Effect_Text();
	virtual ~CSprite_Effect_Text();

	virtual void Initialize(CObj * _pObj) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Set_Size(void) override;

	void						Random_Text(CMyVector2 _vPos);
	void						Set_Text(TEXT_EFFECT_TYPE _TextType, CMyVector2 _vPos);
private:

};

