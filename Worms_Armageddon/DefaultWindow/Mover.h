#pragma once
#include "MyVector2.h"

class CMover
{
public:
	CMover();
	~CMover();

	void				Initialize(CMyVector2* _vPos);
	void				Update(void);
	void				LateUpdate(void);
	void				AddForce(CMyVector2 _tForce) { m_Forces += _tForce; }
	void				Add_Velocity(CMyVector2 _Velocity) { m_Velocity += _Velocity; }
	void				Add_Slide_Velocity(CMyVector2 _Velocity);

	void				Set_MaxVelocity(float _fVelocity) { m_fMaxVelocity = _fVelocity; }
	void				Set_MaxVelocityX(float _fVelocityX) { m_fMaxVelocityX = _fVelocityX; }
	void				Set_MaxVelocityY(float _fVelocityY) { m_fMaxVelocityY = _fVelocityY; }


	void				Set_Brake(float _fBrake) { m_fBrake = _fBrake; }
	void				Set_Mass(float _fMass) { m_fMass = _fMass; }
	void				Set_Gravity(float _fGravity) { m_Gravity.Set_fY(_fGravity); }


	void				SpeedUp(float _fVelocity);
	void				Stop(void) { m_Velocity *= 0.0f; }
	void				StopX(void) { m_Velocity.Set_fX(0.0f); }
	void				StopY(void) { m_Velocity.Set_fY(0.0f); }
	void				Brake(float _fBrake) { m_Velocity *= _fBrake; }
	void				BrakeX(float _fBrake) { m_Velocity.fX *= _fBrake; }
	void				BrakeY(float _fBrake) { m_Velocity.fY *= _fBrake; }

	CMyVector2&			Get_Velocity(void) { return m_Velocity; }

private:
	CMyVector2		m_Velocity;
	CMyVector2		m_Accele;
	CMyVector2		m_Forces;
	CMyVector2		m_Gravity;

	float m_fMass;
	float m_fBrake;

	float m_fMaxVelocity;
	float m_fMaxVelocityX;
	float m_fMaxVelocityY;

	CMyVector2*		m_vPos;
};

