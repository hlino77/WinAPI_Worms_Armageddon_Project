#include "stdafx.h"
#include "Image_Worm_Flying.h"
#include "BmpMgr.h"

CImage_Worm_Flying::CImage_Worm_Flying()
{
}


CImage_Worm_Flying::~CImage_Worm_Flying()
{
}

void CImage_Worm_Flying::Initialize(CObj * _pObj)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Fly/FlyLeft.bmp", L"FlyLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Fly/FlyRight.bmp", L"FlyRight");



	m_fAngle = 0.0f;
	m_fLength = 0.0f;
	m_iCurr = 0;
	m_iMax = 32;

	m_pOwner = _pObj;

	Set_Size();
	Set_Angle();
}

void CImage_Worm_Flying::Update(void)
{
	

	

}

void CImage_Worm_Flying::LateUpdate(void)
{
	Set_Angle();
	Set_Dir();

	m_iCurr = (int)(m_fAngle / 5.625f);
	if (m_iCurr >= m_iMax)
		m_iCurr = m_iMax - 1;
}

void CImage_Worm_Flying::Render(HDC _hDC)
{
	float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
	float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();


	GdiTransparentBlt(_hDC,
		(int)((m_pOwner->Get_Pos().fX - (m_pOwner->Get_Pos().fCX * 0.5f)) + fScrollX), // ������� x��ġ�� ��ǥ
		(int)((m_pOwner->Get_Pos().fY - (m_pOwner->Get_Pos().fCY * 0.5f)) + fScrollY), // ���� ���� y��ġ�� ��ǥ)
		(int)m_fCX, // ���� ���� ���� ����
		(int)m_fCY, // ���� ���� ���� ����
		m_hCurrDC,	// ������ ��Ʈ�� �̹��� dc
		0,		// ��Ʈ���� ����� ���� x��ǥ
		(int)(m_iCurr * m_fCY),		// ��Ʈ���� ����� ���� y��ǥ
		(int)m_fCX, // ������ ��Ʈ���� ���� ������
		(int)m_fCY,// ������ ��Ʈ���� ���� ������
		(RGB(128, 128, 192))); //�����ϰ��� �ϴ� ����
}

void CImage_Worm_Flying::Set_Size(void)
{
	m_fCX = 60.0f;
	m_fCY = 60.0f;
}

void CImage_Worm_Flying::Reset(void)
{
}

void CImage_Worm_Flying::Set_Dir(void)
{

	if (m_pOwner->Get_ObjDir() == OBJ_DIR::LEFT)
	{
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"FlyLeft");

		if (m_fAngle > 180)
		{
			m_fAngle = 360 - m_fAngle;
		}
	}
	else
	{
		m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"FlyRight");
	}
	
}
