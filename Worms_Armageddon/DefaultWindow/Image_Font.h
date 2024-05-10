#pragma once
#include "MyImage.h"
class CImage_Font : public CMyImage
{
public:
	CImage_Font();
	virtual ~CImage_Font();

	virtual void Initialize(CObj * _pObj) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Set_Size(void) override;
	virtual void Reset(void) override;

	void					Render_Num(HDC _hDC, int _iNum,int _iFont ,CMyVector2 _pInfo);
private:

};

