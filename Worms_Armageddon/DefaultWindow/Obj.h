#pragma once
#include "Define.h"
#include "Mover.h"
#include "MyVector2.h"
#include "Enum.h"
#include <vector>

class CState;

class CObj
{
public:
	CObj();
	virtual ~CObj();

	virtual	void			Initialize(void) PURE;
	virtual	void			Update(void) PURE;
	virtual	void			LateUpdate(void) PURE;
	virtual void			Release(void) PURE;
	virtual void			Render(HDC _hDC) PURE;
	virtual void			Update_Rect(void);
	virtual void			MapOut(void) PURE;


	CMyVector2&				Get_Pos(void) { return m_vPos; }
	CMyVector2*				Get_pPos(void) { return &m_vPos; }
	void					Set_Pos(CMyVector2 _vPos) { m_vPos = _vPos; }

	vector<bool>&			Get_BoundingBox(void) { return m_vecBoundingBox; }
	vector<bool>*			Get_pBoundingBox(void) { return &m_vecBoundingBox; }

	CMover*					Get_Mover(void) { return m_pMover; }
	//ENUM
	void					Set_ObjType(OBJ_TYPE _ObjType) { m_ObjType = _ObjType; }
	OBJ_TYPE				Get_ObjTyep(void) { return m_ObjType; }

	void					Set_ObjDir(OBJ_DIR _ObjDir) { m_ObjDir = _ObjDir; }
	OBJ_DIR					Get_ObjDir(void) { return m_ObjDir; }
	OBJ_DIR*				Get_pObjDir(void) { return &m_ObjDir; }

	CMyVector2&				Get_Collision(void) { return m_vCollision; }

	bool					Is_Dead(void) { return m_bDead; }
	void					Set_Dead(void) { m_bDead = true; }

	void					Set_Alive(void) { m_bDead = false; }

	bool*					Get_bBombCollision(void) { return &m_bBombCollision; }

	bool*					Get_bMapCollision(void) { return &m_bMapCollision; }

	CMyVector2*				Get_pClosest(void) { return &m_vClosest; }

	int*					Get_pGetDamage(void) { return &m_iGetDamage; }

	CObj**					Get_pCollObj(void) { return &m_pCollObj; }
	
	//맵 충돌


	//라인

	void					Set_MapCollision(float _fX, float _fY) { m_bMapCollision = true; m_vClosest.fX = _fX; m_vClosest.fY = _fY; } 
	vector<bool>&			Get_LinePixelX(void) { return m_vecPixelX; }
	vector<bool>&			Get_LinePixelY(void) { return m_vecPixelY; }

	vector<bool>*			Get_pLinePixelX(void) { return &m_vecPixelX; }
	vector<bool>*			Get_pLinePixelY(void) { return &m_vecPixelY; }

	float					Get_fLineLength(void) { return m_fLineLength; }
	float*					Get_pLineLength(void) { return &m_fLineLength; }

	//4바운딩박스
	vector<bool>*			Get_LeftBox(void) { return &m_vecLeftBox; }
	vector<bool>*			Get_TopBox(void) { return &m_vecTopBox; }
	vector<bool>*			Get_RightBox(void) { return &m_vecRightBox; }
	vector<bool>*			Get_BottomBox(void) { return &m_vecBottomBox; }
	int						Get_BoxDistance(void) { return m_iBoxDistance; }

	//폭탄 충돌
	void					Set_BombCollision(CMyVector2& _vExplosion, int _iDamage, CObj* _pCollObj) { m_bBombCollision = true; m_vExplosion = _vExplosion; m_iGetDamage = _iDamage; m_pCollObj = _pCollObj; }
	CMyVector2*				Get_vExplosion(void) { return &m_vExplosion; }

	bool					Is_Action(void) { return m_bAction; }

	bool					Is_CanCollision(void) { return m_bCanCollision; }
protected:
	CMover*					m_pMover;
	RECT					m_tRect;
	CMyVector2				m_vPos;

	//ENUM
	OBJ_TYPE				m_ObjType;
	OBJ_DIR					m_ObjDir;

	//충돌 정보
	CMyVector2				m_vClosest;
	bool					m_bMapCollision;

	vector<bool>			m_vecBoundingBox;
	CMyVector2				m_vCollision;

	//점충돌
	vector<bool>			m_vecPixelX;
	vector<bool>			m_vecPixelY;
	float					m_fLineLength;

	//4바운딩
	vector<bool>			m_vecLeftBox;
	vector<bool>			m_vecTopBox;
	vector<bool>			m_vecRightBox;
	vector<bool>			m_vecBottomBox;
	int						m_iBoxDistance;

	//폭탄 충돌
	bool					m_bBombCollision;
	CMyVector2				m_vExplosion;
	CObj*					m_pCollObj;

	//삭제
	bool					m_bDead;

	//스테이트
	vector<CState*>			m_vecState;

	int						m_iGetDamage;

	bool					m_bAction;

	bool					m_bCanCollision;
private:
	
};

