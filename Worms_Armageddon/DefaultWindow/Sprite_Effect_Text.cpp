#include "stdafx.h"
#include "Sprite_Effect_Text.h"


CSprite_Effect_Text::CSprite_Effect_Text()
{
}


CSprite_Effect_Text::~CSprite_Effect_Text()
{
}

void CSprite_Effect_Text::Initialize(CObj * _pObj)
{
	m_pOwner = _pObj;





	m_SpriteState = SPRITE_STATE::END;

	m_PrevSpriteTime = GetTickCount();
	m_SpriteTime = GetTickCount();
}

void CSprite_Effect_Text::Update(void)
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

void CSprite_Effect_Text::LateUpdate(void)
{
}

void CSprite_Effect_Text::Render(HDC _hDC)
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
		RGB(128, 128, 192)); //�����ϰ��� �ϴ� ����
}

void CSprite_Effect_Text::Set_Size(void)
{
}

void CSprite_Effect_Text::Random_Text(CMyVector2 _vPos)
{
	int iTemp = rand() % 4;

	switch (iTemp)
	{
	case 0:
		Set_Text(TEXT_EFFECT_TYPE::BIFF, _vPos);
		break;
	case 1:
		Set_Text(TEXT_EFFECT_TYPE::POOT, _vPos);
		break;
	case 2:
		Set_Text(TEXT_EFFECT_TYPE::POW, _vPos);
		break;
	case 3:
		Set_Text(TEXT_EFFECT_TYPE::FOOM, _vPos);
		break;
	}
}

void CSprite_Effect_Text::Set_Text(TEXT_EFFECT_TYPE _TextType, CMyVector2 _vPos)
{
	switch (_TextType)
	{
	case TEXT_EFFECT_TYPE::BIFF:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"TextBiff");
		m_iCurr = 0;
		m_iMax = 12;
		m_DelayTime = 15;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 60.0f;
		m_fCY = 60.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	case TEXT_EFFECT_TYPE::POOT:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"TextPoot");
		m_iCurr = 0;
		m_iMax = 18;
		m_DelayTime = 15;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 70.0f;
		m_fCY = 70.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	case TEXT_EFFECT_TYPE::POW:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"TextPow");
		m_iCurr = 0;
		m_iMax = 12;
		m_DelayTime = 15;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 60.0f;
		m_fCY = 60.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	case TEXT_EFFECT_TYPE::FOOM:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"TextFoom");
		m_iCurr = 0;
		m_iMax = 20;
		m_DelayTime = 15;
		m_fX = _vPos.fX;
		m_fY = _vPos.fY;
		m_fCX = 100.0f;
		m_fCY = 100.0f;
		m_SpriteState = SPRITE_STATE::START;
		break;
	}

	
}
