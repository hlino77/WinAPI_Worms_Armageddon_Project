#include "stdafx.h"
#include "Obj_Projectile_Banana.h"
#include "Image_Banana.h"
#include "Template.h"
#include "TimeMgr.h"
#include "EffectMgr.h"
#include "ObjMgr.h"
#include "Obj_Map.h"
#include "Obj_Projectile_ChildBanana.h"
#include "GameMgr.h"
#include "SoundMgr.h"


CObj_Projectile_Banana::CObj_Projectile_Banana()
{
}


CObj_Projectile_Banana::~CObj_Projectile_Banana()
{
	Release();
}

void CObj_Projectile_Banana::Initialize(void)
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
	
	m_fTimer = 3.0f;
}

void CObj_Projectile_Banana::Update(void)
{
	if (m_ProjectileState == PROJECTILE_STATE::NONE)
	{
		m_pMover->Update();
		m_pImage->Update();
		m_fTimer -= CTimeMgr::Get_Inst()->Get_DeltaTime();
	}
}

void CObj_Projectile_Banana::LateUpdate(void)
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

		if (m_fTimer < 0.0f)
			Bomb();
	}

	
}

void CObj_Projectile_Banana::Release(void)
{
	Safe_Delete(m_pMover);
	Safe_Delete(m_pImage);
}

void CObj_Projectile_Banana::Render(HDC _hDC)
{
	if (m_ProjectileState == PROJECTILE_STATE::NONE)
	{
		m_pImage->Render(_hDC);
	}
}

void CObj_Projectile_Banana::MapOut(void)
{
	if (m_vPos.fY > 1160)
	{
		m_bDead = true;
		CSoundMgr::Get_Instance()->StopSound(CHANNELID::PROJECTILE);
		CSoundMgr::Get_Instance()->PlaySoundW(L"Splash.wav", CHANNELID::PROJECTILE, g_fVolume);
	}
}

void CObj_Projectile_Banana::Set_Projectile(CObj * _pOwner, CMyVector2 _Pos, float _fPower, CMyVector2 _Dir)
{
	m_pOwner = _pOwner;
	m_vPos.fX = _Pos.fX;
	m_vPos.fY = _Pos.fY;
	m_fPower = _fPower * 70.0f;

	m_pMover->AddForce(_Dir * m_fPower);
}

void CObj_Projectile_Banana::MapCollision(void)
{
	bool bLeftMove = true;
	bool bRightMove = true;
	bool bUpMove = true;
	bool bDownMove = true;
	int iCenterY = -1;


	for (int x = 0; m_vCollision.fCX > x; ++x)
	{
		for (int y = 0; m_vCollision.fCY > y; ++y)
		{
			if (m_vecBoundingBox[x + (m_vCollision.fCX * y)])
			{
				if (x == 0 && y > 10 && y < 14)
				{
					bLeftMove = false;
					break;
				}

				if (x == 12)
				{
					if (iCenterY == -1 && y > 12)
						iCenterY = 24 - y;
				}

				if (x == 24 && y > 10 && y < 14)
				{
					bRightMove = false;
					break;
				}

				if (y == 0 && x > 10 && x < 14)
				{
					bUpMove = false;
				}

				if (y == 24 && x > 10 && x < 14)
				{
					bDownMove = false;
				}
			}
		}
	}

	if (bLeftMove == false)
	{
		if (m_pMover->Get_Velocity().fX < 0)
		{
			m_pMover->BrakeX(0.7f);
			m_pMover->Get_Velocity().Set_fX(m_pMover->Get_Velocity().fX * -1.0f);
			CSoundMgr::Get_Instance()->StopSound(CHANNELID::PROJECTILE);
			CSoundMgr::Get_Instance()->PlaySoundW(L"BananaImpact.wav", CHANNELID::PROJECTILE, g_fVolume);
		}
			
	}

	if (bRightMove == false)
	{
		if (m_pMover->Get_Velocity().fX > 0)
		{
			m_pMover->BrakeX(0.7f);
			m_pMover->Get_Velocity().Set_fX(m_pMover->Get_Velocity().fX * -1.0f);
			CSoundMgr::Get_Instance()->StopSound(CHANNELID::PROJECTILE);
			CSoundMgr::Get_Instance()->PlaySoundW(L"BananaImpact.wav", CHANNELID::PROJECTILE, g_fVolume);
		}
			
	}

	if (bUpMove == false)
	{
		if (m_pMover->Get_Velocity().fY < 0)
		{
			m_pMover->BrakeY(0.7f);
			m_pMover->Get_Velocity().Set_fY(m_pMover->Get_Velocity().fY * -1.0f);
			CSoundMgr::Get_Instance()->StopSound(CHANNELID::PROJECTILE);
			CSoundMgr::Get_Instance()->PlaySoundW(L"BananaImpact.wav", CHANNELID::PROJECTILE, g_fVolume);
		}
			
	}

	if (bDownMove == false)
	{
		if (m_pMover->Get_Velocity().fY > 0)
		{
			if (m_pMover->Get_Velocity().fY < 0.5f && m_pMover->Get_Velocity().fY > 0 && m_pMover->Get_Velocity().fX < 0.5f && m_pMover->Get_Velocity().fX > -0.5f)
			{
				if (iCenterY != -1)
				{
					m_pMover->Stop();
					m_pMover->Set_Gravity(0.0f);
					m_bCanCollision = false;
					m_vPos.fY = (int)(m_vPos.fY - iCenterY);
				}
			}
			else
			{
				m_pMover->BrakeX(0.9f);
				m_pMover->BrakeY(0.7f);
				m_pMover->Get_Velocity().Set_fY(m_pMover->Get_Velocity().fY * -1.0f);
				CSoundMgr::Get_Instance()->PlaySoundW(L"BananaImpact.wav", CHANNELID::PROJECTILE, g_fVolume);
			}
		}	
	}


	m_bMapCollision = false;
	fill(m_vecBoundingBox.begin(), m_vecBoundingBox.end(), false);
}

void CObj_Projectile_Banana::Angle_Update(void)
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

}

void CObj_Projectile_Banana::Bomb(void)
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

	for (int i = 0; 4 > i; ++i)
	{
		Make_Banana();
	}
	
	CSoundMgr::Get_Instance()->Random_BombSound();

}

void CObj_Projectile_Banana::Make_Banana(void)
{
	CObj*		pNewProjectile = new CObj_Projectile_ChildBanana;
	pNewProjectile->Initialize();

	float fShootPower = rand() % 20 + 50.0f;

	float fX = rand() % 3 - 1;
	float fY = -1.0f;

	CMyVector2	ShootDir = { fX, fY };
	CMyVector2  ShootPos = { m_vPos.fX, m_vPos.fY };

	static_cast<CObj_Projectile_ChildBanana*>(pNewProjectile)->Set_Projectile(m_pOwner, ShootPos, fShootPower, ShootDir);

	CObjMgr::Get_Inst()->Add_Obj(pNewProjectile->Get_ObjTyep(), pNewProjectile);

	CGameMgr::Get_Inst()->Set_TurnEnd();

	CCameraMgr::Get_Inst()->Follow_Target(pNewProjectile);
}
