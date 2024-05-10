#include "stdafx.h"
#include "Sprite_Bubble.h"


CSprite_Bubble::CSprite_Bubble()
{
}


CSprite_Bubble::~CSprite_Bubble()
{
}

void CSprite_Bubble::Initialize(CObj * _pObj)
{
	m_pOwner = _pObj;





	m_SpriteState = SPRITE_STATE::END;

	m_PrevSpriteTime = GetTickCount();
	m_SpriteTime = GetTickCount();
}

void CSprite_Bubble::Update(void)
{
	m_fY -= 1.0f;
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

void CSprite_Bubble::LateUpdate(void)
{
}

void CSprite_Bubble::Render(HDC _hDC)
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
		RGB(0, 0, 0)); //�����ϰ��� �ϴ� ����
}

void CSprite_Bubble::Set_Size(void)
{
}

void CSprite_Bubble::Random_Bubble(CMyVector2 _vPos)
{
	int iTemp = rand() % 4;

	switch (iTemp)
	{
	case 0:
		Set_Bubble(BUBBLE_TYPE::BUBBLE1, _vPos);
		break;
	case 1:
		Set_Bubble(BUBBLE_TYPE::BUBBLE2, _vPos);
		break;
	case 2:
		Set_Bubble(BUBBLE_TYPE::BUBBLE3, _vPos);
		break;
	case 3:
		Set_Bubble(BUBBLE_TYPE::BUBBLE4, _vPos);
		break;
	}
}

void CSprite_Bubble::Set_Bubble(BUBBLE_TYPE _BubbleType, CMyVector2 _vPos)
{
	switch (_BubbleType)
	{
	case BUBBLE_TYPE::BUBBLE1:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Bubble1");
		m_iCurr = 0;
		m_iMax = 16;
		m_DelayTime = 30;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 6.0f;
		m_fCY = 16.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	case BUBBLE_TYPE::BUBBLE2:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Bubble2");
		m_iCurr = 0;
		m_iMax = 16;
		m_DelayTime = 30;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 6.0f;
		m_fCY = 6.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	case BUBBLE_TYPE::BUBBLE3:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Bubble3");
		m_iCurr = 0;
		m_iMax = 16;
		m_DelayTime = 30;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 10.0f;
		m_fCY = 8.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	case BUBBLE_TYPE::BUBBLE4:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Bubble4");
		m_iCurr = 0;
		m_iMax = 16;
		m_DelayTime = 30;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 10.0f;
		m_fCY = 10.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	}
}
