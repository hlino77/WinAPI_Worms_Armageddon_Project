#pragma once
#include "Define.h"

class CScene
{
public:
	CScene();
	virtual ~CScene();


	virtual void					Update(void) PURE;
	virtual void					LateUpdate(void) PURE;
	virtual void					Initialize(void) PURE;
	virtual void					Release(void) PURE;
	virtual void					Enter(void) PURE;
	virtual void					Render(HDC _hDC) PURE;
	virtual void					Exit(void) PURE;
protected:
};

