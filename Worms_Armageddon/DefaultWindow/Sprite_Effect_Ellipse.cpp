#include "stdafx.h"
#include "Sprite_Effect_Ellipse.h"


CSprite_Effect_Ellipse::CSprite_Effect_Ellipse()
{
}


CSprite_Effect_Ellipse::~CSprite_Effect_Ellipse()
{
}

void CSprite_Effect_Ellipse::Initialize(CObj * _pObj)
{
	m_pOwner = _pObj;





	m_SpriteState = SPRITE_STATE::END;

	m_PrevSpriteTime = GetTickCount();
	m_SpriteTime = GetTickCount();
}

void CSprite_Effect_Ellipse::Update(void)
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

void CSprite_Effect_Ellipse::LateUpdate(void)
{
}

void CSprite_Effect_Ellipse::Render(HDC _hDC)
{
	float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
	float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();


	GdiTransparentBlt(_hDC,
		int(m_fX - m_fCX * 0.5f) + fScrollX, // ������� x��ġ�� ��ǥ
		(m_fY - m_fCY * 0.5f) + fScrollY, // ���� ���� y��ġ�� ��ǥ)
		m_fCX, // ���� ���� ���� ����
		m_fCY, // ���� ���� ���� ����
		m_hCurrDC,	// ������ ��Ʈ�� �̹��� dc
		0,		// ��Ʈ���� ����� ���� x��ǥ
		m_iCurr * m_fCY,		// ��Ʈ���� ����� ���� y��ǥ
		(int)m_fCX, // ������ ��Ʈ���� ���� ������
		(int)m_fCY,// ������ ��Ʈ���� ���� ������
		RGB(32, 32, 248)); //�����ϰ��� �ϴ� ����
}

void CSprite_Effect_Ellipse::Set_Size(void)
{
}

void CSprite_Effect_Ellipse::Set_Ellipse(ELLIPSE_EFFECT_TYPE _EllipseType, CMyVector2 _vPos)
{
	switch (_EllipseType)
	{
	case ELLIPSE_EFFECT_TYPE::ELLIPSE25:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Ellipse25");
		m_iCurr = 0;
		m_iMax = 20;
		m_DelayTime = 10;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 74.0f;
		m_fCY = 74.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	case ELLIPSE_EFFECT_TYPE::ELLIPSE50:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Ellipse50");
		m_iCurr = 0;
		m_iMax = 20;
		m_DelayTime = 10;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 150.0f;
		m_fCY = 150.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	case ELLIPSE_EFFECT_TYPE::ELLIPSE75:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Ellipse75");
		m_iCurr = 0;
		m_iMax = 10;
		m_DelayTime = 20;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 224.0f;
		m_fCY = 224.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	case ELLIPSE_EFFECT_TYPE::ELLIPSE100:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Ellipse100");
		m_iCurr = 0;
		m_iMax = 10;
		m_DelayTime = 20;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 300.0f;
		m_fCY = 300.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	}
}
