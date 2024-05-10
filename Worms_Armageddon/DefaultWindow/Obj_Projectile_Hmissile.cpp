#include "stdafx.h"
#include "Obj_Projectile_Hmissile.h"
#include "Image_Hmissile.h"
#include "Template.h"
#include "ObjMgr.h"
#include "EffectMgr.h"
#include "Obj_Map.h"
#include "TimeMgr.h"
#include "SoundMgr.h"

CObj_Projectile_Hmissile::CObj_Projectile_Hmissile()
{
}


CObj_Projectile_Hmissile::~CObj_Projectile_Hmissile()
{
	Release();
}

void CObj_Projectile_Hmissile::Initialize(void)
{
	m_ObjType = OBJ_TYPE::PROJECTILE;
	m_ProjectileState = PROJECTILE_STATE::NONE;
	m_WeaponType = WEAPON_TYPE::HMISSILE;

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
	m_pMover->Set_MaxVelocity(15.0f);
	m_pMover->Set_Mass(10.0f);
	m_pMover->Set_Gravity(0.0f);


	m_pImage = new CImage_Hmissile;
	m_pImage->Initialize(this);

	m_ExhaustTime = GetTickCount() + 30;
	m_ExhaustDelay = 30;

	//데미지
	m_iDamage = 40;

	Set_Wind();

	m_bAction = true;

	m_fDelay = 1.0f;

	m_HmissileType = HMISSILE_TYPE::H1;

	m_fAngle = 0.0f;

	m_fTargetLength = 0.0f;

	m_fSpeed = 0.0f;
}

void CObj_Projectile_Hmissile::Update(void)
{
	if (m_ProjectileState == PROJECTILE_STATE::NONE)
	{
		switch (m_HmissileType)
		{
		case HMISSILE_TYPE::H1:
			m_pMover->Update();
			m_pImage->Update();

			m_fDelay -= CTimeMgr::Get_Inst()->Get_DeltaTime();
			if (m_fDelay < 0.0f)
			{
				m_HmissileType = HMISSILE_TYPE::H2;
				Set_Angle();
				CSoundMgr::Get_Instance()->StopSound(CHANNELID::PROJECTILE);
				CSoundMgr::Get_Instance()->PlaySoundW(L"WEAPONHOMING.WAV", CHANNELID::PROJECTILE, g_fVolume);
			}

			if (m_pMover->Get_Velocity().fX < 0.0f)
			{
				m_fAngle -= 15.0f;
				if (m_fAngle < 0.0f)
					m_fAngle = 360.0f;
			}
			else if (m_pMover->Get_Velocity().fX > 0.0f)
			{
				m_fAngle += 15.0f;

				if (m_fAngle > 360.0f)
					m_fAngle = 0.0f;
			}

			break;
		case HMISSILE_TYPE::H2:
			MissileMove();
			m_pMover->Update();


			Set_Angle();
			m_pImage->Update();
			Exhaust();
			break;
		}


	}
}

void CObj_Projectile_Hmissile::LateUpdate(void)
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

void CObj_Projectile_Hmissile::Release(void)
{
	Safe_Delete(m_pMover);
	Safe_Delete(m_pImage);
}

void CObj_Projectile_Hmissile::Render(HDC _hDC)
{
	if (m_ProjectileState == PROJECTILE_STATE::NONE)
	{
		m_pImage->Render(_hDC);
	}
}

void CObj_Projectile_Hmissile::MapOut(void)
{
	if (m_vPos.fY > 1160)
	{
		m_bDead = true;
	}
}

void CObj_Projectile_Hmissile::Set_Projectile(CObj * _pOwner, CMyVector2 _Pos, float _fPower, CMyVector2 _Dir)
{
	m_pOwner = _pOwner;
	m_vPos.fX = _Pos.fX;
	m_vPos.fY = _Pos.fY;
	m_fPower = _fPower * 50.0f;



	m_pMover->AddForce(_Dir * m_fPower);
}

void CObj_Projectile_Hmissile::MapCollision(void)
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

	CEffectMgr::Get_Inst()->Delete_Marker();

	CSoundMgr::Get_Instance()->Random_BombSound();
}

void CObj_Projectile_Hmissile::Exhaust(void)
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



void CObj_Projectile_Hmissile::MissileMove(void)
{
	float fWidth = m_vTargetPos.fX - m_vPos.fX;
	float fHeight = m_vTargetPos.fY - m_vPos.fY;

	m_fTargetLength = sqrt((fWidth * fWidth) + (fHeight * fHeight));

	
	float fX = fWidth * (20 / m_fTargetLength);
	float fY = fHeight * (20 / m_fTargetLength);

	m_fSpeed += 0.5f;

	m_pMover->AddForce(CMyVector2(fX * m_fSpeed, fY * m_fSpeed));

}

