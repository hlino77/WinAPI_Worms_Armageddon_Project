#pragma once
#include "Obj.h"
#include "Animator_Worm.h"
#include "Weapon.h"
#include "Inventory.h"

class CObj_Worm : public CObj
{
public:
	CObj_Worm();
	virtual ~CObj_Worm() override;

	virtual void			Initialize(void) override;
	virtual void			Update(void) override;
	virtual void			LateUpdate(void) override;
	virtual void			Release(void) override;
	virtual void			Render(HDC _hDC) override;
	virtual	void			Update_Rect(void) override;
	virtual void			MapOut(void) override {};
	


	void					Set_State(WORM_STATE _State) { m_CurrState = _State; }
	WORM_STATE				Get_State(void) { return m_CurrState; }
	WORM_STATE*				Get_pState(void) { return &m_CurrState; }


	CMyVector2*				Get_pBottom(void) { return &m_vBottom; }
	CMyVector2&				Get_Bottom(void) { return m_vBottom; }


	CWeapon**				Get_ppWeapon(void) { return &m_pWeapon; }
	CWeapon*				Get_Weapon(void) { return m_pWeapon; }
	void					Set_Weapon(CWeapon* _pWeapon) { m_pWeapon = _pWeapon; }

	CAnimator*				Get_Animator(void) { return m_pAnimator; }

	float					Get_LeftAngle(void) { return m_fLeftAngle; }
	float					Get_RightAngle(void) { return m_fRightAngle; }

	float*					Get_pLeftAngle(void) { return &m_fLeftAngle; }
	float*					Get_pRightAngle(void) { return &m_fRightAngle; }

	bool*					Get_pRightMove(void) { return &m_bRightMove; }
	bool*					Get_pLeftMove(void) { return &m_bLeftMove; }

	WORM_JUMP_STATE*		Get_pJumpState(void) { return &m_JumpState; }
	WORM_JUMP_STATE			Get_JumpState(void) { return m_JumpState; }
	void					Set_JumpState(WORM_JUMP_STATE _JumpState) { m_JumpState = _JumpState; }

	float					Get_WormAngle(void) { return m_fWormAngle; }

	int						Get_WormHp(void) { return m_iWormHp; }
	int*					Get_pWormHp(void) { return &m_iWormHp; }

	void					Set_TeamNum(int _iTeamNum) { m_iTeamNum = _iTeamNum; }
	int						Get_TeamNum(void) { return m_iTeamNum; }

	bool*					Get_pTurn(void) { return &m_bTurn; }
	void					Set_Turn(bool _bTurn) { m_bTurn = _bTurn; }

	void					Put_Weapon(void) { m_bPutWeapon = true; };

	int*					Get_pDamage(void) { return &m_iDamage; }
	bool*					Get_pDamaged(void) { return &m_bDamaged; }
	bool*					Get_pAction(void) { return &m_bAction; }

	CInventory*				Get_Inventory(void) { return m_pInventory; }

	void					Get_Damage(void);
	bool					Is_Damaged(void) { return m_bDamaged; }

	bool*					Get_pBaseHit(void) { return &m_bBaseHit; }

	void					Dead(void);
private:
	CMyVector2				m_vBottom;
	float					m_fBottomLength;

	CAnimator*				m_pAnimator;

	WORM_STATE				m_CurrState;

	void					Set_Bottom(void) { m_vBottom.fX = m_vPos.fX; m_vBottom.fY = m_vPos.fY + m_fBottomLength; }


	//맵 충돌 처리

	float					m_fLeftAngle;
	float					m_fRightAngle;

	float					m_fLeftX;
	float					m_fLeftY;
	float					m_fRightX;
	float					m_fRightY;

	float					m_fCenterX;
	float					m_fCenterY;

	float					Get_Radian(float _fWidth, float _fHeight) { float fLength = sqrt(_fWidth * _fWidth + _fHeight * _fHeight); return acosf(_fWidth / fLength); }

	bool					m_bLeftMove;
	bool					m_bRightMove;



	//무기
	CWeapon*				m_pWeapon;


	WORM_JUMP_STATE			m_JumpState;

	float					m_fWormAngle;

	void					Set_WormAngle(void);


	void					Set_WormDir(void);

	int						m_iWormHp;


	//턴
	int						m_iTeamNum;
	bool					m_bTurn;

	bool					m_bPutWeapon;

	//데미지
	bool					m_bDamaged;
	int						m_iDamage;
	

	//
	CInventory*				m_pInventory;

	
	bool					m_bBaseHit;
};

