#include "stdafx.h"
#include "Obj_Projectile_Sheep.h"
#include "ObjMgr.h"
#include "EffectMgr.h"
#include "Obj_Map.h"
#include "GameMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"

CObj_Projectile_Sheep::CObj_Projectile_Sheep()
{
}


CObj_Projectile_Sheep::~CObj_Projectile_Sheep()
{
	Release();
}

void CObj_Projectile_Sheep::Initialize(void)
{
	m_ObjType = OBJ_TYPE::PROJECTILE;
	m_ProjectileState = PROJECTILE_STATE::NONE;
	m_WeaponType = WEAPON_TYPE::SHEEP;

	m_vPos.fX = 0.0f;
	m_vPos.fY = 0.0f;
	m_vPos.fCX = 60.0f;
	m_vPos.fCY = 60.0f;

	//충돌범위
	m_vCollision.fX = 0.0f;
	m_vCollision.fY = 0.0f;
	m_vCollision.fCX = 35.0f;
	m_vCollision.fCY = 25.0f;

	//폭발 범위
	m_vExplosion.fX = 0.0f;
	m_vExplosion.fY = 0.0f;
	m_vExplosion.fCX = 100.0f;
	m_vExplosion.fCY = 100.0f;

	//바운딩 박스
	m_vecBoundingBox.resize((UINT)(35 * 25), false);
	m_vecPixelX.resize(100, false);
	m_fLineLength = 100.0f;

	Update_Rect();

	m_pMover = new CMover;
	m_pMover->Initialize(&m_vPos);
	m_pMover->Set_Brake(1.0f);
	m_pMover->Set_MaxVelocityX(1.5f);
	m_pMover->Set_MaxVelocity(30.0f);
	m_pMover->Set_Mass(15.0f);

	m_pSprite = new CSprite_Sheep;
	m_pSprite->Initialize(this);
	

	//데미지
	m_iDamage = 20;


	m_bAction = true;
}

void CObj_Projectile_Sheep::Update(void)
{
	if (m_ProjectileState == PROJECTILE_STATE::NONE)
	{
		DirMove();
		m_pMover->Update();
		m_pSprite->Update();
		Key_Input();
	}
}

void CObj_Projectile_Sheep::LateUpdate(void)
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


		m_pSprite->LateUpdate();

		Update_Rect();

	}
}

void CObj_Projectile_Sheep::Release(void)
{
	Safe_Delete(m_pMover);
	Safe_Delete(m_pSprite);
}

void CObj_Projectile_Sheep::Render(HDC _hDC)
{
	if (m_ProjectileState == PROJECTILE_STATE::NONE)
		m_pSprite->Render(_hDC);
}

void CObj_Projectile_Sheep::MapOut(void)
{
	if (m_vPos.fY > 1160)
	{
		m_bDead = true;
	}
}

void CObj_Projectile_Sheep::Set_Projectile(CObj * _pOwner, CMyVector2 _Pos, float _fPower, CMyVector2 _Dir)
{
	m_pOwner = _pOwner;
	m_vPos.fX = _Pos.fX;
	m_vPos.fY = _Pos.fY;

	if (_Dir.fX < 0)
	{
		m_ObjDir = OBJ_DIR::LEFT;
	}
	if (_Dir.fX > 0)
	{
		m_ObjDir = OBJ_DIR::RIGHT;
	}

	static_cast<CSprite_Sheep*>(m_pSprite)->Change_Dir();
}

void CObj_Projectile_Sheep::MapCollision(void)
{
	bool bLeftMove = true;
	bool bRightMove = true;
	bool bUpMove = true;
	bool bDownMove = true;
	bool bJump = false;


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

				if (x == 17)
				{
					if (iCenterY == -1 && y > 12)
						iCenterY = 24 - y;
				}

				if (x == 34 && y > 10 && y < 14)
				{
					bRightMove = false;
					break;
				}

				if (y == 0 && x > 15 && x < 19)
				{
					bUpMove = false;
				}

				if (y == 24 && x > 15 && x < 19)
				{
					bDownMove = false;
				}
			}
		}
	}

	for (int x = 0; m_fLineLength > x; ++x)
	{
		if (m_vecPixelX[x])
		{
			bJump = true;
			break;
		}
	}

	if (bLeftMove == false)
	{
		if (m_pMover->Get_Velocity().fX < 0)
		{
			m_pMover->BrakeX(0.9f);
			m_pMover->Get_Velocity().Set_fX(m_pMover->Get_Velocity().fX * -1.0f);
		}

	}

	if (bRightMove == false)
	{
		if (m_pMover->Get_Velocity().fX > 0)
		{
			m_pMover->BrakeX(0.9f);
			m_pMover->Get_Velocity().Set_fX(m_pMover->Get_Velocity().fX * -1.0f);
		}

	}

	if (bUpMove == false)
	{
		if (m_pMover->Get_Velocity().fY < 0)
		{
			m_pMover->BrakeY(0.9f);
			m_pMover->Get_Velocity().Set_fY(m_pMover->Get_Velocity().fY * -1.0f);
		}

	}

	if (bDownMove == false)
	{
		if (m_pMover->Get_Velocity().fY > 0)
		{
			m_pMover->StopY();
			m_vPos.fY = (int)(m_vPos.fY - iCenterY);
			if (bJump)
			{
				m_pMover->AddForce(CMyVector2(0.0f, -4000.0f));
				CSoundMgr::Get_Instance()->StopSound(CHANNELID::PROJECTILE);
				CSoundMgr::Get_Instance()->PlaySoundW(L"SHEEPBAA.WAV", CHANNELID::PROJECTILE, g_fVolume);
			}
				
		}
	}


	

	m_bMapCollision = false;
	fill(m_vecPixelX.begin(), m_vecPixelX.end(), false);
	fill(m_vecBoundingBox.begin(), m_vecBoundingBox.end(), false);
}

void CObj_Projectile_Sheep::DirMove(void)
{
	switch (m_ObjDir)
	{
	case OBJ_DIR::LEFT:
		m_pMover->AddForce(CMyVector2(-100.0f, 0.0f));
		break;
	case OBJ_DIR::RIGHT:
		m_pMover->AddForce(CMyVector2(100.0f, 0.0f));
		break;
	}
}

void CObj_Projectile_Sheep::Key_Input(void)
{
	if (m_ProjectileState == PROJECTILE_STATE::NONE)
	{
		if (CKeyMgr::Get_Inst()->Key_Down(VK_SPACE))
		{
			Bomb();
		}
	}
	
		

}

void CObj_Projectile_Sheep::Bomb(void)
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

	CGameMgr::Get_Inst()->Set_TurnEnd();

	CSoundMgr::Get_Instance()->Random_BombSound();
}
