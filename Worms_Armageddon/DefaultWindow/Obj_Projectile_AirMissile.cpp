#include "stdafx.h"
#include "Obj_Projectile_AirMissile.h"
#include "Image_AirMissile.h"
#include "Template.h"
#include "ObjMgr.h"
#include "EffectMgr.h"
#include "Obj_Map.h"
#include "SoundMgr.h"

Obj_Projectile_AirMissile::Obj_Projectile_AirMissile()
{
}


Obj_Projectile_AirMissile::~Obj_Projectile_AirMissile()
{
	Release();
}

void Obj_Projectile_AirMissile::Initialize(void)
{
	m_ObjType = OBJ_TYPE::PROJECTILE;
	m_ProjectileState = PROJECTILE_STATE::NONE;
	m_WeaponType = WEAPON_TYPE::AIRMISSILE;

	m_vPos.fX = 0.0f;
	m_vPos.fY = 0.0f;
	m_vPos.fCX = 60.0f;
	m_vPos.fCY = 60.0f;

	//충돌범위
	m_vCollision.fX = 0.0f;
	m_vCollision.fY = 0.0f;
	m_vCollision.fCX = 5.0f;
	m_vCollision.fCY = 5.0f;

	//폭발 범위
	m_vExplosion.fX = 0.0f;
	m_vExplosion.fY = 0.0f;
	m_vExplosion.fCX = 50.0f;
	m_vExplosion.fCY = 50.0f;

	//바운딩 박스
	m_vecBoundingBox.resize((UINT)(5 * 5), false);

	Update_Rect();

	m_pMover = new CMover;
	m_pMover->Initialize(&m_vPos);
	m_pMover->Set_Brake(1.0f);
	m_pMover->Set_MaxVelocity(30.0f);
	m_pMover->Set_Mass(10.0f);
	m_pMover->Set_Gravity(0.0f);


	m_pImage = new CImage_AirMissile;
	m_pImage->Initialize(this);

	m_ExhaustTime = GetTickCount() + 30;
	m_ExhaustDelay = 30;

	//데미지
	m_iDamage = 20;

	Set_Wind();

	m_bAction = true;

	m_fAngle = 90.0f;


	m_fTargetLength = 0.0f;

	m_fSpeed = 1.0f;
}

void Obj_Projectile_AirMissile::Update(void)
{
	Set_TargetAngle();
	if (m_fAngle != m_fTargetAngle)
	{
		if (fabs(m_fTargetAngle - m_fAngle) < 2.0f)
			m_fAngle = m_fTargetAngle;
		else
		{
			m_fAngle += 4.0f;
			if (m_fAngle > 360.0f)
				m_fAngle -= 360.0f;
		}
	}
	MissileMove();
	m_pMover->Update();
	m_pImage->Update();
	Exhaust();
}

void Obj_Projectile_AirMissile::LateUpdate(void)
{
	MapOut();


	switch (m_ProjectileState)
	{
	case PROJECTILE_STATE::END:
		m_bDead = true;
		break;
	case PROJECTILE_STATE::BOMB:
		m_ProjectileState = PROJECTILE_STATE::END;
		break;
	case PROJECTILE_STATE::NONE:
		m_pMover->LateUpdate();

		if (m_bMapCollision)
			MapCollision();

		m_pImage->LateUpdate();

		Update_Rect();
		break;
	}
}

void Obj_Projectile_AirMissile::Release(void)
{
	Safe_Delete(m_pMover);
	Safe_Delete(m_pImage);
}

void Obj_Projectile_AirMissile::Render(HDC _hDC)
{
	if (m_ProjectileState == PROJECTILE_STATE::NONE)
	{
		m_pImage->Render(_hDC);
	}
}

void Obj_Projectile_AirMissile::MapOut(void)
{
	if (m_vPos.fY > 1160)
	{
		m_bDead = true;
	}

}

