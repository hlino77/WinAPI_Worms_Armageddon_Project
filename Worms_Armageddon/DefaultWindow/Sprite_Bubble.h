#pragma once
#include "Sprite.h"
class CSprite_Bubble : public CSprite
{
public:
	CSprite_Bubble();
	virtual ~CSprite_Bubble();

	virtual void Initialize(CObj * _pObj) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Set_Size(void) override;


	void						Random_Bubble(CMyVector2 _vPos);
	void						Set_Bubble(BUBBLE_TYPE _BubbleType, CMyVector2 _vPos);
private:

};

