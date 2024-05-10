#include "stdafx.h"
#include "Sprite_Sea.h"


CSprite_Sea::CSprite_Sea()
{
}


CSprite_Sea::~CSprite_Sea()
{
}

void CSprite_Sea::Initialize(CObj * _pObj)
{
	m_pOwner = _pObj;

	m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"BlueWater");

	m_pOwner = _pObj;
	Set_Size();

	m_iCurr = 0;
	m_iMax = 160;

	m_fCX = 256.0f;
	m_fCY = 48.0f;

	m_SpriteTime = GetTickCount();
	m_DelayTime = 0;
	m_SpriteDelay = 0;

	m_SpriteState = SPRITE_STATE::END;

	m_PrevSpriteTime = GetTickCount();


}

void CSprite_Sea::Update(void)
{
	m_iCurr += 3;
	if (m_iCurr >= m_iMax)
		m_iCurr = 0;
}

void CSprite_Sea::LateUpdate(void)
{

}

void CSprite_Sea::Render(HDC _hDC)
{
	RECT&	CameraRect = CCameraMgr::Get_Inst()->Get_CameraRect();
	float	fCX = m_fCX * 0.5f;
	float	fCY = m_fCY * 0.5f;
	float	fX = m_fX + fCX;
	float	fY = m_fY + fCY;

	if (fX < CameraRect.left - fCX || fX > CameraRect.right + fCX || fY < CameraRect.top - fCY || fY > CameraRect.bottom + fCY)
	{
		return;
	}
	else
	{
		float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
		float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();


		GdiTransparentBlt(_hDC,
			int(m_fX + fScrollX), // ������� x��ġ�� ��ǥ
			int(m_fY + fScrollY), // ���� ���� y��ġ�� ��ǥ)
			m_fCX, // ���� ���� ���� ����
			m_fCY, // ���� ���� ���� ����
			m_hCurrDC,	// ������ ��Ʈ�� �̹��� dc
			0,		// ��Ʈ���� ����� ���� x��ǥ
			m_iCurr * m_fCY,		// ��Ʈ���� ����� ���� y��ǥ
			(int)m_fCX, // ������ ��Ʈ���� ���� ������
			(int)m_fCY,// ������ ��Ʈ���� ���� ������
			RGB(0, 0, 0)); //�����ϰ��� �ϴ� ����
	}



	
}

void CSprite_Sea::Set_Size(void)
{

}

