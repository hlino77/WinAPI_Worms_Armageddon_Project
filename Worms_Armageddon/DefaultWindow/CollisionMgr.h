#pragma once
#include "Obj.h"

class CCollisionMgr
{
private:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static CCollisionMgr*		Get_Inst(void)
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CCollisionMgr;
		}
		return m_pInstance;
	}

	static void					Destroy_Inst(void)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}

	void				Update(void);
	void				LateUpdate(void);
	void				Initialize(void);
	void				Release(void);





private:
	//¸Ê°ú ¿ÀºêÁ§Æ®ÀÇ Ãæµ¹
	bool						MapCollision(OBJ_TYPE _ObjType ,list<CObj*>* _pObjList);
	bool						Worm_MapCollision_Box(CObj* _pObj);
	bool						Worm_MapCollision_Line(CObj* _pObj);
	bool						Worm_MapCollision_4Box(CObj* _pObj);
	bool						Obj_MapCollision(CObj* _pObj);
	bool						Sheep_MapCollision(CObj* _pObj);

	//ÆøÅº°ú ¿úÀÇ Ãæµ¹
	bool						Worm_Projectile_Collision(void);
	bool						W_P_Collision(CObj* _pWorm, CObj* _pProjectile);

	static CCollisionMgr*		m_pInstance;

	CObj*						m_pMap;
	HDC							m_hBackDC;
	vector<bool>*				m_vecMapInfo;
};

