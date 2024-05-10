#pragma once
#include "Sprite.h"
class CSprite_Worm_Slide : public CSprite
{
public:
	CSprite_Worm_Slide();
	virtual ~CSprite_Worm_Slide();

	virtual void Initialize(CObj * _pObj) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Set_Size(void) override;

	void			Set_bSlideEnd(void) { m_bSlideEnd = true; }
	bool			Is_End(void) { return m_bEnd; }
	void			Reset_Slide(void);
private:
	void			Change_Dir(void);

	void			Set_SlideAngle(void);

	void			Set_Slide(void);
	void			Set_SlideEnd(void);

	void			Set_SlideEndAngle(void);

	WORM_SLIDE_STATE		m_SlideState;

	bool			m_bSlideEnd;
	bool			m_bEnd;
};

