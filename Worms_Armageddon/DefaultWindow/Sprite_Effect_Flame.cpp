#include "stdafx.h"
#include "Sprite_Effect_Flame.h"


CSprite_Effect_Flame::CSprite_Effect_Flame()
{
}


CSprite_Effect_Flame::~CSprite_Effect_Flame()
{
}

void CSprite_Effect_Flame::Initialize(CObj * _pObj)
{
	m_pOwner = _pObj;





	m_SpriteState = SPRITE_STATE::END;

	m_PrevSpriteTime = GetTickCount();
	m_SpriteTime = GetTickCount();
}

void CSprite_Effect_Flame::Update(void)
{
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

void CSprite_Effect_Flame::LateUpdate(void)
{
	
}

void CSprite_Effect_Flame::Render(HDC _hDC)
{
	float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
	float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();



	GdiTransparentBlt(_hDC,
		int((m_pOwner->Get_Pos().fX - m_fCX * 0.5f) + fScrollX), // ������� x��ġ�� ��ǥ
		int((m_pOwner->Get_Pos().fY - m_fCY * 0.5f) + fScrollY), // ���� ���� y��ġ�� ��ǥ)
		m_fCX, // ���� ���� ���� ����
		m_fCY, // ���� ���� ���� ����
		m_hCurrDC,	// ������ ��Ʈ�� �̹��� dc
		0,		// ��Ʈ���� ����� ���� x��ǥ
		m_iCurr * m_fCY,		// ��Ʈ���� ����� ���� y��ǥ
		(int)m_fCX, // ������ ��Ʈ���� ���� ������
		(int)m_fCY,// ������ ��Ʈ���� ���� ������
		RGB(128, 128, 192)); //�����ϰ��� �ϴ� ����
}

void CSprite_Effect_Flame::Set_Size(void)
{
}

void CSprite_Effect_Flame::Flame_Reset(void)
{
	int iType = rand() % 2;

	if (iType == 0)
	{
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Flame1");
		m_iCurr = 0;
		m_iMax = 32;
		m_fCX = 60.0f;
		m_fCY = 60.0f;
		m_SpriteState = SPRITE_STATE::START;
	}
	else
	{
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Flame2");
		m_iCurr = 0;
		m_iMax = 32;
		m_fCX = 60.0f;
		m_fCY = 60.0f;
		m_SpriteState = SPRITE_STATE::START;
	}

	m_DelayTime = rand() % 60;
}
