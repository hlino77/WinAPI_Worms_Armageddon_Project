#pragma once
#include "State.h"
#include "Obj_Worm.h"
#include "Animator.h"

class CState_Worm : public CState
{
public:
	CState_Worm();
	virtual ~CState_Worm();

	virtual void			Initialize(CObj * _pOwner) PURE;
	virtual void			Update(void) override PURE;
	virtual void			LateUpdate(void) override PURE;
	virtual void			Release(void) override PURE;
	virtual	void			Key_Input(void) PURE;
protected:
	CMover*					m_pOwnerMover;
	CWeapon**				m_pWeapon;
	CMyVector2*				m_pExplosion;
	CMyVector2*				m_pBottom;
	CMyVector2*				m_pClosest;
	vector<bool>*			m_pBoundingBox;
	WORM_STATE*				m_pWormState;
	WORM_JUMP_STATE*		m_pJumpState;


	bool*					m_pBombCollision;
	bool*					m_pMapCollision;

	float*					m_pLeftAngle;
	float*					m_pRightAngle;

	bool*					m_pLeftMove;
	bool*					m_pRightMove;

	float					Get_Radian(float _fWidth, float _fHeight) { float fLength = sqrt(_fWidth * _fWidth + _fHeight * _fHeight); return acosf(_fWidth / fLength); }


	vector<bool>*			m_pLinePixelX;
	vector<bool>*			m_pLinePixelY;
	float*					m_pLineLength;

	bool*					m_pTurn;

	bool*					m_pDamaged;
	int*					m_pDamage;
	bool*					m_pAction;
	int*					m_pGetDamage;
	int*					m_pHp;

	void					DefaultCollision(void);
	void					BaseCollision(void);
	void					BombCollision(void);
	void					Set_Owner(CObj * _pOwner);

	CInventory*				m_pInventory;
	CAnimator*				m_pAnimator;

	vector<bool>*			m_pLeftBox;
	vector<bool>*			m_pTopBox;
	vector<bool>*			m_pRightBox;
	vector<bool>*			m_pBottomBox;
	int						m_iBoxDistance;

	CObj**					m_pCollObj;
	bool*					m_pBaseHit;
};

