#pragma once
#include "Obj.h"
#include "Sprite.h"

class CObj_BackParticle : public CObj
{
public:
	CObj_BackParticle();
	virtual ~CObj_BackParticle();

	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Release(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void MapOut(void) override;


private:
	void					Set_Speed(void);
	void					Set_Pos(void);
	void					Set_RandomPos(void);
	void					Reset_Particle(void);
	void					Make_Particle(void);

	WIND_DIR				m_WindDir;
	int						m_iWindSpeed;

	CSprite*				m_pSprite;


	//바람타기
	DWORD					m_YDelay;
	DWORD					m_YTime;
	float					m_fPlusY;
};

