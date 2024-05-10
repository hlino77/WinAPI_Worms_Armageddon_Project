#include "stdafx.h"
#include "GameMgr.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "Sprite_WindUI.h"
#include "Obj_Worm.h"
#include "Obj_Map.h"
#include "ObjMgr.h"
#include "Obj_BackParticle.h"
#include "Obj_Cloud.h"
#include "UIMgr.h"
#include "SoundMgr.h"


CGameMgr*						CGameMgr::m_pInstance = nullptr;

CGameMgr::CGameMgr()
	:m_WindDir(WIND_DIR::TYPEEND), m_iWindSpeed(0), m_bPlayerTurn(true), m_bTurnEnd(false), m_iWinnerPlayer(0)
{
}


CGameMgr::~CGameMgr()
{
	Release();
}

void CGameMgr::Initialize(void)
{
	Change_Wind();
	m_pWindSprite = new CSprite_WindUI;
	m_pWindSprite->Initialize(nullptr);


	CObj*		pNewMap = new CObj_Map;
	pNewMap->Initialize();
	pNewMap->Set_ObjType(OBJ_TYPE::MAP);
	CObjMgr::Get_Inst()->Add_Obj(pNewMap->Get_ObjTyep(), pNewMap);


	CObj*		pNewCloud = nullptr;
	for (int i = 0; 60 > i; ++i)
	{
		pNewCloud = new CObj_Cloud;
		pNewCloud->Initialize();
		CObjMgr::Get_Inst()->Add_Obj(pNewCloud->Get_ObjTyep(), pNewCloud);
	}

	CObj*		pNewBackParticle = nullptr;
	for (int i = 0; 150 > i; ++i)
	{
		pNewBackParticle = new CObj_BackParticle;
		pNewBackParticle->Initialize();
		CObjMgr::Get_Inst()->Add_Obj(pNewBackParticle->Get_ObjTyep(), pNewBackParticle);
	}
	
	Make_Worm();

	m_MgrState = GAMEMGR_STATE::TURNSTART;

	m_EndTime = 0;
	m_EndDelay = 3000;
}

void CGameMgr::Update(void)
{

	Key_Input();

	switch (m_MgrState)
	{
	case GAMEMGR_STATE::TURNSTART:
		if (m_bTurnEnd)
		{
			m_MgrState = GAMEMGR_STATE::TURNEND;
		}
		break;
	case GAMEMGR_STATE::TURNEND:
		Find_Action();
		break;
	case GAMEMGR_STATE::ENDSTART:
		if (m_EndTime + m_EndDelay < GetTickCount())
		{
			m_MgrState = GAMEMGR_STATE::END;
		}
		break;
	case GAMEMGR_STATE::END:
		Turn_End();
		break;
	case GAMEMGR_STATE::NEXTTURN:
		Next_Turn();
		break;
	case GAMEMGR_STATE::GAMEEND:
		Set_Winner();
		break;
	}


}

void CGameMgr::LateUpdate(void)
{
	m_pWindSprite->LateUpdate();

	if (!(m_Player1Worms.empty()))
	{
		for (auto iter = m_Player1Worms.begin(); iter != m_Player1Worms.end();)
		{
			if ((*iter)->Is_Dead())
			{
				if (*iter == *m_Player1_Worm)
				{
					m_Player1_Worm = m_Player1Worms.erase(m_Player1_Worm);
					iter = m_Player1_Worm;
					if (m_Player1_Worm == m_Player1Worms.end())
						m_Player1_Worm = m_Player1Worms.begin();
				}
				else
					iter = m_Player1Worms.erase(iter);
			}
			else
				++iter;
		}
	}
	else
	{
		m_iWinnerPlayer = 2;
	}
	
	if (!(m_Player2Worms.empty()))
	{
		for (auto iter = m_Player2Worms.begin(); iter != m_Player2Worms.end();)
		{
			if ((*iter)->Is_Dead())
			{
				if (*iter == *m_Player2_Worm)
				{
					m_Player2_Worm = m_Player2Worms.erase(m_Player2_Worm);
					iter = m_Player2_Worm;
					if (m_Player2_Worm == m_Player2Worms.end())
						m_Player2_Worm = m_Player2Worms.begin();
				}
				else
					iter = m_Player2Worms.erase(iter);
			}
			else
				++iter;
		}
	}
	else
	{
		m_iWinnerPlayer = 1;
	}
}


