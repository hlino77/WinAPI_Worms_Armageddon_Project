#pragma once
#include "MyImage.h"
class CImage_Inventory : public CMyImage
{
public:
	CImage_Inventory();
	virtual ~CImage_Inventory();

	virtual void Initialize(CObj * _pObj) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Set_Size(void) override;
	virtual void Reset(void) override;
	

	void					Set_Pos(CMyVector2* _pPos) { m_pPos = _pPos; }
private:
	CMyVector2*				m_pPos;
};

