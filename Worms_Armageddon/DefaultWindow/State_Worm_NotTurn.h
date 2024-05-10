#pragma once
#include "State_Worm.h"
class CState_Worm_NotTurn : public CState_Worm
{
public:
	CState_Worm_NotTurn();
	virtual ~CState_Worm_NotTurn();


	virtual void Initialize(CObj * _pOwner) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Release(void) override;
	virtual void Key_Input(void) override;

private:

};

