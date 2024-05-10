#include "stdafx.h"
#include "Sprite_Basehit.h"


CSprite_Basehit::CSprite_Basehit()
{
}


CSprite_Basehit::~CSprite_Basehit()
{
}

void CSprite_Basehit::Initialize(CObj * _pObj)
{
	m_pOwner = _pObj;





	m_SpriteState = SPRITE_STATE::END;

	m_PrevSpriteTime = GetTickCount();
	m_SpriteTime = GetTickCount();
}

void CSprite_Basehit::Update(void)
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

void CSprite_Basehit::LateUpdate(void)
{

}

void CSprite_Basehit::Render(HDC _hDC)
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

void CSprite_Basehit::Set_Size(void)
{

}

void CSprite_Basehit::Set_Basehit(CMyVector2 _vPos)
{
	m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Basehit");
	m_iCurr = 0;
	m_iMax = 9;
	m_DelayTime = 15;
	m_fX = _vPos.fX;
	m_fY = _vPos.fY;
	m_fCX = 60.0f;
	m_fCY = 60.0f;
	m_SpriteState = SPRITE_STATE::START;
}
