#include "stdafx.h"
#include "Image_Worm.h"
#include "Obj_Worm.h"

CImage_Worm::CImage_Worm()
{
}


CImage_Worm::~CImage_Worm()
{
}


void CImage_Worm::Set_Angle(void)
{
	m_fAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_WormAngle();
}
