#pragma once
#include "MyImage.h"
class CImage_Structure : public CMyImage
{
public:
	CImage_Structure();
	virtual ~CImage_Structure();


	virtual void			Initialize(CObj * _pObj) override;
	virtual void			Update(void) override;
	virtual void			LateUpdate(void) override;
	virtual void			Render(HDC _hDC) override;
	virtual void			Set_Size(void) override;
	virtual void			Reset(void) override;

	void					Set_Pos(CMyVector2* _pPos) { m_pPos = _pPos; }

	void					Delete_Structure(CMyVector2 _vExplosion);
private:
	CMyVector2*				m_pPos;

	HBITMAP					m_OldMap;
	HDC						m_hMemDC;
};

