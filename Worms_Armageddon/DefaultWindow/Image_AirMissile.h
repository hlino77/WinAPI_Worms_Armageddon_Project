#pragma once
#include "MyImage.h"
class CImage_AirMissile : public CMyImage
{
public:
	CImage_AirMissile();
	virtual ~CImage_AirMissile();


	virtual void Initialize(CObj * _pObj) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Set_Size(void) override;
	virtual void Reset(void) override;

private:
	void					Set_Angle(void);


	
};