void CGameMgr::Release(void)
{
	Safe_Delete(m_pWindSprite);
}

void CGameMgr::Render(HDC _hDC)
{
	m_pWindSprite->Render(_hDC);

}

void CGameMgr::Next_Turn(void)
{
	if (m_iWinnerPlayer > 0)
	{
		m_MgrState = GAMEMGR_STATE::GAMEEND;
		return;
	}

	if (m_bPlayerTurn)
	{
		static_cast<CObj_Worm*>(*m_Player1_Worm)->Set_Turn(false);
		static_cast<CObj_Worm*>(*m_Player1_Worm)->Set_State(WORM_STATE::NOTTURN);
		++m_Player1_Worm;
		if (m_Player1_Worm == m_Player1Worms.end())
			m_Player1_Worm = m_Player1Worms.begin();

		static_cast<CObj_Worm*>(*m_Player2_Worm)->Set_Turn(true);
		static_cast<CObj_Worm*>(*m_Player2_Worm)->Set_State(WORM_STATE::IDLE);
		CCameraMgr::Get_Inst()->Go_Target(*m_Player2_Worm);
		CSoundMgr::Get_Instance()->StopSound(CHANNELID::WORMSPEECH);
		CSoundMgr::Get_Instance()->PlaySoundW(L"YESSIR.WAV", CHANNELID::WORMSPEECH, g_fVolume);
	}
	else
	{
		static_cast<CObj_Worm*>(*m_Player2_Worm)->Set_Turn(false);
		static_cast<CObj_Worm*>(*m_Player2_Worm)->Set_State(WORM_STATE::NOTTURN);
		++m_Player2_Worm;
		if (m_Player2_Worm == m_Player2Worms.end())
			m_Player2_Worm = m_Player2Worms.begin();

		static_cast<CObj_Worm*>(*m_Player1_Worm)->Set_Turn(true);
		static_cast<CObj_Worm*>(*m_Player1_Worm)->Set_State(WORM_STATE::IDLE);
		CCameraMgr::Get_Inst()->Go_Target(*m_Player1_Worm);

		CSoundMgr::Get_Instance()->StopSound(CHANNELID::WORMSPEECH);
		CSoundMgr::Get_Instance()->PlaySoundW(L"DROP.WAV", CHANNELID::WORMSPEECH, g_fVolume);
	}

	Change_Wind();
	m_bPlayerTurn = !m_bPlayerTurn;

	m_MgrState = GAMEMGR_STATE::TURNSTART;
	m_bTurnEnd = false;
}



void CGameMgr::Change_Wind(void)
{
	int iDir = rand() % 3 - 1;
	int iSpeed = rand() % 3 + 1;

	switch (iDir)
	{
	case -1:
		m_WindDir = WIND_DIR::LEFT;
		m_iWindSpeed = iSpeed;
		break;
	case 0:
		m_WindDir = WIND_DIR::MIDDLE;
		m_iWindSpeed = 0;
		break;
	case 1:
		m_WindDir = WIND_DIR::RIGHT;
		m_iWindSpeed = iSpeed;
		break;
	}
}

