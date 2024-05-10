#include "stdafx.h"
#include "Mover.h"
#include "TimeMgr.h"
#include <cmath>
#include "Define.h"

CMover::CMover()
	:m_fMass(0.1f), m_fBrake(1.0f), m_fMaxVelocity(0.0f), m_fMaxVelocityX(0.0f), m_fMaxVelocityY(0.0f)
{
	m_Gravity = CMyVector2(0.0f, 9.8f);
}


CMover::~CMover()
{

}

void CMover::Initialize(CMyVector2 * _vPos)
{
	m_vPos = _vPos;
}

void CMover::Update(void)
{
	AddForce(m_Gravity * m_fMass);


	m_Accele = m_Forces * (1 / m_fMass);



	

	m_Velocity += (m_Accele * CTimeMgr::Get_Inst()->Get_DeltaTime());

	//브레이크
	m_Velocity *= m_fBrake;


	if (m_fMaxVelocityX > 0.0f && fabs(m_Velocity.fX) > m_fMaxVelocityX)
	{
		if (m_Velocity.fX < 0.0f)
			m_Velocity.fX = m_fMaxVelocityX * -1;
		else if (m_Velocity.fX > 0.0f)
			m_Velocity.fX = m_fMaxVelocityX;
	}

	if (m_fMaxVelocityY > 0.0f && fabs(m_Velocity.fY) > m_fMaxVelocityY)
	{
		if (m_Velocity.fY < 0.0f)
			m_Velocity.fY = m_fMaxVelocityY * -1;
		else if (m_Velocity.fY > 0.0f)
			m_Velocity.fY = m_fMaxVelocityY;
	}

	if (m_fMaxVelocity > 0.0f && m_Velocity.Get_Magnitude() > m_fMaxVelocity)
	{
		float fOrigin = m_Velocity.Get_Magnitude();
		float fLength = fOrigin - (fOrigin - m_fMaxVelocity);
		m_Velocity *= (fLength / fOrigin);
	}


	m_Accele *= 0.0f;
	m_Forces *= 0.0f;

}

void CMover::LateUpdate(void)
{
	(*m_vPos) += m_Velocity;
}



void CMover::SpeedUp(float _fVelocity)
{
	m_Velocity += (m_Velocity * _fVelocity *   CTimeMgr::Get_Inst()->Get_DeltaTime());
}


void CMover::Add_Slide_Velocity(CMyVector2 _Velocity)
{
	float fSlide_Speed = m_fMass * 0.1f;
	m_Velocity += (_Velocity * fSlide_Speed * CTimeMgr::Get_Inst()->Get_DeltaTime());
}