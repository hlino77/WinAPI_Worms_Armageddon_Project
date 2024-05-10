#include "stdafx.h"
#include "Obj_Projectile_ChildBanana.h"
#include "Image_Banana.h"
#include "Template.h"
#include "TimeMgr.h"
#include "EffectMgr.h"
#include "ObjMgr.h"
#include "Obj_Map.h"
#include "SoundMgr.h"


CObj_Projectile_ChildBanana::CObj_Projectile_ChildBanana()
{
}


CObj_Projectile_ChildBanana::~CObj_Projectile_ChildBanana()
{
	Release();
}

void CObj_Projectile_ChildBanana::Initialize(void)
{
	m_ObjType = OBJ_TYPE::PROJECTILE;
	m_ProjectileState = PROJECTILE_STATE::NONE;
	m_WeaponType = WEAPON_TYPE::BANANA;

	m_vPos.fX = 0.0f;
	m_vPos.fY = 0.0f;
	m_vPos.fCX = 60.0f;
	m_vPos.fCY = 60.0f;

	//충돌범위
	m_vCollision.fX = 0.0f;
	m_vCollision.fY = 0.0f;
	m_vCollision.fCX = 25.0f;
	m_vCollision.fCY = 25.0f;

	//폭발 범위
	m_vExplosion.fX = 0.0f;
	m_vExplosion.fY = 0.0f;
	m_vExplosion.fCX = 100.0f;
	m_vExplosion.fCY = 100.0f;

	//바운딩 박스
	m_vecBoundingBox.resize((UINT)(25 * 25), false);

	Update_Rect();

	m_pMover = new CMover;
	m_pMover->Initialize(&m_vPos);
	m_pMover->Set_Brake(1.0f);
	m_pMover->Set_MaxVelocity(30.0f);
	m_pMover->Set_Mass(15.0f);


	m_pImage = new CImage_Banana;
	m_pImage->Initialize(this);

	m_fAngle = 90.0f;

	//데미지
	m_iDamage = 30;

	Set_Wind();

	m_bAction = true;
}

void CObj_Projectile_ChildBanana::Update(void)
{
	if (m_ProjectileState == PROJECTILE_STATE::NONE)
	{
		m_pMover->Update();
		m_pImage->Update();
	}
}

void CObj_Projectile_ChildBanana::LateUpdate(void)
{
	MapOut();

	if (m_ProjectileState == PROJECTILE_STATE::END)
		m_bDead = true;

	if (m_ProjectileState == PROJECTILE_STATE::BOMB)
	{
		m_ProjectileState = PROJECTILE_STATE::END;
	}



	if (m_ProjectileState == PROJECTILE_STATE::NONE)
	{
		m_pMover->LateUpdate();

		if (m_bMapCollision)
			MapCollision();

		Angle_Update();

		m_pImage->LateUpdate();

		Update_Rect();

	}
}

void CObj_Projectile_ChildBanana::Release(void)
{
	Safe_Delete(m_pMover);
	Safe_Delete(m_pImage);
}

void CObj_Projectile_ChildBanana::Render(HDC _hDC)
{
	if (m_ProjectileState == PROJECTILE_STATE::NONE)
	{
		m_pImage->Render(_hDC);
	}
}

void CObj_Projectile_ChildBanana::MapOut(void)
{
	if (m_vPos.fY > 1160)
	{
		m_bDead = true;
		CSoundMgr::Get_Instance()->StopSound(CHANNELID::PROJECTILE);
		CSoundMgr::Get_Instance()->PlaySoundW(L"Splash.wav", CHANNELID::PROJECTILE, g_fVolume);
	}
}

void CObj_Projectile_ChildBanana::Set_Projectile(CObj * _pOwner, CMyVector2 _Pos, float _fPower, CMyVector2 _Dir)
{
	m_pOwner = _pOwner;
	m_vPos.fX = _Pos.fX;
	m_vPos.fY = _Pos.fY;
	m_fPower = _fPower * 60.0f;
	CMyVector2 ShootDir;
	ShootDir.fX = _Dir.fX * (rand() % 1000);
	ShootDir.fY = _Dir.fY * m_fPower;

	m_pMover->AddForce(ShootDir);
}

void CObj_Projectile_ChildBanana::MapCollision(void)
{
	Bomb();
}

void CObj_Projectile_ChildBanana::Angle_Update(void)
{
	if (m_pMover->Get_Velocity().fX < 0.0f)
	{
		m_fAngle -= 10.0f;
		if (m_fAngle < 0.0f)
			m_fAngle = 360.0f;
	}
	else if (m_pMover->Get_Velocity().fX > 0.0f)
	{
		m_fAngle += 10.0f;

		if (m_fAngle > 360.0f)
			m_fAngle = 0.0f;
	}
	else if (m_pMover->Get_Velocity().fX == 0.0f)
	{
		m_fAngle += 5.0f;
		if (m_fAngle > 360.0f)
			m_fAngle = 0.0f;
	}
}

void CObj_Projectile_ChildBanana::Bomb(void)
{
	m_ProjectileState = PROJECTILE_STATE::BOMB;
	m_vExplosion.fX = m_vPos.fX;
	m_vExplosion.fY = m_vPos.fY;

	CObjMgr::Get_Inst()->Get_Flame(m_vExplosion, rand() % 3 + 5);
	CEffectMgr::Get_Inst()->Get_Circle(CIRCLE_EFFECT_TYPE::CIRCLE50, m_vExplosion);
	CEffectMgr::Get_Inst()->Get_Ellipse(ELLIPSE_EFFECT_TYPE::ELLIPSE50, m_vExplosion);

	ExplosionSmoke(SMOKE_EFFECT_TYPE::DARK30, rand() % 5 + 10);
	ExplosionSmoke(SMOKE_EFFECT_TYPE::WHITE50, rand() % 5 + 10);

	CEffectMgr::Get_Inst()->Get_Random_Text(m_vExplosion);

	static_cast<CObj_Map*>(CObjMgr::Get_Inst()->Get_ObjList(OBJ_TYPE::MAP)->front())->Delete_Map(m_vExplosion);

	CSoundMgr::Get_Instance()->Random_BombSound();


}
