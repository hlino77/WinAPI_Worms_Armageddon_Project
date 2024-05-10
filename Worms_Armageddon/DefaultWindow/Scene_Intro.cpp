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
		m_hVideo = MCIWndCreate(g_hWnd,			// �θ� ������ �ڵ�
			nullptr,		// mci �����츦 ����ϴ� �ν��Ͻ� �ڵ�
			WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, // WS_CHILD : �ڽ� â, WS_VISIBLE : �� ��� ȭ�鿡 �ÿ�, MCIWNDF_NOPLAYBAR : �÷��� �ٸ� �������� ����
			L"../Data/Intro/0000.wmv");	// ����� ������ ���

										//MoveWindow : �������� ����� ũ�⸦ ����
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
