#include "stdafx.h"
#include "MainGame.h"
#include "SceneMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include <ctime>


CMainGame::CMainGame()
	:m_bEnd(false)
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	srand((unsigned int)time(NULL));
	
	m_DC = GetDC(g_hWnd);

	m_hMemDC = CreateCompatibleDC(m_DC);
	m_hBitmap = CreateCompatibleBitmap(m_DC, WINCX, WINCY);
	m_hOldmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	CSceneMgr::Get_Inst()->Initialize();
}

void CMainGame::Update(void)
{
	CSceneMgr::Get_Inst()->Update();
}

void CMainGame::LateUpdate(void)
{
	CSceneMgr::Get_Inst()->LateUpdate();

	if (CSceneMgr::Get_Inst()->Is_End())
		m_bEnd = true;
}

void CMainGame::Render()
{
	if (CSceneMgr::Get_Inst()->Is_Intro())
		return;

	BitBlt(m_DC, 0, 0, WINCX, WINCY, m_hMemDC, 0, 0, SRCCOPY);
	
	
	CSceneMgr::Get_Inst()->Render(m_hMemDC);
}

void CMainGame::Release(void)
{
	CSceneMgr::Get_Inst()->Destroy_Inst();
	CBmpMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Inst()->Destroy_Inst();


	SelectObject(m_hMemDC, m_hOldmap);
	DeleteObject(m_hBitmap);
	ReleaseDC(g_hWnd, m_DC);
	DeleteDC(m_hMemDC);
}

