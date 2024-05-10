#pragma once
#include "Image_Worm.h"
class CImage_Worm_Flying : public CImage_Worm
{
public:
	CImage_Worm_Flying();
	virtual ~CImage_Worm_Flying();

	virtual void Initialize(CObj * _pObj) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Set_Size(void) override;
	virtual void Reset(void) override;

private:

	void			Set_Dir(void);
};

