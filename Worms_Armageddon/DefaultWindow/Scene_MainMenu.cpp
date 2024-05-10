#include "stdafx.h"
#include "Scene_MainMenu.h"
#include "BmpMgr.h"
#include "Button_Single.h"
#include "Button_Multi.h"
#include "Button_Net.h"
#include "Button_Options.h"
#include "Button_Quit.h"
#include "SoundMgr.h"

CScene_MainMenu::CScene_MainMenu()
{
}


CScene_MainMenu::~CScene_MainMenu()
{
	Release();
}

void CScene_MainMenu::Update(void)
{
	Mouse();

	for (auto& iter : m_vecButtons)
	{
		iter->Update();
	}
}

void CScene_MainMenu::LateUpdate(void)
{
	for (auto& iter : m_vecButtons)
	{
		iter->LateUpdate();
	}
}

void CScene_MainMenu::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/MainMenu/MENUBACK.bmp", L"MenuBack");
	m_MenuBack = CBmpMgr::Get_Instance()->Find_Image(L"MenuBack");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/MainMenu/MainTitle2.bmp", L"MainTitle");
	m_Title = CBmpMgr::Get_Instance()->Find_Image(L"MainTitle");

	CSoundMgr::Get_Instance()->Initialize();

	Mouse();

	m_vecButtons.push_back(new CButton_Single);
	m_vecButtons.push_back(new CButton_Multi);
	m_vecButtons.push_back(new CButton_Net);
	m_vecButtons.push_back(new CButton_Options);
	m_vecButtons.push_back(new CButton_Quit);

	for (auto& iter : m_vecButtons)
	{
		iter->Initialize(&m_Mouse);
	}
}

void CScene_MainMenu::Release(void)
{
	for (auto& iter : m_vecButtons)
	{
		Safe_Delete(iter);
	}
	m_vecButtons.clear();
}

void CScene_MainMenu::Enter(void)
{
	Initialize();
}

void CScene_MainMenu::Render(HDC _hDC)
{
	BitBlt(_hDC, 0, 0, WINCX, WINCY, m_MenuBack, 0, 0, SRCCOPY);

	GdiTransparentBlt(_hDC,
		800 - 210, // 복사받을 x위치의 좌표
		50, // 복사 받을 y위치의 좌표)
		420, // 복사 받을 가로 길이
		139, // 복사 받을 세로 길이
		m_Title,	// 복사할 비트맵 이미지 dc
		0,		// 비트맵을 출력할 시작 x좌표
		0,		// 비트맵을 출력할 시작 y좌표
		420, // 복사할 비트맵의 가로 사이즈
		139,// 복사할 비트맵의 세로 사이즈
		RGB(255, 255, 255)); //제거하고자 하는 색상


	for (auto& iter : m_vecButtons)
	{
		iter->Render(_hDC);
	}
}

void CScene_MainMenu::Exit(void)
{
	Release();
}

void CScene_MainMenu::Mouse(void)
{
	GetCursorPos(&m_Mouse);
	ScreenToClient(g_hWnd, &m_Mouse);
}
