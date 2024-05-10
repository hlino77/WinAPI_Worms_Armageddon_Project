#pragma once
#include "Scene.h"
class CScene_Intro : public CScene
{
public:
	CScene_Intro();
	virtual ~CScene_Intro();

	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Initialize(void) override;
	virtual void Release(void) override;
	virtual void Enter(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Exit(void) override;

private:
	HWND			m_hVideo;
};

