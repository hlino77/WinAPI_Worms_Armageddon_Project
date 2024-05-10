#pragma once
#include "Sprite.h"
class CSprite_Marker : public CSprite
{
public:
	CSprite_Marker();
	virtual ~CSprite_Marker();

	virtual void Initialize(CObj * _pObj) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Set_Size(void) override;


	void				Set_Marker(CMyVector2 _pPos) { m_vPos = _pPos; }
private:
	CMyVector2			m_vPos;
};

