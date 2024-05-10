#pragma once
#include "MyButton.h"
class CButton_Options : public CMyButton
{
public:
	CButton_Options();
	virtual ~CButton_Options();


	virtual void Initialize(POINT * _pMouse) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Release(void) override;
	virtual void Render(HDC _hDC) override;

private:

};

