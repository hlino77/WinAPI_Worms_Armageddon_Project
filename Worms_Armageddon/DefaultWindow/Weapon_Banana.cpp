#include "stdafx.h"
#include "Weapon_Banana.h"
#include "BmpMgr.h"
#include "Image_WeaponAim.h"
#include "KeyMgr.h"
#include "Obj_Projectile_Banana.h"
#include "ObjMgr.h"
#include "GameMgr.h"
#include "SoundMgr.h"

CWeapon_Banana::CWeapon_Banana()
{
}


CWeapon_Banana::~CWeapon_Banana()
{
	Release();
}

void CWeapon_Banana::Update(void)
{
	m_pAim->Update();

	Key_Input();
}

void CWeapon_Banana::Initialize(CObj * _pOwner)
{
	m_WeaponType = WEAPON_TYPE::BANANA;
	m_WeaponState = WEAPON_STATE::IDLE;

	m_fLength = 10.0f;

	m_pOwner = _pOwner;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Gage.bmp", L"Gage");
	m_hGageDC = CBmpMgr::Get_Instance()->Find_Image(L"Gage");



	m_pAim = new CImage_WeaponAim;
	m_pAim->Initialize(m_pOwner);


	return;
}

void CWeapon_Banana::LateUpdate(void)
{
	m_pAim->LateUpdate();
}

void CWeapon_Banana::Render(HDC _hDC)
{

	if (m_WeaponState == WEAPON_STATE::GAGE)
		Gage_Render(_hDC);

	m_pAim->Render(_hDC);
}

void CWeapon_Banana::Release(void)
{
	Safe_Delete(m_pAim);
}

void CWeapon_Banana::Key_Input(void)
{
	if (m_WeaponState == WEAPON_STATE::IDLE)
	{
		if (CKeyMgr::Get_Inst()->Key_Down(VK_SPACE))
		{
			m_WeaponState = WEAPON_STATE::GAGE;

			CSoundMgr::Get_Instance()->StopSound(CHANNELID::WORMSPEECH);
			CSoundMgr::Get_Instance()->StopSound(CHANNELID::WEAPONSOUND);
			CSoundMgr::Get_Instance()->PlaySoundW(L"WATCHTHIS.WAV", CHANNELID::WORMSPEECH, g_fVolume);
			CSoundMgr::Get_Instance()->PlaySoundW(L"THROWPOWERUP.WAV", CHANNELID::WEAPONSOUND, g_fVolume);
		}
	}

	if (m_WeaponState == WEAPON_STATE::GAGE)
	{
		if (CKeyMgr::Get_Inst()->Key_Pressing(VK_SPACE))
		{
			m_fShootPower += 2.0f;
			if (m_fShootPower > 160.0f)
				m_fShootPower = 160.0f;
		}
		else
		{
			Shoot();
			CSoundMgr::Get_Instance()->StopSound(CHANNELID::WEAPONSOUND);
			CSoundMgr::Get_Instance()->PlaySoundW(L"THROWRELEASE.WAV", CHANNELID::WEAPONSOUND, g_fVolume);

			//�׽�Ʈ 
			m_WeaponState = WEAPON_STATE::IDLE;

			m_fShootPower = 0.0f;

			static_cast<CObj_Worm*>(m_pOwner)->Set_State(WORM_STATE::IDLE);
			static_cast<CObj_Worm*>(m_pOwner)->Put_Weapon();

		}
	}
}

void CWeapon_Banana::Shoot(void)
{
	CObj*		pNewProjectile = new CObj_Projectile_Banana;
	pNewProjectile->Initialize();

	float fX = sinf(DEG2RAD(m_fAngle));
	float fY = cosf(DEG2RAD(m_fAngle));

	if (m_pOwner->Get_ObjDir() == OBJ_DIR::LEFT)
		fX *= -1;

	float fPosX = m_fLength * fX;
	float fPosY = m_fLength * fY;



	CMyVector2	ShootDir = { fX, fY };
	CMyVector2  ShootPos = { m_pOwner->Get_Pos().fX + fPosX, m_pOwner->Get_Pos().fY + fPosY };
	//ShootDir.Normalize();

	static_cast<CObj_Projectile_Banana*>(pNewProjectile)->Set_Projectile(m_pOwner, ShootPos, m_fShootPower, ShootDir);

	CObjMgr::Get_Inst()->Add_Obj(pNewProjectile->Get_ObjTyep(), pNewProjectile);

	CGameMgr::Get_Inst()->Set_TurnEnd();

	CCameraMgr::Get_Inst()->Follow_Target(pNewProjectile);
}

void CWeapon_Banana::ResetWeapon(void)
{
}
