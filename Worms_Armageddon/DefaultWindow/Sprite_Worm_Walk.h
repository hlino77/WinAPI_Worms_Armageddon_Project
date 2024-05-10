#pragma once
#include "Sprite.h"
class CSprite_Worm_Walk : public CSprite
{
public:
	CSprite_Worm_Walk();
	virtual ~CSprite_Worm_Walk();



	virtual void			 Initialize(CObj * _pObj) override;
	virtual void			 Update(void) override;
	virtual void			 LateUpdate(void) override;
	virtual void			 Render(HDC _hDC) override;


	void					Set_Pos(void) { m_fX = m_pOwner->Get_Pos().fX; m_fY = m_pOwner->Get_Pos().fY; }
	virtual void			Set_Size(void) override {};
private:
	void		Walk_Render(HDC _hDC);
	void		Change_Dir(void);

	//렌더링 시작 포인트
	float		m_fX;
	float		m_fY;


	void		Set_Angle(void);


	bool		m_bExpand;
};

