#include "stdafx.h"
#include "Sprite_WindUI.h"
#include "GameMgr.h"

CSprite_WindUI::CSprite_WindUI()
	:m_iSpeed(0)
{
}


CSprite_WindUI::~CSprite_WindUI()
{
}

void CSprite_WindUI::Initialize(CObj * _pObj)
{
	m_pOwner = _pObj;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Map/WindBorder2.bmp", L"WindBorder");
	m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"WindBorder");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Map/WindLeft.bmp", L"WindLeft");
	m_hLeftDC = CBmpMgr::Get_Instance()->Find_Image(L"WindLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Map/WindRight.bmp", L"WindRight");
	m_hRightDC = CBmpMgr::Get_Instance()->Find_Image(L"WindRight");


	m_iCurr = 0;
	m_iMax = 8;

	m_SpriteTime = GetTickCount();
	m_DelayTime = 10;
	m_SpriteDelay = 0;

	m_SpriteState = SPRITE_STATE::END;

	m_PrevSpriteTime = GetTickCount();

	Change_WindInfo();
	Set_Size();
}

void CSprite_WindUI::Update(void)
{
	if (m_SpriteTime + m_DelayTime < GetTickCount())
	{
		++m_iCurr;
		if (m_iCurr >= m_iMax)
		{
			m_iCurr = 0;
			m_SpriteState = SPRITE_STATE::END;
		}


		m_SpriteTime = GetTickCount();
	}


	if (m_fLength != m_fCX)
	{
		if (m_fLength > m_fCX)
			m_fCX += 1.0f;
		else if (m_fLength < m_fCX)
			m_fCX -= 1.0f;
	}
}

void CSprite_WindUI::LateUpdate(void)
{
	if (m_WindDir != CGameMgr::Get_Inst()->Get_WindDir())
		Change_WindInfo();

	if (m_iSpeed != CGameMgr::Get_Inst()->Get_WindSpeed())
		Set_Size();

	if (m_SpriteState == SPRITE_STATE::END)
	{
		m_SpriteState = SPRITE_STATE::START;
		m_SpriteTime = GetTickCount();
	}
}

void CSprite_WindUI::Render(HDC _hDC)
{
	GdiTransparentBlt(_hDC,
		1410, // ������� x��ġ�� ��ǥ
		850, // ���� ���� y��ġ�� ��ǥ)
		180, // ���� ���� ���� ����
		19, // ���� ���� ���� ����
		m_hCurrDC,	// ������ ��Ʈ�� �̹��� dc
		0,		// ��Ʈ���� ����� ���� x��ǥ
		0,		// ��Ʈ���� ����� ���� y��ǥ
		180, // ������ ��Ʈ���� ���� ������
		19,// ������ ��Ʈ���� ���� ������
		RGB(128, 128, 192)); //�����ϰ��� �ϴ� ����


	switch (m_WindDir)
	{
	case WIND_DIR::LEFT:
		Left_Render(_hDC);
		break;
	case WIND_DIR::RIGHT:
		Right_Render(_hDC);
		break;
	}
}

void CSprite_WindUI::Set_Size(void)
{
	m_iSpeed = CGameMgr::Get_Inst()->Get_WindSpeed();
	m_fLength = 28.0f * m_iSpeed;
	m_fCY = 13.0f;
}

void CSprite_WindUI::Left_Render(HDC _hDC)
{
	float fX = (float)1498 - m_fCX;
	float fY = 853.0f;

	GdiTransparentBlt(_hDC,
		fX, // ������� x��ġ�� ��ǥ
		fY, // ���� ���� y��ġ�� ��ǥ)
		m_fCX, // ���� ���� ���� ����
		13, // ���� ���� ���� ����
		m_hLeftDC,	// ������ ��Ʈ�� �̹��� dc
		m_iCurr,		// ��Ʈ���� ����� ���� x��ǥ
		0,		// ��Ʈ���� ����� ���� y��ǥ
		m_fCX, // ������ ��Ʈ���� ���� ������
		13,// ������ ��Ʈ���� ���� ������
		RGB(0, 0, 0)); //�����ϰ��� �ϴ� ����
}

void CSprite_WindUI::Right_Render(HDC _hDC)
{
	float fX = (float)1502;
	float fY = 853.0f;

	GdiTransparentBlt(_hDC,
		fX, // ������� x��ġ�� ��ǥ
		fY, // ���� ���� y��ġ�� ��ǥ)
		m_fCX, // ���� ���� ���� ����
		13, // ���� ���� ���� ����
		m_hRightDC,	// ������ ��Ʈ�� �̹��� dc
		8 - m_iCurr,		// ��Ʈ���� ����� ���� x��ǥ
		0,		// ��Ʈ���� ����� ���� y��ǥ
		m_fCX, // ������ ��Ʈ���� ���� ������
		13,// ������ ��Ʈ���� ���� ������
		RGB(0, 0, 0)); //�����ϰ��� �ϴ� ����
}

void CSprite_WindUI::Change_WindInfo(void)
{
	m_WindDir = CGameMgr::Get_Inst()->Get_WindDir();
	m_iSpeed = CGameMgr::Get_Inst()->Get_WindSpeed();

	m_fCX = 0.0f;
	Set_Size();
}