void CGameMgr::Make_Worm(void)
{
	int iCount = 2;

	CObj*		pNewWorm = nullptr;

	for (int i = 0; iCount > i; ++i)
	{
		pNewWorm = new CObj_Worm;
		pNewWorm->Initialize();
		pNewWorm->Set_ObjType(OBJ_TYPE::WORM);
		static_cast<CObj_Worm*>(pNewWorm)->Set_TeamNum(1);
		CObjMgr::Get_Inst()->Add_Obj(pNewWorm->Get_ObjTyep(), pNewWorm);
		m_Player1Worms.push_back(pNewWorm);
		pNewWorm = nullptr;
	}

	m_Player1_Worm = m_Player1Worms.begin();

	for (int j = 0; iCount > j; ++j)
	{
		pNewWorm = new CObj_Worm;
		pNewWorm->Initialize();
		pNewWorm->Set_ObjType(OBJ_TYPE::WORM);
		static_cast<CObj_Worm*>(pNewWorm)->Set_TeamNum(2);
		CObjMgr::Get_Inst()->Add_Obj(pNewWorm->Get_ObjTyep(), pNewWorm);
		m_Player2Worms.push_back(pNewWorm);
		pNewWorm = nullptr;
	}

	m_Player2_Worm = m_Player2Worms.begin();

	static_cast<CObj_Worm*>(*m_Player1_Worm)->Set_Turn(true);
}

void CGameMgr::Find_Action(void)
{
	list<CObj*>* pWormList = CObjMgr::Get_Inst()->Get_ObjList(OBJ_TYPE::WORM);

	for (auto& iter : *pWormList)
	{
		if (iter->Is_Action())
			return;
	}

	list<CObj*>* pBombList = CObjMgr::Get_Inst()->Get_ObjList(OBJ_TYPE::PROJECTILE);

	for (auto& iter : *pBombList)
	{
		if (iter->Is_Action())
			return;
	}

	m_MgrState = GAMEMGR_STATE::ENDSTART;
	m_EndTime = GetTickCount();
}

void CGameMgr::Turn_End(void)
{
	list<CObj*>* pWormList = CObjMgr::Get_Inst()->Get_ObjList(OBJ_TYPE::WORM);

	for (auto& iter : *pWormList)
	{
		if (static_cast<CObj_Worm*>(iter)->Is_Damaged())
		{
			static_cast<CObj_Worm*>(iter)->Get_Damage();
		}
	}

	for (auto& iter : *pWormList)
	{
		if (static_cast<CObj_Worm*>(iter)->Get_WormHp() == 0)
		{
			static_cast<CObj_Worm*>(iter)->Dead();
			m_MgrState = GAMEMGR_STATE::TURNEND;
			CCameraMgr::Get_Inst()->Go_Target(iter);
			return;
		}
	}

	if(m_MgrState == GAMEMGR_STATE::END)
		m_MgrState = GAMEMGR_STATE::NEXTTURN;
}

void CGameMgr::Key_Input(void)
{

	if (CKeyMgr::Get_Inst()->Key_Down('T'))
	{
		Change_Wind();
	}
	m_pWindSprite->Update();

	if (CKeyMgr::Get_Inst()->Key_Down('Y'))
	{
		Next_Turn();
	}
}

void CGameMgr::Set_Winner(void)
{
	if (m_iWinnerPlayer == 1)
	{
		for (auto& iter : m_Player1Worms)
		{
			static_cast<CObj_Worm*>(iter)->Set_State(WORM_STATE::WINNER);
			CCameraMgr::Get_Inst()->Go_Target(iter);
		}
	}

	if (m_iWinnerPlayer == 2)
	{
		for (auto& iter : m_Player2Worms)
		{
			static_cast<CObj_Worm*>(iter)->Set_State(WORM_STATE::WINNER);
			CCameraMgr::Get_Inst()->Go_Target(iter);
		}
	}
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlaySoundW(L"VICTORY.WAV", CHANNELID::WORMSPEECH, g_fVolume);
	CSoundMgr::Get_Instance()->PlaySoundW(L"CrowdPart2.wav", CHANNELID::GAMESOUND, g_fVolume);
	CUIMgr::Get_Inst()->Set_UIRend(false);
	m_MgrState = GAMEMGR_STATE::TYPEEND;
}
