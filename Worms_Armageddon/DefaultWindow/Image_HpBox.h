#pragma once
#include "MyImage.h"
class CImage_HpBox : public CMyImage
{
public:
	CImage_HpBox();
	virtual ~CImage_HpBox();


	virtual void Initialize(CObj * _pObj) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Set_Size(void) override;
	virtual void Reset(void) override;

	void				Size_Render(HDC _hDC, CMyVector2 _pInfo,int _iSize);
private:



};

