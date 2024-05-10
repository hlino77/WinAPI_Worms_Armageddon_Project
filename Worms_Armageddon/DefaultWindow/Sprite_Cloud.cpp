#include "stdafx.h"
#include "Sprite_Cloud.h"
#include "Obj_Cloud.h"

CSprite_Cloud::CSprite_Cloud()
{
}


CSprite_Cloud::~CSprite_Cloud()
{
}

void CSprite_Cloud::Initialize(CObj * _pObj)
{
	m_pOwner = _pObj;


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Map/BlackCloud.bmp", L"BlackCloud");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Map/NormalCloud.bmp", L"NormalCloud");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Map/SmallCloud.bmp", L"SmallCloud");

	Set_Cloud();

	m_iCurr = rand() % 19;
	m_iMax = 20;

	m_SpriteTime = GetTickCount();
	m_DelayTime = 100;
	m_SpriteDelay = 100;

	m_SpriteState = SPRITE_STATE::END;

	m_PrevSpriteTime = GetTickCount();
}

void CSprite_Cloud::Update(void)
{
	switch (m_SpriteState)
	{
	case SPRITE_STATE::START:
		if (m_SpriteTime + m_DelayTime < GetTickCount())
		{
			++m_iCurr;
			if (m_iCurr >= m_iMax)
			{
				m_SpriteState = SPRITE_STATE::REVERSE;
				m_iCurr = m_iMax - 1;
			}
			m_SpriteTime = GetTickCount();
		}
		break;
	case SPRITE_STATE::REVERSE:
		if (m_SpriteTime + m_DelayTime < GetTickCount())
		{
			--m_iCurr;
			if (m_iCurr <= 0)
			{
				m_SpriteState = SPRITE_STATE::END;
				m_PrevSpriteTime = GetTickCount();
			}
			m_SpriteTime = GetTickCount();
		}
		break;
	case SPRITE_STATE::END:
		if (m_PrevSpriteTime + m_SpriteDelay <= GetTickCount())
		{
			m_SpriteState = SPRITE_STATE::START;
		}
		break;
	}
}

void CSprite_Cloud::LateUpdate(void)
{
	if (m_CurrType != static_cast<CObj_Cloud*>(m_pOwner)->Get_CloudType())
	{
		Set_Cloud();
	}
}

void CSprite_Cloud::Render(HDC _hDC)
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
		RGB(192, 192, 128)); //�����ϰ��� �ϴ� ����
}

void CSprite_Cloud::Set_Size(void)
{
	m_fCX = m_pOwner->Get_Pos().fCX;
	m_fCY = m_pOwner->Get_Pos().fCY;
}

void CSprite_Cloud::Set_Cloud(void)
{
	m_CurrType = static_cast<CObj_Cloud*>(m_pOwner)->Get_CloudType();
	Set_Size();

	switch (m_CurrType)
	{
	case CLOUD_TYPE::SMALL:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"SmallCloud");
		break;
	case CLOUD_TYPE::NORMAL:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"NormalCloud");
		break;
	case CLOUD_TYPE::BLACK:
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"BlackCloud");
		break;
	}
}
