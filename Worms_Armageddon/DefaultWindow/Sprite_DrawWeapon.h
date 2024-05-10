#pragma once
#include "Sprite.h"
class CSprite_DrawWeapon : public CSprite
{
public:
	CSprite_DrawWeapon();
	virtual ~CSprite_DrawWeapon();


	virtual void				Initialize(CObj * _pObj) override;
	virtual void				Update(void) override;
	virtual void				LateUpdate(void) override;
	virtual void				Render(HDC _hDC) override;
	virtual void				Set_Size(void) override {};

	void						Set_Weapon(void);
	bool						Is_Idle(void) { return m_bUseIdle; }
private:
	void						Insert_Image(void);

	int							m_iR;
	int							m_iG;
	int							m_iB;


	//바주카
	void						Set_Bazooka(void);
	void						Set_Bazooka_Angle(void);

	//바나나
	void						Set_Banana(void);
	void						Set_Banana_Angle(void);
	
	//무전기
	void						Set_Radio(void);
	void						Set_Radio_Angle(void);

	//야구
	void						Set_Base(void);
	void						Set_Base_Angle(void);

	//홀리
	void						Set_Holy(void);
	void						Set_Holy_Angle(void);

	//구조물
	void						Set_Hat(void);
	void						Set_Hat_Angle(void);

	//양
	void						Set_Sheep(void);
	void						Set_Sheep_Angle(void);

	//메테오
	void						Set_Meteor(void);
	void						Set_Meteor_Angle(void);



	bool						m_bUseIdle;
};

