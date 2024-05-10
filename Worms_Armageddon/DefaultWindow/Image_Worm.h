#pragma once
#include "MyImage.h"
class CImage_Worm : public CMyImage
{
public:
	CImage_Worm();
	virtual ~CImage_Worm();


	virtual void Initialize(CObj * _pObj) override PURE;
	virtual void Update(void) override PURE;
	virtual void LateUpdate(void) override PURE;
	virtual void Render(HDC _hDC) override PURE;
	virtual void Set_Size(void) override PURE;
	virtual void Reset(void) override PURE;
protected:
	void			Set_Angle(void);

private:
	



};

