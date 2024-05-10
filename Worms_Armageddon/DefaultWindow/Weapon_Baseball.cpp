#include "stdafx.h"
#include "Weapon_Baseball.h"
#include "BmpMgr.h"
#include "Image_WeaponAim.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Obj_Projectile_Baseball.h"
#include "GameMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"


CWeapon_Baseball::CWeapon_Baseball()
{
}


CWeapon_Baseball::~CWeapon_Baseball()
{
	Release();
}

void CWeapon_Baseball::Update(void)
{
	m_pAim->Update();
	Key_Input();

	if (m_WeaponState == WEAPON_STATE::SHOOT)
	{
		m_fEndDelay -= CTimeMgr::Get_Inst()->Get_DeltaTime();
		if (m_fEndDelay < 0.0f)
		{
			static_cast<CObj_Worm*>(m_pOwner)->Set_State(WORM_STATE::IDLE);
			static_cast<CObj_Worm*>(m_pOwner)->Put_Weapon();
		}
	}
}

void CWeapon_Baseball::Initialize(CObj * _pOwner)
{
	m_WeaponType = WEAPON_TYPE::BASEBALL;
	m_WeaponState = WEAPON_STATE::IDLE;

	m_fLength = 10.0f;

	m_pOwner = _pOwner;




	m_pAim = new CImage_WeaponAim;
	m_pAim->Initialize(m_pOwner);


	m_fEndDelay = 2.0f;

	return;
}

void CWeapon_Baseball::LateUpdate(void)
{
	m_pAim->LateUpdate();


	
}

void CWeapon_Baseball::Render(HDC _hDC)
{

	m_pAim->Render(_hDC);
}

void CWeapon_Baseball::Release(void)
{
	Safe_Delete(m_pAim);
}

void CWeapon_Baseball::Key_Input(void)
{
	if (m_WeaponState == WEAPON_STATE::IDLE)
	{
		if (CKeyMgr::Get_Inst()->Key_Down(VK_SPACE))
		{
			CSoundMgr::Get_Instance()->StopSound(CHANNELID::WEAPONSOUND);
			CSoundMgr::Get_Instance()->PlaySoundW(L"BaseBallBatRelease.wav", CHANNELID::WEAPONSOUND, g_fVolume);

			Shoot();

			m_WeaponState = WEAPON_STATE::SHOOT;

			m_fShootPower = 0.0f;

			static_cast<CAnimator_Worm*>(static_cast<CObj_Worm*>(m_pOwner)->Get_Animator())->Reset_WeaponIdle();
			
		}
	}
}

void CWeapon_Baseball::Shoot(void)
{
	CObj*		pNewProjectile = new CObj_Projectile_Baseball;
	pNewProjectile->Initialize();

	float fX = sinf(DEG2RAD(m_fAngle));
	float fY = cosf(DEG2RAD(m_fAngle));

	if (m_pOwner->Get_ObjDir() == OBJ_DIR::LEFT)
		fX *= -1;

	float fPosX = m_fLength * fX;
	float fPosY = m_fLength * fY;

	m_fShootPower = 20000.0f;

	CMyVector2	ShootDir = { fX, fY };
	CMyVector2  ShootPos = { m_pOwner->Get_Pos().fX + fPosX, m_pOwner->Get_Pos().fY + fPosY };
	//ShootDir.Normalize();

	static_cast<CObj_Projectile_Baseball*>(pNewProjectile)->Set_Projectile(m_pOwner, ShootPos, m_fShootPower, ShootDir);
	static_cast<CObj_Projectile_Baseball*>(pNewProjectile)->Set_Owner(m_pOwner);


	CObjMgr::Get_Inst()->Add_Obj(pNewProjectile->Get_ObjTyep(), pNewProjectile);

	CGameMgr::Get_Inst()->Set_TurnEnd();

	CCameraMgr::Get_Inst()->Follow_Target(pNewProjectile);


}

void CWeapon_Baseball::ResetWeapon(void)
{
	m_WeaponState = WEAPON_STATE::IDLE;
	m_fEndDelay = 2.0f;
}
