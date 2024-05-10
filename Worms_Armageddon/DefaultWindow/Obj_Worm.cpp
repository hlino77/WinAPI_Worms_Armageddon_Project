#include "stdafx.h"
#include "Obj_Worm.h"
#include "Template.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Mover.h"
#include <algorithm>
#include <iostream>
#include "Weapon_Bazooka.h"
#include "State_Worm_Idle.h"
#include "State_Worm_Walk.h"
#include "State_Worm_Weapon.h"
#include "State_Worm_Jump.h"
#include "State_Worm_Flying.h"
#include "State_Worm_Slide.h"
#include "EffectMgr.h"
#include "GameMgr.h"
#include "State_Worm_Dead.h"
#include "State_Worm_Winner.h"
#include "State_Worm_Swim.h"
#include "State_Worm_NotTurn.h"
#include "SoundMgr.h"


using namespace std;

CObj_Worm::CObj_Worm()
	:m_pAnimator(nullptr), m_fBottomLength(8.0f), m_fLeftAngle(0.0f), m_bLeftMove(true), m_bRightMove(true), m_fRightAngle(0.0f), m_pWeapon(nullptr), m_iWormHp(100), m_bTurn(false),
	m_bPutWeapon(false), m_bDamaged(false), m_iDamage(0), m_pInventory(nullptr), m_bBaseHit(false)
{
}


CObj_Worm::~CObj_Worm()
{
	Release();
}

void CObj_Worm::Initialize(void)
{
	//애니메이터
	m_pAnimator = new CAnimator_Worm;
	m_pAnimator->Initialize(this);

	m_vPos.fX = rand() % 1200 + MAPPOSX;
	m_vPos.fY = 800.0f;
	m_vPos.fCX = 25.0f;
	m_vPos.fCY = 25.0f;
	
	
	m_vBottom.fX = m_vPos.fX;
	m_vBottom.fY = m_vPos.fY + m_fBottomLength;
	m_vBottom.fCX = 15.0f;
	m_vBottom.fCY = 25.0f;


	//바운딩 박스
	m_vecBoundingBox.resize((UINT)(m_vBottom.fCX * m_vBottom.fCY), false);

	//점 충돌
	m_fLineLength = 31.0f;
	m_vecPixelX.resize(m_fLineLength, false);
	m_vecPixelY.resize(m_fLineLength, false);


	//4바운딩
	m_iBoxDistance = 15.0f;
	m_vecLeftBox.resize(15 * 5, false);
	m_vecTopBox.resize(30 * 5, false);
	m_vecRightBox.resize(15 * 5, false);
	m_vecBottomBox.resize(30 * 5, false);

	m_CurrState = WORM_STATE::IDLE;
	Update_Rect();


	m_pMover = new CMover;
	m_pMover->Initialize(&m_vPos);
	m_pMover->Set_Brake(0.999f);
	m_pMover->Set_MaxVelocity(20.0f);
	m_pMover->Set_Mass(10.0f);

	//인벤토리
	m_pInventory = new CInventory();
	m_pInventory->Initialize(this);

	//스테이트 (순서 중요)
	m_vecState.reserve((UINT)WORM_STATE::TYPEEND);
	m_vecState.push_back(new CState_Worm_Idle);
	m_vecState.push_back(new CState_Worm_Walk);
	m_vecState.push_back(new CState_Worm_Weapon);
	m_vecState.push_back(new CState_Worm_Jump);
	m_vecState.push_back(new CState_Worm_Flying);
	m_vecState.push_back(new CState_Worm_Slide);
	m_vecState.push_back(new CState_Worm_Dead);
	m_vecState.push_back(new CState_Worm_Winner);
	m_vecState.push_back(new CState_Worm_Swim);
	m_vecState.push_back(new CState_Worm_NotTurn);

	for (auto& iter : m_vecState)
	{
		iter->Initialize(this);
	}

	//
}

void CObj_Worm::Update(void)
{

	if(m_CurrState == WORM_STATE::FlYING)
		Set_WormAngle();

	
	
	m_vecState[(UINT)m_CurrState]->Update();

	


	Set_Bottom();
	
	m_pAnimator->Update();
}

