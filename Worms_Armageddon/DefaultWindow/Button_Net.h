#pragma once
#include "MyButton.h"
class CButton_Net : public CMyButton
{
public:
	CButton_Net();
	virtual ~CButton_Net();


	virtual void Initialize(POINT * _pMouse) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Release(void) override;
	virtual void Render(HDC _hDC) override;
};

