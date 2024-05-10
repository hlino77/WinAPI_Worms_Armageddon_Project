#pragma once
#include "Sprite.h"
#include "Enum.h"

class CSprite_WindUI : public CSprite
{
public:
	CSprite_WindUI();
	virtual ~CSprite_WindUI();


	virtual void Initialize(CObj * _pObj) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Set_Size(void) override;


private:
	void		Left_Render(HDC _hDC);
	void		Right_Render(HDC _hDC);

	HDC			m_hLeftDC;
	HDC			m_hRightDC;

	WIND_DIR	m_WindDir;
	int			m_iSpeed;

	void		Change_WindInfo(void);

	float		m_fLength;
};

