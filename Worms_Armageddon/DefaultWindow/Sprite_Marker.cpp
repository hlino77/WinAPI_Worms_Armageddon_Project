#include "stdafx.h"
#include "Sprite_Marker.h"


CSprite_Marker::CSprite_Marker()
{
}


CSprite_Marker::~CSprite_Marker()
{
}

void CSprite_Marker::Initialize(CObj * _pObj)
{
	m_pOwner = _pObj;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Effect/Marker.bmp", L"Marker");
	m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Marker");


	m_iCurr = 0;
	m_iMax = 10;

	m_fCX = 32.0f;
	m_fCY = 32.0f;

	m_SpriteTime = GetTickCount();
	m_DelayTime = 20;
	m_SpriteDelay = 2000;

	m_SpriteState = SPRITE_STATE::END;

	m_PrevSpriteTime = GetTickCount();
}

void CSprite_Marker::Update(void)
{
	if (m_SpriteState == SPRITE_STATE::START || m_SpriteState == SPRITE_STATE::REVERSE)
	{
		if (m_SpriteTime + m_DelayTime < GetTickCount())
		{
			if (m_SpriteState == SPRITE_STATE::START)
				++m_iCurr;
			else if (m_SpriteState == SPRITE_STATE::REVERSE)
				--m_iCurr;


			if (m_iCurr >= m_iMax && m_SpriteState == SPRITE_STATE::START)
			{
				m_SpriteState = SPRITE_STATE::REVERSE;
				m_iCurr = m_iMax - 1;
			}

			if (m_iCurr <= 0 && m_SpriteState == SPRITE_STATE::REVERSE)
			{
				m_SpriteState = SPRITE_STATE::END;
				m_PrevSpriteTime = GetTickCount();
			}

			m_SpriteTime = GetTickCount();
		}
	}
	else if (m_SpriteState == SPRITE_STATE::END)
	{
		if (m_PrevSpriteTime + m_SpriteDelay <= GetTickCount())
		{
			m_SpriteState = SPRITE_STATE::START;
		}
	}
}

void CSprite_Marker::LateUpdate(void)
{
}

void CSprite_Marker::Render(HDC _hDC)
{
	float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
	float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();



	GdiTransparentBlt(_hDC,
		(int)(m_vPos.fX - m_fCX * 0.5f) + fScrollX, // ������� x��ġ�� ��ǥ
		(int)(m_vPos.fY - m_fCY * 0.5f) + fScrollY, // ���� ���� y��ġ�� ��ǥ)
		(int)m_fCX, // ���� ���� ���� ����
		(int)m_fCY, // ���� ���� ���� ����
		m_hCurrDC,	// ������ ��Ʈ�� �̹��� dc
		0,		// ��Ʈ���� ����� ���� x��ǥ
		(int)(m_iCurr * m_fCY),		// ��Ʈ���� ����� ���� y��ǥ
		(int)m_fCX, // ������ ��Ʈ���� ���� ������
		(int)m_fCY,// ������ ��Ʈ���� ���� ������
		(RGB(0, 0, 0))); //�����ϰ��� �ϴ� ����
}

void CSprite_Marker::Set_Size(void)
{

}
