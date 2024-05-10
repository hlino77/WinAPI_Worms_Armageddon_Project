#pragma once
#include "Sprite.h"
class CSprite_Basehit : public CSprite
{
public:
	CSprite_Basehit();
	virtual ~CSprite_Basehit();


	virtual void Initialize(CObj * _pObj) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Set_Size(void) override;



	void						Set_Basehit(CMyVector2 _vPos);
private:

};

