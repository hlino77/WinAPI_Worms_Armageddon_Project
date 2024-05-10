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
		800 - 210, // ������� x��ġ�� ��ǥ
		50, // ���� ���� y��ġ�� ��ǥ)
		420, // ���� ���� ���� ����
		139, // ���� ���� ���� ����
		m_Title,	// ������ ��Ʈ�� �̹��� dc
		0,		// ��Ʈ���� ����� ���� x��ǥ
		0,		// ��Ʈ���� ����� ���� y��ǥ
		420, // ������ ��Ʈ���� ���� ������
		139,// ������ ��Ʈ���� ���� ������
		RGB(255, 255, 255)); //�����ϰ��� �ϴ� ����


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