void Obj_Projectile_AirMissile::Set_Projectile(CObj * _pOwner, CMyVector2 _Pos, float _fPower, CMyVector2 _Dir)
{
	m_pOwner = _pOwner;
	m_vPos.fX = _Pos.fX;
	m_vPos.fY = _Pos.fY;
	m_fPower = _fPower * 50.0f;



	m_pMover->AddForce(_Dir * m_fPower);
}

void Obj_Projectile_AirMissile::MapCollision(void)
{
	m_ProjectileState = PROJECTILE_STATE::BOMB;
	m_vExplosion.fX = m_vPos.fX;
	m_vExplosion.fY = m_vPos.fY;

	CObjMgr::Get_Inst()->Get_Flame(m_vExplosion, rand() % 3 + 3);
	CEffectMgr::Get_Inst()->Get_Circle(CIRCLE_EFFECT_TYPE::CIRCLE25, m_vExplosion);
	CEffectMgr::Get_Inst()->Get_Ellipse(ELLIPSE_EFFECT_TYPE::ELLIPSE25, m_vExplosion);

	ExplosionSmoke(SMOKE_EFFECT_TYPE::DARK20, rand() % 5 + 10);
	ExplosionSmoke(SMOKE_EFFECT_TYPE::WHITE25, rand() % 5 + 10);

	CEffectMgr::Get_Inst()->Get_Random_Text(m_vExplosion);

	static_cast<CObj_Map*>(CObjMgr::Get_Inst()->Get_ObjList(OBJ_TYPE::MAP)->front())->Delete_Map(m_vExplosion);

	CEffectMgr::Get_Inst()->Delete_Marker();

	CSoundMgr::Get_Instance()->Random_BombSound();
}

void Obj_Projectile_AirMissile::Exhaust(void)
{
	if (m_ExhaustTime + m_ExhaustDelay < GetTickCount())
	{
		float fAngle = m_fAngle + 180.0f;
		if (fAngle > 360.0f)
			fAngle -= 360.0f;

		float fLength = 25.0f;
		float fRadian = DEG2RAD(fAngle);

		float fX = m_vPos.fX + (fLength * sinf(fRadian));
		float fY = m_vPos.fY + (fLength * cosf(fRadian) * -1);

		float FirstfX = fX + ((rand() % 3 - 1) * 2.0f);
		float FirstfY = fY + (rand() % 3 - 1) * 2.0f;
		float SecondfX = fX + (rand() % 3 - 1) * 2.0f;
		float SecondfY = fY + (rand() % 3 - 1) * 2.0f;

		CEffectMgr::Get_Inst()->Get_Exhaust(EXHAUST_EFFECT_TYPE::WHITE, CMyVector2(FirstfX, FirstfY));
		CEffectMgr::Get_Inst()->Get_Exhaust(EXHAUST_EFFECT_TYPE::WHITE, CMyVector2(SecondfX, SecondfY));

		m_ExhaustTime = GetTickCount();
	}
}

void Obj_Projectile_AirMissile::MissileMove(void)
{
	float fRadian = DEG2RAD(m_fAngle);

	float fX = sinf(fRadian);
	float fY = cosf(fRadian) * -1.0f;

	m_fSpeed += 0.4f;

	if (m_fSpeed > 20.0f)
		m_fSpeed = 20.0f;

	m_vPos.fX += fX * m_fSpeed;
	m_vPos.fY += fY * m_fSpeed;
}

void Obj_Projectile_AirMissile::Set_TargetAngle(void)
{
	float fWidth = m_vPos.fX - m_vTargetPos.fX;
	float fHeight = m_vPos.fY - m_vTargetPos.fY;

	m_fTargetLength = sqrt((fWidth * fWidth) + (fHeight * fHeight));

	float fRadian = acosf(fHeight / m_fTargetLength);

	if (m_vPos.fX > m_vTargetPos.fX)
		fRadian = (2 * PI) - fRadian;

	m_fTargetAngle = RAD2DEG(fRadian);
}
