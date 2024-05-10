#pragma once
#include "MyImage.h"

class CMyButton
{
public:
	CMyButton();
	virtual ~CMyButton();

	virtual void		Initialize(POINT* _pMouse) PURE;
	virtual void		Update(void) PURE;
	virtual void		LateUpdate(void) PURE;
	virtual void		Release(void) PURE;
	virtual void		Render(HDC _hDC) PURE;

protected:
	void				MouseUpdate(void);


	CMyVector2			m_vPos;
	bool				m_bMouseIn;
	POINT*				m_pMouse;
	HDC					m_Button;
	HDC					m_Border;

	bool				m_bSound;
};

