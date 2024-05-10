#include "stdafx.h"
#include "Scene_Game.h"
#include "TimeMgr.h"
#include "ObjMgr.h"
#include "Obj_Worm.h"
#include "Enum.h"
#include "Obj_Map.h"
#include "CollisionMgr.h"
#include "Obj_Cloud.h"
#include "Obj_BackParticle.h"
#include "GameMgr.h"
#include "EffectMgr.h"
#include "CameraMgr.h"
#include "UIMgr.h"
#include "SoundMgr.h"

CScene_Game::CScene_Game()
{
}


CScene_Game::~CScene_Game()
{
	Release();
}

float g_fVolume;

void CScene_Game::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Map/BackGround.bmp", L"BackGround");
	m_hBackGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"BackGround");

	CCameraMgr::Get_Inst()->Initialize();
	CTimeMgr::Get_Inst()->Initialize();
	CObjMgr::Get_Inst()->Initialize();
	
	CUIMgr::Get_Inst()->Initialize();
	
	


	g_fVolume = 0.5f;

	
	//맵 생성후 불려져야 함
	CCollisionMgr::Get_Inst()->Initialize();

	CEffectMgr::Get_Inst()->Initialize();


	CSoundMgr::Get_Instance()->PlayBGM(L"BGM.wav", g_fVolume);
	CSoundMgr::Get_Instance()->StopSound(CHANNELID::GAMESOUND);
	CSoundMgr::Get_Instance()->PlaySoundW(L"StartRound.wav", CHANNELID::GAMESOUND, g_fVolume);
}


void CScene_Game::Update(void)
{
	CTimeMgr::Get_Inst()->Update();
	CObjMgr::Get_Inst()->Update();
	CGameMgr::Get_Inst()->Update();
	CEffectMgr::Get_Inst()->Update();
	CUIMgr::Get_Inst()->Update();

	CCameraMgr::Get_Inst()->Update();
}

void CScene_Game::LateUpdate(void)
{
	
	//오브젝트보다 먼저
	CCollisionMgr::Get_Inst()->LateUpdate();
	CObjMgr::Get_Inst()->LateUpdate();
	CGameMgr::Get_Inst()->LateUpdate();
	CEffectMgr::Get_Inst()->LateUpdate();
	CUIMgr::Get_Inst()->LateUpdate();

	CCameraMgr::Get_Inst()->LateUpdate();
}



void CScene_Game::Release(void)
{
	CCameraMgr::Get_Inst()->Destroy_Inst();
	CCollisionMgr::Get_Inst()->Destroy_Inst();
	CTimeMgr::Get_Inst()->Destroy_Inst();
	CObjMgr::Get_Inst()->Destroy_Inst();
	CGameMgr::Get_Inst()->Destroy_Inst();
	CEffectMgr::Get_Inst()->Destroy_Inst();
	CUIMgr::Get_Inst()->Destroy_Inst();
	CSoundMgr::Get_Instance()->Destroy_Instance();
}

void CScene_Game::Enter(void)
{
	Initialize();
}

void CScene_Game::Render(HDC _hDC)
{
	float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
	float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();


	BitBlt(_hDC, fScrollX, fScrollY, 4000, 1300, m_hBackGroundDC, 0, 0, SRCCOPY);
	CObjMgr::Get_Inst()->Render(_hDC);
	CGameMgr::Get_Inst()->Render(_hDC);
	CEffectMgr::Get_Inst()->Render(_hDC);
	CUIMgr::Get_Inst()->Render(_hDC);
}

void CScene_Game::Exit(void)
{
}
