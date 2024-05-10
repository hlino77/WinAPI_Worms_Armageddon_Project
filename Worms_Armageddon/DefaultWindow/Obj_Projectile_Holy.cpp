#include "stdafx.h"
#include "Obj_Projectile_Holy.h"
#include "Image_Holy.h"
#include "TimeMgr.h"
#include "Template.h"
#include "ObjMgr.h"
#include "EffectMgr.h"
#include "Obj_Map.h"
#include "Sprite_Star.h"
#include "SoundMgr.h"


CObj_Projectile_Holy::CObj_Projectile_Holy()
{
}


CObj_Projectile_Holy::~CObj_Projectile_Holy()
{
	Release();
}

void CObj_Projectile_Holy::Initialize(void)
{
	m_ObjType = OBJ_TYPE::PROJECTILE;
	m_ProjectileState = PROJECTILE_STATE::NONE;
	m_WeaponType = WEAPON_TYPE::HOLY;

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
	m_vExplosion.fCX = 200.0f;
	m_vExplosion.fCY = 200.0f;

	//바운딩 박스
	m_vecBoundingBox.resize((UINT)(25 * 25), false);

	Update_Rect();

	m_pMover = new CMover;
	m_pMover->Initialize(&m_vPos);
	m_pMover->Set_Brake(1.0f);
	m_pMover->Set_MaxVelocity(30.0f);
	m_pMover->Set_Mass(15.0f);


	m_pImage = new CImage_Holy;
	m_pImage->Initialize(this);

	m_fAngle = 90.0f;

	//데미지
	m_iDamage = 40;


	m_bAction = true;

	m_fTimer = 3.0f;

	Initialize_Star();

	m_bEffect = false;
	m_iEffectDelay = 50;
	m_iEffectTime = 0;
	m_fEffectTime = 1.0f;
	m_bTimer = false;

	m_bSound = true;
}

void CObj_Projectile_Holy::Update(void)
{
	if (m_ProjectileState == PROJECTILE_STATE::NONE)
	{
		
		m_pMover->Update();
		m_pImage->Update();

		if(m_bTimer)
			m_fTimer -= CTimeMgr::Get_Inst()->Get_DeltaTime();

		EffectUpdate();

		for (auto iter = m_RenderList.begin(); iter != m_RenderList.end();)
		{
			if ((*iter)->Get_SpriteState() == SPRITE_STATE::START)
			{
				(*iter)->Update();
				++iter;
			}
			else
			{
				iter = m_RenderList.erase(iter);
			}
		}
	}
}

void CObj_Projectile_Holy::LateUpdate(void)
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
		else if (m_fTimer < 1.5f && m_bSound)
		{
			CSoundMgr::Get_Instance()->StopSound(CHANNELID::PROJECTILE);
			CSoundMgr::Get_Instance()->PlaySoundW(L"HOLYGRENADE.WAV", CHANNELID::PROJECTILE, g_fVolume);
			m_bSound = false;
		}
	}

}

void CObj_Projectile_Holy::Release(void)
{
	for (auto& iter : m_StarList)
	{
		Safe_Delete(iter);
	}
	m_StarList.clear();

	Safe_Delete(m_pMover);
	Safe_Delete(m_pImage);
}

void CObj_Projectile_Holy::Render(HDC _hDC)
{
	for (auto& iter : m_RenderList)
	{
		iter->Render(_hDC);
	}
	

	if (m_ProjectileState == PROJECTILE_STATE::NONE)
	{
		m_pImage->Render(_hDC);
	}
}

void CObj_Projectile_Holy::MapOut(void)
{
	if (m_vPos.fY > 1160)
	{
		m_bDead = true;
	}
}

void CObj_Projectile_Holy::Set_Projectile(CObj * _pOwner, CMyVector2 _Pos, float _fPower, CMyVector2 _Dir)
{
	m_pOwner = _pOwner;
	m_vPos.fX = _Pos.fX;
	m_vPos.fY = _Pos.fY;
	m_fPower = _fPower * 70.0f;

	m_pMover->AddForce(_Dir * m_fPower);
}

