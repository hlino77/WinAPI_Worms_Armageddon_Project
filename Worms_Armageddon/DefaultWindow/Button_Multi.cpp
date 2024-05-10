#include "stdafx.h"
#include "Button_Multi.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

CButton_Multi::CButton_Multi()
{
}


CButton_Multi::~CButton_Multi()
{
	Release();
}

void CButton_Multi::Initialize(POINT * _pMouse)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/MainMenu/Multi.bmp", L"Multi");
	m_Button = CBmpMgr::Get_Instance()->Find_Image(L"Multi");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/MainMenu/Border.bmp", L"Border");
	m_Border = CBmpMgr::Get_Instance()->Find_Image(L"Border");

	m_vPos.fX = 900.0;
	m_vPos.fY = 300.0f;
	m_vPos.fCX = 240.0f;
	m_vPos.fCY = 150.0f;

	m_pMouse = _pMouse;
}

void CButton_Multi::Update(void)
{
	MouseUpdate();


	if (m_bMouseIn && CKeyMgr::Get_Inst()->Key_Down(VK_LBUTTON))
	{
		CSceneMgr::Get_Inst()->Set_Next_Scene(SCENE_TYPE::GAME);
		CSoundMgr::Get_Instance()->StopSound(CHANNELID::GAMESOUND);
		CSoundMgr::Get_Instance()->PlaySoundW(L"increaseiconnumber.wav", CHANNELID::GAMESOUND, 0.5f);
	}
}

void CButton_Multi::LateUpdate(void)
{
}

void CButton_Multi::Release(void)
{
}

void CButton_Multi::Render(HDC _hDC)
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

	if (m_bMouseIn)
	{
		GdiTransparentBlt(_hDC,
			m_vPos.fX, // ������� x��ġ�� ��ǥ
			m_vPos.fY, // ���� ���� y��ġ�� ��ǥ)
			m_vPos.fCX, // ���� ���� ���� ����
			m_vPos.fCY, // ���� ���� ���� ����
			m_Border,	// ������ ��Ʈ�� �̹��� dc
			0,		// ��Ʈ���� ����� ���� x��ǥ
			0,		// ��Ʈ���� ����� ���� y��ǥ
			m_vPos.fCX, // ������ ��Ʈ���� ���� ������
			m_vPos.fCY,// ������ ��Ʈ���� ���� ������
			RGB(0, 0, 0)); //�����ϰ��� �ϴ� ����
	}
}
