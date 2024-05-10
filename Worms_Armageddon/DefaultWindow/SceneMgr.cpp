#include "stdafx.h"
#include "SceneMgr.h"
#include "Template.h"
#include "Scene_Game.h"
#include "Scene_Intro.h"
#include "Scene_MainMenu.h"

CSceneMgr*		CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	:m_bChange(false), m_bIntro(false), m_bEnd(false)
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Initialize(void)
{
	for (UINT i = 0; (UINT)SCENE_TYPE::TYPEEND > i; ++i)
	{
		m_vecScene_List.push_back(nullptr);
	}
	m_NextScene = SCENE_TYPE::INTRO;

	m_pCurrScene = Make_Scene(m_NextScene);
	m_pCurrScene->Enter();
}

void CSceneMgr::Update(void)
{
	m_pCurrScene->Update();
}

void CSceneMgr::LateUpdate(void)
{
	m_pCurrScene->LateUpdate();

	if (m_bChange == true)
		Change_Scene();
}

void CSceneMgr::Release(void)
{
	for (auto& iter : m_vecScene_List)
	{
		Safe_Delete(iter);
	}
	m_vecScene_List.clear();
}

void CSceneMgr::Render(HDC _hDC)
{
	m_pCurrScene->Render(_hDC);
}

void CSceneMgr::Change_Scene(void)
{

	m_pPrevScene = m_pCurrScene;

	m_pCurrScene = Make_Scene(m_NextScene);


	m_pCurrScene->Enter();
	m_pPrevScene->Exit();


	m_bChange = false;
}

void CSceneMgr::Set_Next_Scene(SCENE_TYPE _SceneType)
{
	m_bChange = true;
	m_NextScene = _SceneType;
}

CScene * CSceneMgr::Make_Scene(SCENE_TYPE _SceneType)
{
	if (m_vecScene_List[(UINT)_SceneType] == nullptr)
	{
		CScene* pNewScene = nullptr;
		switch (_SceneType)
		{
		case SCENE_TYPE::GAME:
			pNewScene = new CScene_Game;
			m_vecScene_List[(UINT)_SceneType] = pNewScene;
			return pNewScene;
		case SCENE_TYPE::INTRO:
			pNewScene = new CScene_Intro;
			m_vecScene_List[(UINT)_SceneType] = pNewScene;
			return pNewScene;
		case SCENE_TYPE::MAINMENU:
			pNewScene = new CScene_MainMenu;
			m_vecScene_List[(UINT)_SceneType] = pNewScene;
			return pNewScene;
		}
	}

	return m_vecScene_List[(UINT)_SceneType];
}




