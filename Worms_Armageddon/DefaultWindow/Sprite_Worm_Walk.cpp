#include "stdafx.h"
#include "Sprite_Worm_Walk.h"
#include "TimeMgr.h"
#include "Obj_Worm.h"
#include "SoundMgr.h"


CSprite_Worm_Walk::CSprite_Worm_Walk()
{
}


CSprite_Worm_Walk::~CSprite_Worm_Walk()
{

}

void CSprite_Worm_Walk::Initialize(CObj * _pObj)
{
	m_pOwner = _pObj;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Left_Walk.bmp", L"Left_Walk");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Right_Walk.bmp", L"Right_Walk");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Left_Walk_Up.bmp", L"Left_Walk_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Right_Walk_Up.bmp", L"Right_Walk_Up");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Left_Walk_Down.bmp", L"Left_Walk_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/Right_Walk_Down.bmp", L"Right_Walk_Down");


	m_CurrDir = m_pOwner->Get_ObjDir();
	Change_Dir();


	m_iCurr = 0;
	m_iMax = 15;

	m_fCX = 60.0f;
	m_fCY = 60.0f;

	m_DelayTime = 15;

	m_SpriteDelay = 0;

	m_SpriteState = SPRITE_STATE::END;

	m_PrevSpriteTime = GetTickCount();


	m_bExpand = true;
}

void CSprite_Worm_Walk::Update(void)
{
	if (m_SpriteTime + m_DelayTime < GetTickCount())
	{
		++m_iCurr;

		if (m_bExpand && m_iCurr > 8)
		{
			CSoundMgr::Get_Instance()->StopSound(CHANNELID::WORMSOUND);
			CSoundMgr::Get_Instance()->PlaySoundW(L"walk-expand.wav", CHANNELID::WORMSOUND, g_fVolume - 0.1f);
			m_bExpand = false;
		}

		if (m_iCurr >= m_iMax)
		{
			m_iCurr = 0;
			m_SpriteState = SPRITE_STATE::END;
			
		}
			

		m_SpriteTime = GetTickCount();
	}



}

void CSprite_Worm_Walk::LateUpdate(void)
{
	if (m_CurrDir != m_pOwner->Get_ObjDir())
	{
		Change_Dir();
	}

	if (m_SpriteState == SPRITE_STATE::END)
	{
		m_SpriteState = SPRITE_STATE::START;
		m_SpriteTime = GetTickCount();
		m_fX = m_pOwner->Get_Pos().fX;
		Set_Angle();
		CSoundMgr::Get_Instance()->StopSound(CHANNELID::WORMSOUND);
		CSoundMgr::Get_Instance()->PlaySoundW(L"walk-compress.wav", CHANNELID::WORMSOUND, g_fVolume - 0.1f);
		m_bExpand = true;
	}
}

void CSprite_Worm_Walk::Render(HDC _hDC)
{
	Walk_Render(_hDC);
}

void CSprite_Worm_Walk::Walk_Render(HDC _hDC)
{
	float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
	float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();


	GdiTransparentBlt(_hDC,
		int(m_fX - m_fCX * 0.5f) + fScrollX, // ������� x��ġ�� ��ǥ
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

void CSprite_Worm_Walk::Change_Dir(void)
{
	switch (m_pOwner->Get_ObjDir())
	{
	case OBJ_DIR::LEFT:
		m_iCurr = 0;
		m_SpriteState = SPRITE_STATE::END;
		m_CurrDir = m_pOwner->Get_ObjDir();
		break;
	case OBJ_DIR::RIGHT:
		m_iCurr = 0;
		m_SpriteState = SPRITE_STATE::END;
		m_CurrDir = m_pOwner->Get_ObjDir();
		break;
	}
}

void CSprite_Worm_Walk::Set_Angle(void)
{
	float fLeftAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_LeftAngle();
	float fRightAngle = static_cast<CObj_Worm*>(m_pOwner)->Get_RightAngle();

	if (m_CurrDir == OBJ_DIR::LEFT)
	{
		if (fLeftAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Left_Walk_Down");
		}
		else if (fLeftAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Left_Walk_Up");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Left_Walk");
		}

	}
	else if (m_CurrDir == OBJ_DIR::RIGHT)
	{
		if (fRightAngle < -23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Right_Walk_Up");
		}
		else if (fRightAngle > 23.0f)
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Right_Walk_Down");
		}
		else
		{
			m_hCurrDC = CBmpMgr::Get_Instance()->Find_Image(L"Right_Walk");
		}
	}
}
