#pragma once
#include "Obj.h"
#include "Image_Structure.h"

class CObj_Structure : public CObj
{
public:
	CObj_Structure();
	virtual ~CObj_Structure();


	virtual void			Initialize(void) override;
	virtual void			Update(void) override;
	virtual void			LateUpdate(void) override;
	virtual void			Release(void) override;
	virtual void			Render(HDC _hDC) override;
	virtual void			MapOut(void) override;

	void					Set_Structure(CMyVector2 _vPos);
	void					Delete_Structure(CMyVector2 _vExplosion);
private:
	
	CMyImage*				m_pStructure;



};

