#include "stdafx.h"
#include "State_Worm.h"
#include "Obj_Projectile.h"
#include "Obj_Projectile_Baseball.h"
#include "EffectMgr.h"
#include "SoundMgr.h"

CState_Worm::CState_Worm()
	:m_pOwnerMover(nullptr), m_pWeapon(nullptr), m_pBombCollision(nullptr),m_pExplosion(nullptr), m_pMapCollision(nullptr),
	m_pLeftAngle(nullptr), m_pRightAngle(nullptr), m_pBottom(nullptr), m_pClosest(nullptr), m_pBoundingBox(nullptr), m_pRightMove(nullptr), m_pLeftMove(nullptr),m_pWormState(nullptr),
	m_pJumpState(nullptr), m_pLinePixelX(nullptr), m_pLinePixelY(nullptr), m_pLineLength(nullptr), m_pTurn(nullptr), m_pDamage(nullptr), m_pDamaged(nullptr), m_pAction(nullptr),
	m_pGetDamage(nullptr), m_pHp(nullptr), m_pInventory(nullptr), m_pAnimator(nullptr), m_pLeftBox(nullptr), m_pRightBox(nullptr), m_pTopBox(nullptr), m_pBottomBox(nullptr), m_pCollObj(nullptr)
{
}


CState_Worm::~CState_Worm()
{
}

void CState_Worm::DefaultCollision(void)
{
	CMyVector2		m_vDir = { m_pPos->fX - m_pExplosion->fX ,  fabs(m_pPos->fY - m_pExplosion->fY) * -1.0f };

	float fLength = sqrt((m_vDir.fX * m_vDir.fX) + (m_vDir.fY * m_vDir.fY));

	m_vDir.Normalize();

	m_vDir *= ((m_pExplosion->fCX * 40.0f) * (20 / fLength));

	m_pOwnerMover->Stop();
	m_pOwnerMover->AddForce(CMyVector2(m_vDir.fX, m_vDir.fY));

	if (m_vDir.fY < -1000.0f)
		*m_pWormState = WORM_STATE::FlYING;
	else
		*m_pWormState = WORM_STATE::SLIDE;


	CSoundMgr::Get_Instance()->Random_WormHit();

	//초기화
	*m_pBombCollision = false;
	*m_pExplosion = { 0.0f,0.0f };

	*m_pGetDamage -= (0.1f * fLength);
	if (*m_pGetDamage > 0.0f)
	{
		*m_pDamage += *m_pGetDamage;
		*m_pGetDamage = 0;
		*m_pDamaged = true;
	}
	*m_pAction = true;
	*m_pCollObj = nullptr;
}

void CState_Worm::BaseCollision(void)
{
	if (static_cast<CObj_Projectile_Baseball*>(*m_pCollObj)->Get_Owner() == m_pOwner)
	{
		*m_pBombCollision = false;
		*m_pExplosion = { 0.0f,0.0f };

		*m_pGetDamage = 0;
		*m_pDamaged = false;
		*m_pAction = false;
		*m_pCollObj = nullptr;
		return;
	}
	else
	{
		CMyVector2		m_vDir = static_cast<CObj_Projectile_Baseball*>(*m_pCollObj)->Get_Dir();

		m_vDir *= static_cast<CObj_Projectile_Baseball*>(*m_pCollObj)->Get_Power();

		m_pOwnerMover->Stop();
		m_pOwnerMover->AddForce(CMyVector2(m_vDir.fX, m_vDir.fY));

	
		*m_pWormState = WORM_STATE::FlYING;
		CCameraMgr::Get_Inst()->Follow_Target(m_pOwner);

		CEffectMgr::Get_Inst()->Get_Basehit(*m_pPos);
	

		//초기화
		*m_pBombCollision = false;
		*m_pExplosion = { 0.0f,0.0f };

		*m_pDamage += *m_pGetDamage;
		*m_pGetDamage = 0;
		*m_pDamaged = true;
		*m_pAction = true;
		*m_pCollObj = nullptr;

		CSoundMgr::Get_Instance()->StopSound(CHANNELID::PROJECTILE);
		CSoundMgr::Get_Instance()->PlaySoundW(L"BaseBallBatImpact.wav", CHANNELID::PROJECTILE, g_fVolume);

		CSoundMgr::Get_Instance()->StopSound(CHANNELID::WORMSOUND1);
		CSoundMgr::Get_Instance()->PlaySoundW(L"OW1.WAV", CHANNELID::WORMSOUND1, g_fVolume);

		*m_pBaseHit = true;
	}
}

