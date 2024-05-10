#include "stdafx.h"
#include "Weapon_Donkey.h"
#include "KeyMgr.h"
#include "Obj_Projectile_Donkey.h"
#include "ObjMgr.h"
#include "GameMgr.h"
#include "Obj_Worm.h"
#include "EffectMgr.h"
#include "SoundMgr.h"


CWeapon_Donkey::CWeapon_Donkey()
{
}


CWeapon_Donkey::~CWeapon_Donkey()
{
	Release();
}

void CWeapon_Donkey::Update(void)
{
	if (CCameraMgr::Get_Inst()->Is_Mouse() == false && m_WeaponState == WEAPON_STATE::IDLE)
	{
		CCameraMgr::Get_Inst()->ShowMouse();
	}

	Key_Input();
}

void CWeapon_Donkey::Initialize(CObj * _pOwner)
{
	m_WeaponType = WEAPON_TYPE::DONKEY;
	m_WeaponState = WEAPON_STATE::IDLE;

	m_fLength = 10.0f;

	m_pOwner = _pOwner;




	m_pAim = nullptr;


	return;
}

void CWeapon_Donkey::LateUpdate(void)
{
}

void CWeapon_Donkey::Render(HDC _hDC)
{
}

void CWeapon_Donkey::Release(void)
{
}

void CWeapon_Donkey::Key_Input(void)
{
	if (CKeyMgr::Get_Inst()->Key_Down(VK_LBUTTON))
	{
		CSoundMgr::Get_Instance()->StopSound(CHANNELID::GAMESOUND);
		CSoundMgr::Get_Instance()->PlaySoundW(L"CursorSelect.wav", CHANNELID::GAMESOUND, g_fVolume);

		CSoundMgr::Get_Instance()->StopSound(CHANNELID::WORMSPEECH);
		CSoundMgr::Get_Instance()->PlaySoundW(L"ORDERS.WAV", CHANNELID::WORMSPEECH, g_fVolume);

		Shoot();
		

		//Å×½ºÆ® 
		m_WeaponState = WEAPON_STATE::SHOOTEND;

		m_fShootPower = 0.0f;

		static_cast<CObj_Worm*>(m_pOwner)->Set_State(WORM_STATE::IDLE);
		static_cast<CObj_Worm*>(m_pOwner)->Put_Weapon();

		if (CCameraMgr::Get_Inst()->Is_Mouse() == true)
		{
			CCameraMgr::Get_Inst()->PutMouse();
		}
	}
}

void CWeapon_Donkey::Shoot(void)
{
	CObj*		pNewProjectile = new CObj_Projectile_Donkey;
	pNewProjectile->Initialize();

	float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
	float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();

	
	POINT* pt = CCameraMgr::Get_Inst()->Get_Mouse();
	

	CMyVector2  ShootPos = { pt->x - fScrollX , pt->y - fScrollY };

	CEffectMgr::Get_Inst()->Get_Marker(ShootPos);
	//ShootDir.Normalize();

	static_cast<CObj_Projectile_Donkey*>(pNewProjectile)->Set_Projectile(m_pOwner, ShootPos, 0.0f , ShootPos);

	CObjMgr::Get_Inst()->Add_Obj(pNewProjectile->Get_ObjTyep(), pNewProjectile);

	CGameMgr::Get_Inst()->Set_TurnEnd();

	CCameraMgr::Get_Inst()->Follow_Target(pNewProjectile);

	CSoundMgr::Get_Instance()->StopSound(CHANNELID::WEAPONSOUND);
	CSoundMgr::Get_Instance()->PlaySoundW(L"HOLYDONKEY.WAV", CHANNELID::WEAPONSOUND, g_fVolume);
}

void CWeapon_Donkey::ResetWeapon(void)
{
}
