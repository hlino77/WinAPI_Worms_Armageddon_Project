#include "stdafx.h"
#include "Scene_Intro.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "GameMgr.h"

CScene_Intro::CScene_Intro()
{
}


CScene_Intro::~CScene_Intro()
{
	Release();
}

void CScene_Intro::Update(void)
{
	if (CKeyMgr::Get_Inst()->Key_Down(VK_SPACE))
	{
		m_hVideo = MCIWndCreate(g_hWnd,			// 부모 윈도우 핸들
			nullptr,		// mci 윈도우를 사용하는 인스턴스 핸들
			WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, // WS_CHILD : 자식 창, WS_VISIBLE : 그 즉시 화면에 시연, MCIWNDF_NOPLAYBAR : 플레이 바를 생성하지 않음
			L"../Data/Intro/0000.wmv");	// 재생할 파일의 경로

										//MoveWindow : 동영상을 재생할 크기를 설정
		MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, FALSE);

		MCIWndPlay(m_hVideo);
	}

	if (CKeyMgr::Get_Inst()->Key_Down(VK_RETURN))
	{
		CSceneMgr::Get_Inst()->Set_Next_Scene(SCENE_TYPE::MAINMENU);
		return;
	}
}

void CScene_Intro::LateUpdate(void)
{

}

void CScene_Intro::Initialize(void)
{
	CSceneMgr::Get_Inst()->Set_Intro(true);

	CGameMgr::Get_Inst()->Initialize();
}

void CScene_Intro::Release(void)
{
	
}

void CScene_Intro::Enter(void)
{
	Initialize();
}

void CScene_Intro::Render(HDC _hDC)
{
}

void CScene_Intro::Exit(void)
{
	MCIWndClose(m_hVideo);
	CSceneMgr::Get_Inst()->Set_Intro(false);
}
