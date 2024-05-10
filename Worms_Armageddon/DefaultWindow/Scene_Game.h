#pragma once
#include "Scene.h"
class CScene_Game : public CScene
{
public:
	CScene_Game();
	virtual ~CScene_Game();

	// CScene을(를) 통해 상속됨
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Initialize(void) override;
	virtual void Release(void) override;
	virtual void Enter(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Exit(void) override;

private:
	HDC			m_hBackGroundDC;


};

