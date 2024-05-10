#pragma once
#include "State_Worm.h"
class CState_Worm_Swim : public CState_Worm
{
public:
	CState_Worm_Swim();
	virtual ~CState_Worm_Swim();


	virtual void Initialize(CObj * _pOwner) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Release(void) override;
	virtual void Key_Input(void) override;

private:
	DWORD			m_BubbleDelay;
	DWORD			m_BubbleTime;

	CMyVector2		m_vBubblePos;
};

