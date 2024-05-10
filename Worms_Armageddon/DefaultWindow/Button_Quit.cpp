#include "stdafx.h"
#include "Button_Quit.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"
#include "SceneMgr.h"

CButton_Quit::CButton_Quit()
{
}


CButton_Quit::~CButton_Quit()
{
}

void CButton_Quit::Initialize(POINT * _pMouse)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/MainMenu/Quit1.bmp", L"Quit1");
	m_Button = CBmpMgr::Get_Instance()->Find_Image(L"Quit1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/MainMenu/Quit2.bmp", L"Quit2");
	m_Border = CBmpMgr::Get_Instance()->Find_Image(L"Quit2");

	m_vPos.fX = 1000.0;
	m_vPos.fY = 700.0;
	m_vPos.fCX = 138.0f;
	m_vPos.fCY = 37.0f;


	m_pMouse = _pMouse;
}

void CButton_Quit::Update(void)
{
	MouseUpdate();

	if (m_bMouseIn && CKeyMgr::Get_Inst()->Key_Down(VK_LBUTTON))
	{
 		CSceneMgr::Get_Inst()->Set_GameEnd();
		CSoundMgr::Get_Instance()->StopSound(CHANNELID::GAMESOUND);
		CSoundMgr::Get_Instance()->PlaySoundW(L"increaseiconnumber.wav", CHANNELID::GAMESOUND, 0.5f);
	}
}

void CButton_Quit::LateUpdate(void)
{
}

void CButton_Quit::Release(void)
{
}

void CButton_Quit::Render(HDC _hDC)
{
	if (m_bMouseIn)
	{
		BitBlt(_hDC,
			m_vPos.fX, // ������� x��ġ�� ��ǥ
			m_vPos.fY, // ���� ���� y��ġ�� ��ǥ)
			m_vPos.fCX, // ���� ���� ���� ����
			m_vPos.fCY, // ���� ���� ���� ����
			m_Border,	// ������ ��Ʈ�� �̹��� dc
			0,		// ��Ʈ���� ����� ���� x��ǥ
			0,		// ��Ʈ���� ����� ���� y��ǥ
			SRCCOPY); //�����ϰ��� �ϴ� ����
	}
	else
	{
		BitBlt(_hDC,
			m_vPos.fX, // ������� x��ġ�� ��ǥ
			m_vPos.fY, // ���� ���� y��ġ�� ��ǥ)
			m_vPos.fCX, // ���� ���� ���� ����
			m_vPos.fCY, // ���� ���� ���� ����
			m_Button,	// ������ ��Ʈ�� �̹��� dc
			0,		// ��Ʈ���� ����� ���� x��ǥ
			0,		// ��Ʈ���� ����� ���� y��ǥ
			SRCCOPY); //�����ϰ��� �ϴ� ����
	}
}
