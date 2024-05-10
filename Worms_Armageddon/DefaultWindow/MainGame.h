#pragma once

#include "Define.h"


class CMainGame
{
public:
	void		Initialize(void);
	void		Update(void);
	void		LateUpdate(void);
	void		Render();
	void		Release(void);


	bool		Is_End(void) { return m_bEnd; }
private:
	HDC					m_DC;
	HDC					m_hMemDC;

	HBITMAP				m_hOldmap;
	HBITMAP				m_hBitmap;

	bool				m_bEnd;
public:
	CMainGame();
	~CMainGame();
};

