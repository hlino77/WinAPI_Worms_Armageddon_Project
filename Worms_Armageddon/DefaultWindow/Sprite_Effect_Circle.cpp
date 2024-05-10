#include "stdafx.h"
#include "Sprite_Effect_Circle.h"


CSprite_Effect_Circle::CSprite_Effect_Circle()
{
}


CSprite_Effect_Circle::~CSprite_Effect_Circle()
{
}

void CSprite_Effect_Circle::Initialize(CObj * _pObj)
{
	m_pOwner = _pObj;





	m_SpriteState = SPRITE_STATE::END;

	m_PrevSpriteTime = GetTickCount();
	m_SpriteTime = GetTickCount();
}

void CSprite_Effect_Circle::Update(void)
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

void CSprite_Effect_Circle::LateUpdate(void)
{
}

void CSprite_Effect_Circle::Render(HDC _hDC)
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
		RGB(128, 128, 192)); //�����ϰ��� �ϴ� ����
}

void CSprite_Effect_Circle::Set_Size(void)
{

}


void CSprite_Effect_Circle::Set_Circle(CIRCLE_EFFECT_TYPE _CircleType, CMyVector2 _vPos)
{
	switch (_CircleType)
	{
	case CIRCLE_EFFECT_TYPE::CIRCLE25:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Circle25");
		m_iCurr = 0;
		m_iMax = 8;
		m_DelayTime = 10;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 50.0f;
		m_fCY = 50.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	case CIRCLE_EFFECT_TYPE::CIRCLE50:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Circle50");
		m_iCurr = 0;
		m_iMax = 8;
		m_DelayTime = 10;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 100.0f;
		m_fCY = 100.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	case CIRCLE_EFFECT_TYPE::CIRCLE75:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Circle75");
		m_iCurr = 0;
		m_iMax = 4;
		m_DelayTime = 20;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 150.0f;
		m_fCY = 150.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	case CIRCLE_EFFECT_TYPE::CIRCLE100:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Circle100");
		m_iCurr = 0;
		m_iMax = 4;
		m_DelayTime = 20;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 200.0f;
		m_fCY = 200.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	}
}
