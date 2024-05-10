#pragma once
#include "Obj.h"
#include "MyImage.h"
#include "Inventory.h"


class CUIMgr
{
public:
	CUIMgr();
	~CUIMgr();

	static CUIMgr*		Get_Inst(void)
	{
		if (!m_pInstance)
			m_pInstance = new CUIMgr;

		return m_pInstance;
	}
	static void		Destroy_Inst(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}

	}


	void						Initialize(void);
	void						Update(void);
	void						LateUpdate(void);
	void						Render(HDC _hDC);
	void						Release(void);
	
	void						Set_UIRend(bool _UIRend) { m_bUIRend = _UIRend; }

	void						Get_Inventory(CInventory* _pInventory);
private:
	static CUIMgr*							m_pInstance;

	//Ã¼·Â UI
	void						Render_Hp(HDC _hDC);
	CMyImage*					m_pHpBox;
	CMyImage*					m_pFont;
	
	list<CObj*>*							m_pObjList;

	bool						m_bUIRend;


	void						Render_Inventory(HDC _hDC);
	bool						m_bInven;


	CInventory*					m_pInventory;
	void						Inventory_Update(void);
	void						Select_Inventory(void);
	void						Inventory_KeyInput(void);
	CMyVector2					m_vInvenPos;
	CMyImage*					m_pInvenImage;


	INVEN_UI_STATE				m_InvenState;
};

