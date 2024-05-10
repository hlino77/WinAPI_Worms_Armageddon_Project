#include "stdafx.h"
#include "Obj_Projectile_Donkey.h"
#include "Image_Donkey.h"
#include "Template.h"
#include "ObjMgr.h"
#include "EffectMgr.h"
#include "Obj_Map.h"
#include "SoundMgr.h"

CObj_Projectile_Donkey::CObj_Projectile_Donkey()
{
}


CObj_Projectile_Donkey::~CObj_Projectile_Donkey()
{
	Release();
}

void CObj_Projectile_Donkey::Initialize(void)
{
	m_ObjType = OBJ_TYPE::PROJECTILE;
	m_ProjectileState = PROJECTILE_STATE::NONE;
	m_WeaponType = WEAPON_TYPE::DONKEY;

	m_vPos.fX = 0.0f;
	m_vPos.fY = 0.0f;
	m_vPos.fCX = 158.0f;
	m_vPos.fCY = 147.0f;

	//충돌범위
	m_vCollision.fX = 0.0f;
	m_vCollision.fY = 0.0f;
	m_vCollision.fCX = 100.0f;
	m_vCollision.fCY = 2.0f;

	//폭발 범위
	m_vExplosion.fX = 0.0f;
	m_vExplosion.fY = 0.0f;
	m_vExplosion.fCX = 200.0f;
	m_vExplosion.fCY = 200.0f;

	//바운딩 박스
	m_vecBoundingBox.resize((UINT)(100 * 2), false);

	Update_Rect();

	m_pMover = new CMover;
	m_pMover->Initialize(&m_vPos);
	m_pMover->Set_Brake(1.0f);
	m_pMover->Set_MaxVelocity(30.0f);
	m_pMover->Set_Mass(10.0f);


	m_pImage = new CImage_Donkey;
	m_pImage->Initialize(this);

	//데미지
	m_iDamage = 40;

	m_bAction = true;
}

void CObj_Projectile_Donkey::Update(void)
{
	if (m_ProjectileState == PROJECTILE_STATE::NONE)
	{
		m_pMover->Update();
		m_pImage->Update();
	}
}

void CObj_Projectile_Donkey::LateUpdate(void)
{
	MapOut();

	if (m_ProjectileState == PROJECTILE_STATE::BOMB)
	{
		m_ProjectileState = PROJECTILE_STATE::NONE;
	}

	if (m_ProjectileState == PROJECTILE_STATE::NONE)
	{
		m_pMover->LateUpdate();

		if (m_bMapCollision)
			MapCollision();


		m_pImage->LateUpdate();

		Update_Rect();
	}

	
}

void CObj_Projectile_Donkey::Release(void)
{
	Safe_Delete(m_pMover);
	Safe_Delete(m_pImage);
}

void CObj_Projectile_Donkey::Render(HDC _hDC)
{
	m_pImage->Render(_hDC);
}

void CObj_Projectile_Donkey::MapOut(void)
{
	if (m_vPos.fY > 1160)
	{
		m_bDead = true;
	}
}

void CObj_Projectile_Donkey::Set_Projectile(CObj * _pOwner, CMyVector2 _Pos, float _fPower, CMyVector2 _Dir)
{
	m_pOwner = _pOwner;
	m_vPos.fX = _Pos.fX;
	m_vPos.fY = 0.0f;
}

void CObj_Projectile_Donkey::MapCollision(void)
{

	if (m_pMover->Get_Velocity().fY > 0)
	{
		m_ProjectileState = PROJECTILE_STATE::BOMB;

		m_vExplosion.fX = m_vPos.fX;
		m_vExplosion.fY = m_vPos.fY;

		CObjMgr::Get_Inst()->Get_Flame(m_vExplosion, rand() % 3 + 7);
		CEffectMgr::Get_Inst()->Get_Circle(CIRCLE_EFFECT_TYPE::CIRCLE100, m_vExplosion);
		CEffectMgr::Get_Inst()->Get_Ellipse(ELLIPSE_EFFECT_TYPE::ELLIPSE100, m_vExplosion);

		ExplosionSmoke(SMOKE_EFFECT_TYPE::DARK40, rand() % 5 + 10);
		ExplosionSmoke(SMOKE_EFFECT_TYPE::WHITE100, rand() % 5 + 10);

		CEffectMgr::Get_Inst()->Get_Random_Text(m_vExplosion);

		static_cast<CObj_Map*>(CObjMgr::Get_Inst()->Get_ObjList(OBJ_TYPE::MAP)->front())->Delete_Map(m_vExplosion);

		m_pMover->StopY();
		m_pMover->AddForce(CMyVector2(0.0f, -4000.0f));

		m_bMapCollision = false;
		fill(m_vecBoundingBox.begin(), m_vecBoundingBox.end(), false);

		CEffectMgr::Get_Inst()->Delete_Marker();

		CSoundMgr::Get_Instance()->StopSound(CHANNELID::WEAPONSOUND);
		CSoundMgr::Get_Instance()->PlaySoundW(L"HOLYDONKEYIMPACT.WAV", CHANNELID::WEAPONSOUND, g_fVolume);


		CSoundMgr::Get_Instance()->Random_BombSound();
	}
	
}
