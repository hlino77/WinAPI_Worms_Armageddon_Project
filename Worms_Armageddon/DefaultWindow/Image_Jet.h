#pragma once
#include "MyImage.h"
class CImage_Jet : public CMyImage
{
public:
	CImage_Jet();
	virtual ~CImage_Jet();

	virtual void Initialize(CObj * _pObj) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Set_Size(void) override;
	virtual void Reset(void) override;


	void					Set_JetPos(CMyVector2* _pPos) { m_pJetPos = _pPos; }
private:
	CMyVector2*				m_pJetPos;
};

