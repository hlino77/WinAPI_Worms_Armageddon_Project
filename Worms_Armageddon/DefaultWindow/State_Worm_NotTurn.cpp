#include "stdafx.h"
#include "State_Worm_NotTurn.h"


CState_Worm_NotTurn::CState_Worm_NotTurn()
{
}


CState_Worm_NotTurn::~CState_Worm_NotTurn()
{
	Release();
}

void CState_Worm_NotTurn::Initialize(CObj * _pOwner)
{
	Set_Owner(_pOwner);
}

void CState_Worm_NotTurn::Update(void)
{

}

void CState_Worm_NotTurn::LateUpdate(void)
{
	if (*m_pBombCollision)
		BombCollision();
}

void CState_Worm_NotTurn::Release(void)
{

}

void CState_Worm_NotTurn::Key_Input(void)
{

}
