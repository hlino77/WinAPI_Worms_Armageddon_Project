#include "stdafx.h"
#include "Sprite_Effect_Smoke.h"


CSprite_Effect_Smoke::CSprite_Effect_Smoke()
	:m_fSpeedX(0.0f), m_fSpeedY(0.0f)
{

}


CSprite_Effect_Smoke::~CSprite_Effect_Smoke()
{

}

void CSprite_Effect_Smoke::Initialize(CObj * _pObj)
{
	m_pOwner = _pObj;





	m_SpriteState = SPRITE_STATE::END;

	m_PrevSpriteTime = GetTickCount();
	m_SpriteTime = GetTickCount();
}

void CSprite_Effect_Smoke::Update(void)
{
	m_fX += m_fSpeedX;
	m_fY += m_fSpeedY;
	m_fSpeedX *= 0.97f;

	if (m_SpriteState == SPRITE_STATE::START)
	{
		if (m_SpriteTime + m_DelayTime < GetTickCount())
		{
			++m_iCurr;
			if (m_iCurr >= m_iMax)
			{
				m_SpriteState = SPRITE_STATE::END;
			}
			m_SpriteTime = GetTickCount();
		}
	}
}

void CSprite_Effect_Smoke::LateUpdate(void)
{

}

void CSprite_Effect_Smoke::Render(HDC _hDC)
{
	float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
	float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();


	GdiTransparentBlt(_hDC,
		int((m_fX - m_fCX * 0.5f) + fScrollX), // ������� x��ġ�� ��ǥ
		int((m_fY - m_fCY * 0.5f) + fScrollY), // ���� ���� y��ġ�� ��ǥ)
		m_fCX, // ���� ���� ���� ����
		m_fCY, // ���� ���� ���� ����
		m_hCurrDC,	// ������ ��Ʈ�� �̹��� dc
		0,		// ��Ʈ���� ����� ���� x��ǥ
		m_iCurr * m_fCY,		// ��Ʈ���� ����� ���� y��ǥ
		(int)m_fCX, // ������ ��Ʈ���� ���� ������
		(int)m_fCY,// ������ ��Ʈ���� ���� ������
		RGB(192, 192, 128)); //�����ϰ��� �ϴ� ����
}

void CSprite_Effect_Smoke::Set_Size(void)
{

}

void CSprite_Effect_Smoke::Set_Smoke(SMOKE_EFFECT_TYPE _SmokeType, CMyVector2 _vPos)
{
	switch (_SmokeType)
	{
	case SMOKE_EFFECT_TYPE::DARK20:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"DarkSmoke20");
		m_iCurr = 0;
		m_iMax = 28;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 20.0f;
		m_fCY = 20.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	case SMOKE_EFFECT_TYPE::DARK30:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"DarkSmoke30");
		m_iCurr = 0;
		m_iMax = 28;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 30.0f;
		m_fCY = 30.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	case SMOKE_EFFECT_TYPE::DARK40:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"DarkSmoke40");
		m_iCurr = 0;
		m_iMax = 28;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 40.0f;
		m_fCY = 40.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;

	case SMOKE_EFFECT_TYPE::WHITE25:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"WhiteSmoke25");
		m_iCurr = 0;
		m_iMax = 28;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 44.0f;
		m_fCY = 44.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	case SMOKE_EFFECT_TYPE::WHITE50:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"WhiteSmoke50");
		m_iCurr = 0;
		m_iMax = 28;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 60.0f;
		m_fCY = 60.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	case SMOKE_EFFECT_TYPE::WHITE75:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"WhiteSmoke75");
		m_iCurr = 0;
		m_iMax = 28;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 90.0f;
		m_fCY = 90.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	case SMOKE_EFFECT_TYPE::WHITE100:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"WhiteSmoke100");
		m_iCurr = 0;
		m_iMax = 28;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 134.0f;
		m_fCY = 134.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	}

	m_DelayTime = rand() % 30;
	m_fSpeedX = (rand() % 3 - 1) * 1.0f;
	m_fSpeedY = (rand() % 10 + 1) * - 0.2f;
}
