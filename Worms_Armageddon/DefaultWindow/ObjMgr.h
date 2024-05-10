#pragma once
#include "Enum.h"
#include <map>
#include "Obj.h"

class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	static CObjMgr*		Get_Inst(void)
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;

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



	void					Initialize(void);
	void					Update(void);
	void					LateUpdate(void);
	void					Release(void);
	void					Render(HDC _hDC);
	

	void					Add_Obj(OBJ_TYPE _ObjType, CObj* _pObj);
	void					Delete_Obj(OBJ_TYPE _ObjType, CObj* _pObj);
	list<CObj*>*			Get_ObjList(OBJ_TYPE _ObjType) { return &(m_Obj_List[(UINT)_ObjType]); }
	list<CObj*>*			Get_ObjList(UINT _ObjType) { return &(m_Obj_List[_ObjType]); }

	void					Get_Flame(CMyVector2 _vPos, int iCount);

	void					Delete_Structure(CMyVector2 _vExplosion);

private:
	static CObjMgr*						m_pInstance;
	map<UINT, list<CObj*>>				m_Obj_List;


	void								Initialize_Flame(void);
	list<CObj*>							m_FlameList;
	list<CObj*>::iterator				m_Flameiter;
};

