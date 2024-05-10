#include "stdafx.h"
#include "Sprite_Worm_Winner.h"


CSprite_Worm_Winner::CSprite_Worm_Winner()
{
}


CSprite_Worm_Winner::~CSprite_Worm_Winner()
{
}

void CSprite_Worm_Winner::Initialize(CObj * _pObj)
{
	m_pOwner = _pObj;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Winner.bmp", L"Winner");

	m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Winner");


	m_iCurr = 0;
	m_iMax = 14;

	m_fCX = 60.0f;
	m_fCY = 60.0f;

	m_DelayTime = 20;
	m_SpriteDelay = 0;

	m_SpriteState = SPRITE_STATE::START;

	m_PrevSpriteTime = GetTickCount();
}

void CSprite_Worm_Winner::Update(void)
{
	if (m_SpriteState == SPRITE_STATE::START)
	{
		if (m_SpriteTime + m_DelayTime < GetTickCount())
		{
			++m_iCurr;
			if (m_iCurr >= m_iMax)
			{
				m_iCurr = 0;
			}
			m_SpriteTime = GetTickCount();
		}
	}
}

void CSprite_Worm_Winner::LateUpdate(void)
{

}

void CSprite_Worm_Winner::Render(HDC _hDC)
{
	float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
	float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();




	GdiTransparentBlt(_hDC,
		int(m_pOwner->Get_Pos().fX - m_fCX * 0.5f) + fScrollX, // ������� x��ġ�� ��ǥ
		(m_pOwner->Get_Pos().fY - m_fCY * 0.5f) + fScrollY, // ���� ���� y��ġ�� ��ǥ)
		m_fCX, // ���� ���� ���� ����
		m_fCY, // ���� ���� ���� ����
		m_hCurrDC,	// ������ ��Ʈ�� �̹��� dc
		0,		// ��Ʈ���� ����� ���� x��ǥ
		m_iCurr * m_fCY,		// ��Ʈ���� ����� ���� y��ǥ
		(int)m_fCX, // ������ ��Ʈ���� ���� ������
		(int)m_fCY,// ������ ��Ʈ���� ���� ������
		RGB(128, 128, 192)); //�����ϰ��� �ϴ� ����
}

void CSprite_Worm_Winner::Set_Size(void)
{

}
