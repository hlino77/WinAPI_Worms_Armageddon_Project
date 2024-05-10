#include "stdafx.h"
#include "Obj_Projectile_DeadBomb.h"
#include "ObjMgr.h"
#include "EffectMgr.h"
#include "Obj_Map.h"
#include "SoundMgr.h"

CObj_Projectile_DeadBomb::CObj_Projectile_DeadBomb()
{
}


CObj_Projectile_DeadBomb::~CObj_Projectile_DeadBomb()
{
}

void CObj_Projectile_DeadBomb::Initialize(void)
{
	m_ObjType = OBJ_TYPE::PROJECTILE;
	m_ProjectileState = PROJECTILE_STATE::NONE;
	m_WeaponType = WEAPON_TYPE::BAZOOKA;

	//폭발 범위
	m_vExplosion.fX = 0.0f;
	m_vExplosion.fY = 0.0f;
	m_vExplosion.fCX = 50.0f;
	m_vExplosion.fCY = 50.0f;

	//데미지
	m_iDamage = 10;

	m_bAction = true;
}

void CObj_Projectile_DeadBomb::Update(void)
{
	if (m_ProjectileState == PROJECTILE_STATE::END)
		m_bDead = true;

	if (m_ProjectileState == PROJECTILE_STATE::BOMB)
	{
		m_ProjectileState = PROJECTILE_STATE::END;
	}

	if (m_ProjectileState == PROJECTILE_STATE::NONE)
	{
		m_ProjectileState = PROJECTILE_STATE::BOMB;
		m_vExplosion.fX = m_vPos.fX;
		m_vExplosion.fY = m_vPos.fY;

		CObjMgr::Get_Inst()->Get_Flame(m_vExplosion, rand() % 3 + 2);
		CEffectMgr::Get_Inst()->Get_Circle(CIRCLE_EFFECT_TYPE::CIRCLE25, m_vExplosion);
		CEffectMgr::Get_Inst()->Get_Ellipse(ELLIPSE_EFFECT_TYPE::ELLIPSE25, m_vExplosion);

		ExplosionSmoke(SMOKE_EFFECT_TYPE::DARK20, rand() % 5 + 5);
		ExplosionSmoke(SMOKE_EFFECT_TYPE::WHITE25, rand() % 5 + 5);


		static_cast<CObj_Map*>(CObjMgr::Get_Inst()->Get_ObjList(OBJ_TYPE::MAP)->front())->Delete_Map(m_vExplosion);

		CSoundMgr::Get_Instance()->Random_BombSound();
	}
}

void CObj_Projectile_DeadBomb::LateUpdate(void)
{
}

void CObj_Projectile_DeadBomb::Release(void)
{
}

void CObj_Projectile_DeadBomb::Render(HDC _hDC)
{
}

void CObj_Projectile_DeadBomb::MapOut(void)
{
}

void CObj_Projectile_DeadBomb::Set_Projectile(CObj * _pOwner, CMyVector2 _Pos, float _fPower, CMyVector2 _Dir)
{
	m_pOwner = _pOwner;
	m_vPos = _Pos;
}

void CObj_Projectile_DeadBomb::MapCollision(void)
{
}
