#include "stdafx.h"
#include "Weapon_Hmissile.h"
#include "BmpMgr.h"
#include "Image_WeaponAim.h"
#include "KeyMgr.h"
#include "Obj_Projectile_Hmissile.h"
#include "ObjMgr.h"
#include "GameMgr.h"
#include "EffectMgr.h"
#include "SoundMgr.h"


CWeapon_Hmissile::CWeapon_Hmissile()
{
}


CWeapon_Hmissile::~CWeapon_Hmissile()
{
	Release();
}

void CWeapon_Hmissile::Update(void)
{
	if (!m_bTarget && CCameraMgr::Get_Inst()->Is_Mouse() == false)
	{
		CCameraMgr::Get_Inst()->ShowMouse();
	}

	Key_Input();

	m_pAim->Update();
}

void CWeapon_Hmissile::Initialize(CObj * _pOwner)
{
	m_WeaponType = WEAPON_TYPE::HMISSILE;
	m_WeaponState = WEAPON_STATE::IDLE;

	m_fLength = 10.0f;

	m_pOwner = _pOwner;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Gage.bmp", L"Gage");
	m_hGageDC = CBmpMgr::Get_Instance()->Find_Image(L"Gage");



	m_pAim = new CImage_WeaponAim;
	m_pAim->Initialize(m_pOwner);

	m_bTarget = false;


	return;

}

void CWeapon_Hmissile::LateUpdate(void)
{
	m_pAim->LateUpdate();
}

void CWeapon_Hmissile::Render(HDC _hDC)
{

	if (m_WeaponState == WEAPON_STATE::GAGE)
		Gage_Render(_hDC);

	m_pAim->Render(_hDC);
}

void CWeapon_Hmissile::Release(void)
{
	Safe_Delete(m_pAim);

}

void CWeapon_Hmissile::Key_Input(void)
{

	if (m_bTarget)
	{
		if (m_WeaponState == WEAPON_STATE::IDLE)
		{
			if (CKeyMgr::Get_Inst()->Key_Down(VK_SPACE))
			{
				m_WeaponState = WEAPON_STATE::GAGE;
				CSoundMgr::Get_Instance()->PlaySoundW(L"Fire.WAV", CHANNELID::WORMSPEECH, g_fVolume);
				CSoundMgr::Get_Instance()->PlaySoundW(L"ROCKETPOWERUP.WAV", CHANNELID::WEAPONSOUND, g_fVolume);
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
				CSoundMgr::Get_Instance()->StopSound(CHANNELID::WEAPONSOUND);
				CSoundMgr::Get_Instance()->PlaySoundW(L"ROCKETRELEASE.WAV", CHANNELID::WEAPONSOUND, g_fVolume);

				Shoot();

				//Å×½ºÆ® 
				m_WeaponState = WEAPON_STATE::IDLE;

				m_fShootPower = 0.0f;

				static_cast<CObj_Worm*>(m_pOwner)->Set_State(WORM_STATE::IDLE);
				static_cast<CObj_Worm*>(m_pOwner)->Put_Weapon();

			}
		}
	}
	

	if (CKeyMgr::Get_Inst()->Key_Down(VK_LBUTTON))
	{
		CSoundMgr::Get_Instance()->StopSound(CHANNELID::GAMESOUND);
		CSoundMgr::Get_Instance()->PlaySoundW(L"CursorSelect.wav", CHANNELID::GAMESOUND, g_fVolume);

		POINT* pt = CCameraMgr::Get_Inst()->Get_Mouse();

		float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
		float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();

		m_vTargetPos = { pt->x - fScrollX , pt->y - fScrollY };

		cout << m_vTargetPos.fX << endl;
		cout << m_vTargetPos.fY << endl;

		CEffectMgr::Get_Inst()->Get_Marker(m_vTargetPos);

		CCameraMgr::Get_Inst()->PutMouse();
		m_bTarget = true;
	}
}

void CWeapon_Hmissile::Shoot(void)
{
	CObj*		pNewProjectile = new CObj_Projectile_Hmissile;
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

	static_cast<CObj_Projectile_Hmissile*>(pNewProjectile)->Set_Projectile(m_pOwner, ShootPos, m_fShootPower, ShootDir);
	static_cast<CObj_Projectile_Hmissile*>(pNewProjectile)->Set_TargetPos(m_vTargetPos);

	CObjMgr::Get_Inst()->Add_Obj(pNewProjectile->Get_ObjTyep(), pNewProjectile);

	CGameMgr::Get_Inst()->Set_TurnEnd();

	CCameraMgr::Get_Inst()->Follow_Target(pNewProjectile);
}

void CWeapon_Hmissile::ResetWeapon(void)
{
	m_bTarget = false;
}
