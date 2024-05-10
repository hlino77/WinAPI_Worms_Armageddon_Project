#pragma once
#include "Scene.h"
#include "MyButton.h"

class CScene_MainMenu : public CScene
{
public:
	CScene_MainMenu();
	virtual ~CScene_MainMenu();

	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Initialize(void) override;
	virtual void Release(void) override;
	virtual void Enter(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Exit(void) override;


	void				Mouse(void);
private:
	HDC					m_MenuBack;
	HDC					m_Title;

	POINT				m_Mouse;

	vector<CMyButton*>		m_vecButtons;
};

