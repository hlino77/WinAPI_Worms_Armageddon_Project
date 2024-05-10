#pragma once
#include "Sprite.h"
class CSprite_Sheep : public CSprite
{
public:
	CSprite_Sheep();
	virtual ~CSprite_Sheep();


	virtual void Initialize(CObj * _pObj) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Set_Size(void) override;


	void		Change_Dir(void);
private:
	
};

