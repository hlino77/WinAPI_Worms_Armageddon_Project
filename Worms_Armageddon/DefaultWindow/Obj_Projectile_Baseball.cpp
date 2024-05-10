#include "stdafx.h"
#include "Obj_Projectile_Baseball.h"


CObj_Projectile_Baseball::CObj_Projectile_Baseball()
{
}


CObj_Projectile_Baseball::~CObj_Projectile_Baseball()
{
	Release();
}

void CObj_Projectile_Baseball::Initialize(void)
{
	m_ObjType = OBJ_TYPE::PROJECTILE;
	m_ProjectileState = PROJECTILE_STATE::NONE;
	m_WeaponType = WEAPON_TYPE::BASEBALL;

	m_vPos.fX = 0.0f;
	m_vPos.fY = 0.0f;
	m_vPos.fCX = 60.0f;
	m_vPos.fCY = 60.0f;

	//충돌범위
	m_vCollision.fX = 0.0f;
	m_vCollision.fY = 0.0f;
	m_vCollision.fCX = 15.0f;
	m_vCollision.fCY = 15.0f;

	//폭발 범위
	m_vExplosion.fX = 0.0f;
	m_vExplosion.fY = 0.0f;
	m_vExplosion.fCX = 15.0f;
	m_vExplosion.fCY = 15.0f;

	//바운딩 박스
	m_vecBoundingBox.resize((UINT)(10 * 15), false);

	Update_Rect();

	m_pMover = nullptr;





	//데미지
	m_iDamage = 10;

	m_bAction = true;
}

void CObj_Projectile_Baseball::Update(void)
{
	if (m_ProjectileState == PROJECTILE_STATE::BOMB)
	{
		m_ProjectileState = PROJECTILE_STATE::END;
		m_bDead = true;
	}
		


	m_ProjectileState = PROJECTILE_STATE::BOMB;
}

void CObj_Projectile_Baseball::LateUpdate(void)
{
	
}

void CObj_Projectile_Baseball::Release(void)
{
}

void CObj_Projectile_Baseball::Render(HDC _hDC)
{
}

void CObj_Projectile_Baseball::MapOut(void)
{
}

void CObj_Projectile_Baseball::Set_Projectile(CObj * _pOwner, CMyVector2 _Pos, float _fPower, CMyVector2 _Dir)
{
	m_pOwner = _pOwner;
	m_vPos = _Pos;
	m_fShootPower = _fPower;
	m_vDir = _Dir;
	m_vExplosion.fX = m_vPos.fX;
	m_vExplosion.fY = m_vPos.fY;
}

void CObj_Projectile_Baseball::MapCollision(void)
{
}
