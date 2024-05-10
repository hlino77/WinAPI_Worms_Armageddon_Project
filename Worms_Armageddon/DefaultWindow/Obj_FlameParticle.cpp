#include "stdafx.h"
#include "Obj_FlameParticle.h"
#include "Sprite_Effect_Flame.h"
#include "EffectMgr.h"

CObj_FlameParticle::CObj_FlameParticle()
{
}


CObj_FlameParticle::~CObj_FlameParticle()
{
	Release();
}

void CObj_FlameParticle::Initialize(void)
{
	m_ObjType = OBJ_TYPE::FLAMEPARTICLE;

	m_pMover = new CMover;
	m_pMover->Initialize(&m_vPos);
	m_pMover->Set_Mass(6.0f);


	m_vPos.fCX = 60.0f;
	m_vPos.fCY = 60.0f;
	//스프라이트
	
	m_pSprite = new CSprite_Effect_Flame;
	m_pSprite->Initialize(this);

	m_iSmokeTime = GetTickCount();
	m_iSmokeDelay = 100.0f;
}

void CObj_FlameParticle::Update(void)
{
	m_pMover->Update();
	m_pSprite->Update();

	if (m_pMover->Get_Velocity().fY > 0)
	{
		if (m_iSmokeTime + m_iSmokeDelay < GetTickCount())
		{
			CEffectMgr::Get_Inst()->Get_Smoke(SMOKE_EFFECT_TYPE::DARK20, m_vPos);
			m_iSmokeTime = GetTickCount();
		}
	}
		
}

void CObj_FlameParticle::LateUpdate(void)
{
	m_pMover->LateUpdate();
	m_pSprite->LateUpdate();

	if (m_pSprite->Get_SpriteState() == SPRITE_STATE::END)
		m_bDead = true;
}

void CObj_FlameParticle::Release(void)
{
	Safe_Delete(m_pMover);
	Safe_Delete(m_pSprite);
}

void CObj_FlameParticle::Render(HDC _hDC)
{
	m_pSprite->Render(_hDC);
}

void CObj_FlameParticle::MapOut(void)
{

}

void CObj_FlameParticle::Reset(CMyVector2 _vPos)
{
	m_vPos.fX = _vPos.fX;
	m_vPos.fY = _vPos.fY;
	
	MakeMove();
	
	static_cast<CSprite_Effect_Flame*>(m_pSprite)->Flame_Reset();
}

void CObj_FlameParticle::MakeMove(void)
{
	int iTemp = rand() % 2;
	if (iTemp == 0)
		iTemp = -1;


	int iForceX = (rand() % 30 * 10) * iTemp;

	int iForceY = (rand() % 7 * 60 + 220) * -1;

	m_pMover->Stop();
	m_pMover->AddForce(CMyVector2(iForceX, iForceY));
}
