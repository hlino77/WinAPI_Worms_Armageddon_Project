#pragma once
#include "MyImage.h"
class CImage_Bazooka : public CMyImage
{
public:
	CImage_Bazooka();
	virtual ~CImage_Bazooka();

	virtual void			Initialize(CObj * _pObj) override;
	virtual void			Update(void) override;
	virtual void			LateUpdate(void) override;
	virtual void			Render(HDC _hDC) override;
	virtual void			Set_Size(void) override;
	virtual void			Reset(void) override;



private:
	void					Set_Angle(void);
};