void CObj_Projectile_Holy::MapCollision(void)
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
			m_pMover->BrakeX(0.6f);
			m_pMover->Get_Velocity().Set_fX(m_pMover->Get_Velocity().fX * -1.0f);
			ResetEffect();

			CSoundMgr::Get_Instance()->StopSound(CHANNELID::PROJECTILE);
			CSoundMgr::Get_Instance()->PlaySoundW(L"HOLYGRENADEIMPACT.WAV", CHANNELID::PROJECTILE, g_fVolume);
		}

	}

	if (bRightMove == false)
	{
		if (m_pMover->Get_Velocity().fX > 0)
		{
			m_pMover->BrakeX(0.6f);
			m_pMover->Get_Velocity().Set_fX(m_pMover->Get_Velocity().fX * -1.0f);
			ResetEffect();

			CSoundMgr::Get_Instance()->StopSound(CHANNELID::PROJECTILE);
			CSoundMgr::Get_Instance()->PlaySoundW(L"HOLYGRENADEIMPACT.WAV", CHANNELID::PROJECTILE, g_fVolume);
		}

	}

	if (bUpMove == false)
	{
		if (m_pMover->Get_Velocity().fY < 0)
		{
			m_pMover->BrakeY(0.6f);
			m_pMover->Get_Velocity().Set_fY(m_pMover->Get_Velocity().fY * -1.0f);
			ResetEffect();

			CSoundMgr::Get_Instance()->StopSound(CHANNELID::PROJECTILE);
			CSoundMgr::Get_Instance()->PlaySoundW(L"HOLYGRENADEIMPACT.WAV", CHANNELID::PROJECTILE, g_fVolume);
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
					m_bTimer = true;
					m_pMover->Stop();
					m_pMover->Set_Gravity(0.0f);
					m_bCanCollision = false;
					m_vPos.fY = (int)(m_vPos.fY - iCenterY);
				}
			}
			else
			{
				m_pMover->BrakeX(0.8f);
				m_pMover->BrakeY(0.6f);
				m_pMover->Get_Velocity().Set_fY(m_pMover->Get_Velocity().fY * -1.0f);
				ResetEffect();

				CSoundMgr::Get_Instance()->PlaySoundW(L"HOLYGRENADEIMPACT.WAV", CHANNELID::PROJECTILE, g_fVolume);
			}
		}
	}


	m_bMapCollision = false;
	fill(m_vecBoundingBox.begin(), m_vecBoundingBox.end(), false);
}

void CObj_Projectile_Holy::Angle_Update(void)
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

void CObj_Projectile_Holy::Bomb(void)
{
	m_ProjectileState = PROJECTILE_STATE::BOMB;
	m_vExplosion.fX = m_vPos.fX;
	m_vExplosion.fY = m_vPos.fY;

	CObjMgr::Get_Inst()->Get_Flame(m_vExplosion, rand() % 3 + 18);
	CEffectMgr::Get_Inst()->Get_Circle(CIRCLE_EFFECT_TYPE::CIRCLE100, m_vExplosion);
	CEffectMgr::Get_Inst()->Get_Ellipse(ELLIPSE_EFFECT_TYPE::ELLIPSE100, m_vExplosion);

	ExplosionSmoke(SMOKE_EFFECT_TYPE::DARK40, rand() % 5 + 20);
	ExplosionSmoke(SMOKE_EFFECT_TYPE::WHITE100, rand() % 5 + 20);

	CEffectMgr::Get_Inst()->Get_Random_Text(m_vExplosion);

	static_cast<CObj_Map*>(CObjMgr::Get_Inst()->Get_ObjList(OBJ_TYPE::MAP)->front())->Delete_Map(m_vExplosion);

	CSoundMgr::Get_Instance()->Random_BombSound();

}

void CObj_Projectile_Holy::MakeStar(void)
{
	int iCount = rand() % 5 + 2;

	for (int i = 0; iCount > i; ++i)
	{
		static_cast<CSprite_Star*>(*m_Stariter)->Set_Star(m_vPos);
		m_RenderList.push_back(*m_Stariter);


		++m_Stariter;

		if (m_Stariter == m_StarList.end())
			m_Stariter = m_StarList.begin();
	}
}

void CObj_Projectile_Holy::Initialize_Star(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Effect/Star.bmp", L"Star");


	CSprite*		pStar = nullptr;

	for (int i = 0; 200 > i; ++i)
	{
		pStar = new CSprite_Star;
		pStar->Initialize(nullptr);
		m_StarList.push_back(pStar);
		pStar = nullptr;
	}

	m_Stariter = m_StarList.begin();
}

void CObj_Projectile_Holy::EffectUpdate(void)
{
	if (m_bEffect)
	{
		m_fEffectTime -= CTimeMgr::Get_Inst()->Get_DeltaTime();

		if (m_iEffectTime + m_iEffectDelay < GetTickCount())
		{
			MakeStar();
			m_iEffectTime = GetTickCount();
		}

		if (m_fEffectTime < 0.0f)
		{
			m_bEffect = false;
			m_fEffectTime = 1.0f;
		}
	}
}
