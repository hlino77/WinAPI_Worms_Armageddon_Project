#include "stdafx.h"
#include "State_Worm_Swim.h"
#include "EffectMgr.h"

CState_Worm_Swim::CState_Worm_Swim()
{
}


CState_Worm_Swim::~CState_Worm_Swim()
{
}

void CState_Worm_Swim::Initialize(CObj * _pOwner)
{
	Set_Owner(_pOwner);

	m_BubbleDelay = 200.0f;
	m_BubbleTime = GetTickCount();
}

void CState_Worm_Swim::Update(void)
{
	m_pPos->fY += 0.5f;

	m_vBubblePos.fX = m_pPos->fX - 8.0f;
	m_vBubblePos.fY = m_pPos->fY - 2.0f;

	if (m_BubbleTime + m_BubbleDelay < GetTickCount())
	{
		CEffectMgr::Get_Inst()->Get_RandomBubble(m_vBubblePos);
		m_BubbleTime = GetTickCount();
	}
		
}

void CState_Worm_Swim::LateUpdate(void)
{
	if (m_pPos->fY > 1300.0f)
		m_pOwner->Set_Dead();
}

void CState_Worm_Swim::Release(void)
{

}

void CState_Worm_Swim::Key_Input(void)
{
}
