#pragma once
#include "MyImage.h"
class CImage_Hmissile : public CMyImage
{
public:
	CImage_Hmissile();
	virtual ~CImage_Hmissile();

	virtual void Initialize(CObj * _pObj) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Set_Size(void) override;
	virtual void Reset(void) override;

private:
	void					Set_Angle(void);

	HMISSILE_TYPE*			m_pOwnerHmissile;

	bool					m_bChange;
};

