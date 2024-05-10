#pragma once
#include "Sprite.h"
class CSprite_Star : public CSprite
{
public:
	CSprite_Star();
	virtual ~CSprite_Star();

	virtual void Initialize(CObj * _pObj) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Set_Size(void) override;


	void						Set_Star(CMyVector2 _vPos);
private:
	CMyVector2					m_vDir;

	void						Make_Dir(void);
};

