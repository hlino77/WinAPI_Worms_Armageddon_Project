#pragma once
#include "Obj.h"
#include "Sprite.h"

class CObj_Map : public CObj
{
public:
	CObj_Map();
	virtual ~CObj_Map();

	virtual void			Initialize(void) override;
	virtual void			Update(void) override;
	virtual void			LateUpdate(void) override;
	virtual void			Release(void) override;
	virtual void			Render(HDC _hDC) override;
	virtual void			MapOut(void) override {};



	HDC&					Get_BackDC(void) { return m_hBackDC; }
	vector<bool>*			Get_MapInfo(void) { return &m_vecMapInfo; }


	void					Delete_Map(CMyVector2 _vExplosion);

	void					Make_Sea(void);
private:
	HDC								m_hMapDC;
	HDC								m_hBackDC;

	HDC								m_hWaterBackDC;
	HBITMAP							m_BackOldMap;
	
	void							Set_BackDC(void);


	vector<list<CSprite*>>			m_vecSeaList;


	float							m_fMapX;
	float							m_fMapY;

	vector<bool>					m_vecMapInfo;
};