void CObj_Worm::LateUpdate(void)
{

	m_vecState[(UINT)m_CurrState]->LateUpdate();

	Set_WormDir();

	Update_Rect();
	
	

	m_pAnimator->LateUpdate();

	

	if (m_bPutWeapon)
	{
		m_pWeapon = nullptr;
		m_bPutWeapon = false;
	}

	if (m_vPos.fY > 1165.0f && m_CurrState != WORM_STATE::SWIM)
	{
		m_CurrState = WORM_STATE::SWIM;
		m_vPos.fY += 30.0f;
		CSoundMgr::Get_Instance()->StopSound(CHANNELID::WORMSOUND);
		CSoundMgr::Get_Instance()->PlaySoundW(L"Splash.wav", CHANNELID::WORMSOUND, g_fVolume);
		CCameraMgr::Get_Inst()->Go_Target(m_vPos);
	}
		
}

void CObj_Worm::Release(void)
{
	Safe_Delete(m_pAnimator);
	Safe_Delete(m_pMover);

	for (auto& iter : m_vecState)
	{
		Safe_Delete(iter);
	}
	m_vecState.clear();

	Safe_Delete(m_pInventory);
}

void CObj_Worm::Render(HDC _hDC)
{
	m_pAnimator->Render(_hDC);

	if (m_CurrState == WORM_STATE::WEAPON)
		m_pWeapon->Render(_hDC);

	//Rectangle(_hDC, m_vBottom.fX - m_vBottom.fCX * 0.5f, m_vBottom.fY - m_vBottom.fCY * 0.5f, m_vBottom.fX + m_vBottom.fCX * 0.5f, m_vBottom.fY + m_vBottom.fCY * 0.5f);

	//테스트
	/*TCHAR	LAngle[64] = L"";

	swprintf_s(LAngle, L"LAngle : %f", m_fLeftAngle);
	TextOut(_hDC, 100, 100, LAngle, lstrlen(LAngle));

	TCHAR	RAngle[64] = L"";

	swprintf_s(RAngle, L"RAngle : %f", m_fRightAngle);
	TextOut(_hDC, 100, 140, RAngle, lstrlen(RAngle));*/
	
}

void CObj_Worm::Update_Rect(void)
{
	m_tRect.left = (LONG)(m_vPos.fX - m_vPos.fCX * 0.5f);
	m_tRect.right = (LONG)(m_vPos.fX + m_vPos.fCX * 0.5f);
	m_tRect.bottom = (LONG)(m_vPos.fY + m_vPos.fCY * 0.5f);
	m_tRect.top = (LONG)(m_vPos.fY - m_vPos.fCY * 0.5f);


}



void CObj_Worm::Get_Damage(void)
{
	if (m_iDamage > m_iWormHp)
		m_iDamage = m_iWormHp;

	m_iWormHp -= m_iDamage;

	CEffectMgr::Get_Inst()->Get_MinusHp(m_vPos, m_iDamage, m_iTeamNum);
	
	m_iDamage = 0;
	m_bDamaged = false;
}

void CObj_Worm::Set_WormAngle(void)
{
	float fX = m_pMover->Get_Velocity().fX;
	float fY = m_pMover->Get_Velocity().fY * -1;

	float fLength = m_pMover->Get_Velocity().Get_Magnitude();

	float fRadian = acosf(fY / fLength);

	if (fX < 0)
		fRadian = (2 * PI) - fRadian;
	
	m_fWormAngle = RAD2DEG(fRadian);


}

void CObj_Worm::Set_WormDir(void)
{
	if (m_pMover->Get_Velocity().fX > 0.0f)
		m_ObjDir = OBJ_DIR::RIGHT;
	else if (m_pMover->Get_Velocity().fX < 0.0f)
		m_ObjDir = OBJ_DIR::LEFT;
}

void CObj_Worm::Dead(void)
{
	m_CurrState = WORM_STATE::DEAD;
	m_bAction = true;
	CSoundMgr::Get_Instance()->Random_WormDie();
}


