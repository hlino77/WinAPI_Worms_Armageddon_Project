#pragma once
#include "Enum.h"
#include "Sprite.h"


class CGameMgr
{
private:
	CGameMgr();
	~CGameMgr();
public:
	static CGameMgr*		Get_Inst(void)
	{
		if (!m_pInstance)
			m_pInstance = new CGameMgr;

		return m_pInstance;
	}
	static void		Destroy_Inst(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}

	}

	void						Initialize(void);
	void						Update(void);
	void						LateUpdate(void);
	void						Release(void);
	void						Render(HDC _hDC);

	WIND_DIR					Get_WindDir(void) { return m_WindDir; }
	int							Get_WindSpeed(void) { return m_iWindSpeed; }

	void						Set_State(GAMEMGR_STATE _State) { m_MgrState = _State; }
	GAMEMGR_STATE				Get_State(void) { return m_MgrState; }
	void						Next_Turn(void);

	void						Set_TurnEnd(void) { m_bTurnEnd = true; }

	
private:
	static CGameMgr*						m_pInstance;


	//¹Ù¶÷
	void					Change_Wind(void);
	WIND_DIR				m_WindDir;
	int						m_iWindSpeed;
	HDC						m_hWindBorder;
	CSprite*				m_pWindSprite;


	list<CObj*>				m_Player1Worms;
	list<CObj*>::iterator	m_Player1_Worm;

	list<CObj*>				m_Player2Worms;
	list<CObj*>::iterator	m_Player2_Worm;

	void					Make_Worm(void);

	bool					m_bPlayerTurn;

	bool					m_bTurnEnd;


	void					Find_Action(void);
	void					Turn_End(void);

	DWORD					m_EndDelay;
	DWORD					m_EndTime;
	bool					m_bDelayStart;

	GAMEMGR_STATE			m_MgrState;

	void					Key_Input(void);

	int						m_iWinnerPlayer;

	void					Set_Winner(void);

};