void CState_Worm::BombCollision(void)
{
	//충돌처리
	switch (dynamic_cast<CObj_Projectile*>(*m_pCollObj)->Get_WeaponType())
	{
	case WEAPON_TYPE::BASEBALL:
		BaseCollision();
		break;
	default:
		DefaultCollision();
		break;
	}
}

void CState_Worm::Set_Owner(CObj * _pOwner)
{
	m_pOwner = _pOwner;
	m_pOwnerMover = _pOwner->Get_Mover();
	m_pBombCollision = _pOwner->Get_bBombCollision();
	m_pExplosion = _pOwner->Get_vExplosion();
	m_pMapCollision = _pOwner->Get_bMapCollision();
	m_pBottom = static_cast<CObj_Worm*>(_pOwner)->Get_pBottom();
	m_pBoundingBox = _pOwner->Get_pBoundingBox();
	m_pPos = _pOwner->Get_pPos();
	m_pRightMove = static_cast<CObj_Worm*>(_pOwner)->Get_pRightMove();
	m_pLeftMove = static_cast<CObj_Worm*>(_pOwner)->Get_pLeftMove();
	m_pObjDir = _pOwner->Get_pObjDir();
	m_pWormState = static_cast<CObj_Worm*>(_pOwner)->Get_pState();
	m_pWeapon = static_cast<CObj_Worm*>(_pOwner)->Get_ppWeapon();
	m_pLeftAngle = static_cast<CObj_Worm*>(_pOwner)->Get_pLeftAngle();
	m_pRightAngle = static_cast<CObj_Worm*>(_pOwner)->Get_pRightAngle();
	m_pClosest = _pOwner->Get_pClosest();
	m_pJumpState = static_cast<CObj_Worm*>(_pOwner)->Get_pJumpState();
	m_pLinePixelX = static_cast<CObj_Worm*>(_pOwner)->Get_pLinePixelX();
	m_pLinePixelY = static_cast<CObj_Worm*>(_pOwner)->Get_pLinePixelY();
	m_pLineLength = static_cast<CObj_Worm*>(_pOwner)->Get_pLineLength();
	m_pTurn = static_cast<CObj_Worm*>(_pOwner)->Get_pTurn();
	m_pDamage = static_cast<CObj_Worm*>(_pOwner)->Get_pDamage();
	m_pDamaged = static_cast<CObj_Worm*>(_pOwner)->Get_pDamaged();
	m_pAction = static_cast<CObj_Worm*>(_pOwner)->Get_pAction();
	m_pGetDamage = _pOwner->Get_pGetDamage();
	m_pHp = static_cast<CObj_Worm*>(_pOwner)->Get_pWormHp();
	m_pInventory = static_cast<CObj_Worm*>(_pOwner)->Get_Inventory();
	m_pAnimator = static_cast<CObj_Worm*>(_pOwner)->Get_Animator();
	m_pLeftBox = _pOwner->Get_LeftBox();
	m_pRightBox = _pOwner->Get_RightBox();
	m_pTopBox = _pOwner->Get_TopBox();
	m_pBottomBox = _pOwner->Get_BottomBox();
	m_iBoxDistance = _pOwner->Get_BoxDistance();
	m_pCollObj = _pOwner->Get_pCollObj();
	m_pBaseHit = static_cast<CObj_Worm*>(_pOwner)->Get_pBaseHit();
}

