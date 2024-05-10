#include "stdafx.h"
#include "State_Worm_Dead.h"
#include "Obj_Projectile_DeadBomb.h"
#include "ObjMgr.h"


CState_Worm_Dead::CState_Worm_Dead()
{
}


CState_Worm_Dead::~CState_Worm_Dead()
{
}

void CState_Worm_Dead::Initialize(CObj * _pOwner)
{
	Set_Owner(_pOwner);
}

void CState_Worm_Dead::Update(void)
{
}

void CState_Worm_Dead::LateUpdate(void)
{
	if (static_cast<CObj_Worm*>(m_pOwner)->Get_Animator()->Get_CurrSprite()->Get_SpriteState() == SPRITE_STATE::END)
	{
		CObj*		pNewProjectile = new CObj_Projectile_DeadBomb;
		pNewProjectile->Initialize();

		m_pOwner->Set_Dead();

		static_cast<CObj_Projectile_DeadBomb*>(pNewProjectile)->Set_Projectile(m_pOwner, *m_pPos, 0.0f, CMyVector2(0.0f,0.0f));

		CObjMgr::Get_Inst()->Add_Obj(pNewProjectile->Get_ObjTyep(), pNewProjectile);
	}
}

void CState_Worm_Dead::Release(void)
{

}

void CState_Worm_Dead::Key_Input(void)
{
}

