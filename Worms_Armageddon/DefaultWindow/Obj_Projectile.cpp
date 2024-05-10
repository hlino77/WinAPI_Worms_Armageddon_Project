#include "stdafx.h"
#include "Obj_Projectile.h"
#include "EffectMgr.h"
#include "GameMgr.h"

CObj_Projectile::CObj_Projectile()
{
}


CObj_Projectile::~CObj_Projectile()
{
}

void CObj_Projectile::ExplosionSmoke(SMOKE_EFFECT_TYPE _SmokeType, int iCount)
{
	float fSize = (m_vPos.fCX / sqrt(2.0f));
	fSize *= 0.5f;


	for (int i = 0; iCount > i; ++i)
	{
		int iTemp = rand() % 2;
		if (iTemp == 0)
			iTemp = -1;

		float fX = (rand() % (int)fSize) * iTemp;
		float fY = (rand() % (int)fSize) * iTemp;

		CEffectMgr::Get_Inst()->Get_Smoke(_SmokeType, CMyVector2(m_vExplosion.fX + fX, m_vExplosion.fY + fY));
	}	
}

void CObj_Projectile::Set_Wind(void)
{
	m_WindDir = CGameMgr::Get_Inst()->Get_WindDir();
	m_iWindSpeed = CGameMgr::Get_Inst()->Get_WindSpeed();
}

void CObj_Projectile::WindMove(void)
{
	float fForce = m_iWindSpeed * 40.0f;

	if (m_WindDir == WIND_DIR::LEFT)
		fForce *= -1;

	m_pMover->AddForce(CMyVector2(fForce, 0.0f));
}
