#pragma once
#include "Obj.h"
#include "Sprite_Cloud.h"


class CObj_Cloud : public CObj
{
public:
	CObj_Cloud();
	virtual ~CObj_Cloud();


	virtual void			Initialize(void) override;
	virtual void			Update(void) override;
	virtual void			LateUpdate(void) override;
	virtual void			Release(void) override;
	virtual void			Render(HDC _hDC) override;
	virtual void			MapOut(void) override;


	CLOUD_TYPE				Get_CloudType(void) { return m_CloudType; }
private:
	void					Set_CloudType(void);
	void					Set_Speed(void);
	void					Set_Pos(void);


	void					Reset_Cloud(void);

	CLOUD_TYPE				m_CloudType;

	WIND_DIR				m_WindDir;
	int						m_iWindSpeed;

	CSprite*				m_pSprite;
};

