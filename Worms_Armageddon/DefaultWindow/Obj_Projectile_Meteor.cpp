#include "stdafx.h"
#include "Obj_Projectile_Meteor.h"
#include "EffectMgr.h"
#include "Sprite_Meteor.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "Obj_Map.h"
#include "GameMgr.h"


CObj_Projectile_Meteor::CObj_Projectile_Meteor()
	:m_bShooted(false)
{
}


CObj_Projectile_Meteor::~CObj_Projectile_Meteor()
{
	Release();
}

void CObj_Projectile_Meteor::Initialize(void)
{
	m_ObjType = OBJ_TYPE::PROJECTILE;
	m_ProjectileState = PROJECTILE_STATE::NONE;
	m_WeaponType = WEAPON_TYPE::BAZOOKA;

	m_vPos.fX = 0.0f;
	m_vPos.fY = 0.0f;
	m_vPos.fCX = 60.0f;
	m_vPos.fCY = 60.0f;

	//충돌범위
	m_vCollision.fX = 0.0f;
	m_vCollision.fY = 0.0f;
	m_vCollision.fCX = 10.0f;
	m_vCollision.fCY = 15.0f;

	//폭발 범위
	m_vExplosion.fX = 0.0f;
	m_vExplosion.fY = 0.0f;
	m_vExplosion.fCX = 100.0f;
	m_vExplosion.fCY = 100.0f;

	//바운딩 박스
	m_vecBoundingBox.resize((UINT)(10 * 15), false);

	Update_Rect();

	m_pMover = new CMover;
	m_pMover->Initialize(&m_vPos);
	m_pMover->Set_Brake(1.0f);
	m_pMover->Set_MaxVelocity(20.0f);
	m_pMover->Set_Mass(10.0f);
	m_pMover->Set_Gravity(0.0f);

	m_pSprite = new CSprite_Meteor;
	m_pSprite->Initialize(this);

	m_ExhaustTime = GetTickCount() + 30;
	m_ExhaustDelay = 30;

	//데미지
	m_iDamage = 20;

	Set_Wind();

	m_bAction = true;
}

void CObj_Projectile_Meteor::Update(void)
{
	if (!m_bShooted)
	{
		if (m_iStartTime + m_iDelay < GetTickCount())
		{
			Shoot();
			m_bShooted = true;
		}
	}

	if (m_bShooted && m_ProjectileState == PROJECTILE_STATE::NONE)
	{
		m_pMover->Update();
		m_pSprite->Update();
		Exhaust();
	}
}

void CObj_Projectile_Meteor::LateUpdate(void)
{
	MapOut();

	if (m_bShooted && m_ProjectileState == PROJECTILE_STATE::END)
		m_bDead = true;

	if (m_bShooted && m_ProjectileState == PROJECTILE_STATE::BOMB)
	{
		m_ProjectileState = PROJECTILE_STATE::END;
	}



	if (m_bShooted && m_ProjectileState == PROJECTILE_STATE::NONE)
	{
		m_pMover->LateUpdate();

		if (m_bMapCollision)
			MapCollision();

		m_pSprite->LateUpdate();

		Update_Rect();
	}
}

void CObj_Projectile_Meteor::Release(void)
{
	Safe_Delete(m_pMover);
	Safe_Delete(m_pSprite);
}

void CObj_Projectile_Meteor::Render(HDC _hDC)
{
	if (m_ProjectileState == PROJECTILE_STATE::NONE)
	{
		m_pSprite->Render(_hDC);
	}
}

void CObj_Projectile_Meteor::MapOut(void)
{
	if (m_vPos.fY > 1160)
	{
		m_bDead = true;
		CSoundMgr::Get_Instance()->StopSound(CHANNELID::PROJECTILE);
		CSoundMgr::Get_Instance()->PlaySoundW(L"Splash.wav", CHANNELID::PROJECTILE, g_fVolume);
	}
}

void CObj_Projectile_Meteor::Set_Projectile(CObj * _pOwner, CMyVector2 _Pos, float _fPower, CMyVector2 _Dir)
{
}

void CObj_Projectile_Meteor::MapCollision(void)
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

	if (m_iNum == 20)
		CGameMgr::Get_Inst()->Set_TurnEnd();

	CCameraMgr::Get_Inst()->Camera_Shake();
}

void CObj_Projectile_Meteor::Set_Meteor(int _iNum)
{
	m_iNum = _iNum;
	m_vPos.fX = rand() % 2000 + 1000;
	m_vPos.fY = -25.0f;

	m_vTargetPos.fX = rand() % 1200 + 1350;
	m_vTargetPos.fY = rand() % 200 + 980;

	m_iDelay = rand() % 500 + (500 * _iNum);
	m_iStartTime = GetTickCount();
}

void CObj_Projectile_Meteor::Exhaust(void)
{
	if (m_ExhaustTime + m_ExhaustDelay < GetTickCount())
	{
		float fX = m_vPos.fX;
		float fY = m_vPos.fY + 10.0f;


		CEffectMgr::Get_Inst()->Get_Exhaust(EXHAUST_EFFECT_TYPE::WHITE, CMyVector2(fX, fY));

		m_ExhaustTime = GetTickCount();
	}
}

void CObj_Projectile_Meteor::Shoot(void)
{
	float fX = m_vTargetPos.fX - m_vPos.fX;
	float fY = m_vTargetPos.fY - m_vPos.fY;

	m_pMover->AddForce(CMyVector2(fX * 1000.0f, fY * 1000.0f));

	CSoundMgr::Get_Instance()->StopSound(CHANNELID::WEAPONSOUND);
	CSoundMgr::Get_Instance()->PlaySoundW(L"Armageddon.wav", CHANNELID::WORMSOUND, g_fVolume);
}
