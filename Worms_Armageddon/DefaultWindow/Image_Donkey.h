#pragma once
#include "MyImage.h"
class CImage_Donkey : public CMyImage
{
public:
	CImage_Donkey();
	virtual ~CImage_Donkey();
 
	virtual void Initialize(CObj * _pObj) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Set_Size(void) override;
	virtual void Reset(void) override;

private:

};

