#include "stdafx.h"
#include "MyButton.h"
#include "SoundMgr.h"

CMyButton::CMyButton()
	:m_bMouseIn(false), m_bSound(true)
{
}


CMyButton::~CMyButton()
{
}

void CMyButton::MouseUpdate(void)
{
	if (m_pMouse->x > m_vPos.fX && m_pMouse->x < m_vPos.fX + m_vPos.fCX &&
		m_pMouse->y > m_vPos.fY && m_pMouse->y < m_vPos.fY + m_vPos.fCY)
	{
		if (m_bSound)
		{
			CSoundMgr::Get_Instance()->StopSound(CHANNELID::GAMESOUND);
			CSoundMgr::Get_Instance()->PlaySoundW(L"KEYCLICK.WAV", CHANNELID::GAMESOUND, 0.5f);
			m_bSound = false;
		}
		m_bMouseIn = true;
	}
	else
	{
		m_bMouseIn = false;
		m_bSound = true;
	}
}
