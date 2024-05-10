#pragma once
#include "MyButton.h"
class CButton_Single : public CMyButton
{
public:
	CButton_Single();
	virtual ~CButton_Single();


	virtual void			Initialize(POINT * _pMouse) override;
	virtual void			Update(void) override;
	virtual void			LateUpdate(void) override;
	virtual void			Release(void) override;
	virtual void			Render(HDC _hDC) override;

private:

};

