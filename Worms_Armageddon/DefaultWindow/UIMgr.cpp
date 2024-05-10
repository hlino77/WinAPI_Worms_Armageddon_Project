#include "stdafx.h"
#include "UIMgr.h"
#include "Image_HpBox.h"
#include "Image_Font.h"
#include "Image_HpBox.h"
#include "Image_Font.h"
#include "Obj_Worm.h"
#include "ObjMgr.h"
#include "GameMgr.h"
#include "KeyMgr.h"
#include "Image_Inventory.h"
#include "SoundMgr.h"


CUIMgr*							CUIMgr::m_pInstance = nullptr;


CUIMgr::CUIMgr()
	:m_bUIRend(true), m_bInven(false), m_pInventory(nullptr)
{
}


CUIMgr::~CUIMgr()
{
	Release();
}

void CUIMgr::Initialize(void)
{
	m_pHpBox = new CImage_HpBox;
	m_pHpBox->Initialize(nullptr);
	m_pFont = new CImage_Font;
	m_pFont->Initialize(nullptr);

	m_pInvenImage = new CImage_Inventory;
	m_pInvenImage->Initialize(nullptr);
	static_cast<CImage_Inventory*>(m_pInvenImage)->Set_Pos(&m_vInvenPos);

	m_pObjList = CObjMgr::Get_Inst()->Get_ObjList(OBJ_TYPE::WORM);

	m_vInvenPos.fX = 1600.0f;
	m_vInvenPos.fY = 450.0f;
	m_vInvenPos.fCX = 180.0f;
	m_vInvenPos.fCY = 380.0f;

	m_InvenState = INVEN_UI_STATE::TYPEEND;
}

void CUIMgr::Update(void)
{
	if (m_bInven)
		Inventory_Update();
}

void CUIMgr::LateUpdate(void)
{

}

void CUIMgr::Render(HDC _hDC)
{
	if(m_bUIRend)
		Render_Hp(_hDC);

	if (m_bInven)
		Render_Inventory(_hDC);
}

void CUIMgr::Release(void)
{
	Safe_Delete(m_pFont);
	Safe_Delete(m_pHpBox);
	Safe_Delete(m_pInvenImage);
}



void CUIMgr::Render_Hp(HDC _hDC)
{
	for (auto& iter : *m_pObjList)
	{
		int iHp = static_cast<CObj_Worm*>(iter)->Get_WormHp();

		CMyVector2		vHpPos;
		vHpPos.fX = int(iter->Get_Pos().fX);
		vHpPos.fY = int(iter->Get_Pos().fY) - 30;

		int iTeamNum = static_cast<CObj_Worm*>(iter)->Get_TeamNum();
		int iSize = 3;
		int iFirst = iHp / 100;
		int iSecond = (iHp % 100) / 10;
		int iThird = iHp % 10;

		if (iFirst == 0)
			--iSize;
		

		vHpPos.fCX = iSize * 10.0f + 6.0f;

		static_cast<CImage_HpBox*>(m_pHpBox)->Size_Render(_hDC, vHpPos, iSize);


		for (int i = 0; iSize > i; ++i)
		{
			CMyVector2 vPos = { (vHpPos.fX + vHpPos.fCX * 0.5f) - 8.0f - (10.0f * i),vHpPos.fY - 1.0f };

			if(i == 0)
				static_cast<CImage_Font*>(m_pFont)->Render_Num(_hDC, iThird, iTeamNum, vPos);
			if(i == 1)
				static_cast<CImage_Font*>(m_pFont)->Render_Num(_hDC, iSecond, iTeamNum, vPos);
			if(i == 2)
				static_cast<CImage_Font*>(m_pFont)->Render_Num(_hDC, iFirst, iTeamNum, vPos);
		}	
	}
}

void CUIMgr::Render_Inventory(HDC _hDC)
{
	m_pInvenImage->Render(_hDC);
}

void CUIMgr::Inventory_Update(void)
{
	switch (m_InvenState)
	{
	case INVEN_UI_STATE::DRAW:
		if (m_vInvenPos.fX >= 1410.0f)
		{
			m_vInvenPos.fX -= 10.0f;
			if (m_vInvenPos.fX < 1410.0f)
			{
				m_vInvenPos.fX = 1410.0f;
				m_InvenState = INVEN_UI_STATE::STOP;
			}		
		}
		break;
	case INVEN_UI_STATE::STOP:
		Inventory_KeyInput();
		break;
	case INVEN_UI_STATE::PUT:
		if (m_vInvenPos.fX <= 1600.0f)
		{
			m_vInvenPos.fX += 10.0f;
			if (m_vInvenPos.fX > 1600.0f)
			{
				m_vInvenPos.fX = 1600.0f;
				m_InvenState = INVEN_UI_STATE::TYPEEND;
				m_bInven = false;
				m_pInventory = nullptr;
			}
		}
		break;
	}
}

void CUIMgr::Select_Inventory(void)
{
	POINT* pMouse = CCameraMgr::Get_Inst()->Get_Mouse();

	float fX =  pMouse->x - (m_vInvenPos.fX + 33.0f);
	float fY = pMouse->y - (m_vInvenPos.fY + 1.0f);

	if (fX < 0 || fY < 0)
		return;

	int iX = fX / 29.0f;
	int iY = fY / 29.0f;

	if (iX == 0 && iY == 1)
	{
		m_pInventory->Set_OwnerWeapon(WEAPON_TYPE::BAZOOKA);
		Get_Inventory(nullptr);
		CSoundMgr::Get_Instance()->StopSound(CHANNELID::GAMESOUND);
		CSoundMgr::Get_Instance()->PlaySoundW(L"CursorSelect.wav", CHANNELID::GAMESOUND, g_fVolume);
		return;
	}

	if (iX == 1 && iY == 1)
	{
		m_pInventory->Set_OwnerWeapon(WEAPON_TYPE::HMISSILE);
		Get_Inventory(nullptr);
		CSoundMgr::Get_Instance()->StopSound(CHANNELID::GAMESOUND);
		CSoundMgr::Get_Instance()->PlaySoundW(L"CursorSelect.wav", CHANNELID::GAMESOUND, g_fVolume);
		return;
	}

	if (iX == 2 && iY == 2)
	{
		m_pInventory->Set_OwnerWeapon(WEAPON_TYPE::BANANA);
		Get_Inventory(nullptr);
		CSoundMgr::Get_Instance()->StopSound(CHANNELID::GAMESOUND);
		CSoundMgr::Get_Instance()->PlaySoundW(L"CursorSelect.wav", CHANNELID::GAMESOUND, g_fVolume);
		return;
	}

	if (iX == 2 && iY == 5)
	{
		m_pInventory->Set_OwnerWeapon(WEAPON_TYPE::SHEEP);
		Get_Inventory(nullptr);
		CSoundMgr::Get_Instance()->StopSound(CHANNELID::GAMESOUND);
		CSoundMgr::Get_Instance()->PlaySoundW(L"CursorSelect.wav", CHANNELID::GAMESOUND, g_fVolume);
		return;
	}

	if (iX == 1 && iY == 11)
	{
		m_pInventory->Set_OwnerWeapon(WEAPON_TYPE::DONKEY);
		Get_Inventory(nullptr);
		CSoundMgr::Get_Instance()->StopSound(CHANNELID::GAMESOUND);
		CSoundMgr::Get_Instance()->PlaySoundW(L"CursorSelect.wav", CHANNELID::GAMESOUND, g_fVolume);
		return;
	}

	if (iX == 0 && iY == 11)
	{
		m_pInventory->Set_OwnerWeapon(WEAPON_TYPE::METEOR);
		Get_Inventory(nullptr);
		CSoundMgr::Get_Instance()->StopSound(CHANNELID::GAMESOUND);
		CSoundMgr::Get_Instance()->PlaySoundW(L"CursorSelect.wav", CHANNELID::GAMESOUND, g_fVolume);
		return;
	}

	if (iX == 0 && iY == 6)
	{
		m_pInventory->Set_OwnerWeapon(WEAPON_TYPE::AIRMISSILE);
		Get_Inventory(nullptr);
		CSoundMgr::Get_Instance()->StopSound(CHANNELID::GAMESOUND);
		CSoundMgr::Get_Instance()->PlaySoundW(L"CursorSelect.wav", CHANNELID::GAMESOUND, g_fVolume);
		return;
	}
	if (iX == 3 && iY == 7)
	{
		m_pInventory->Set_OwnerWeapon(WEAPON_TYPE::BASEBALL);
		Get_Inventory(nullptr);
		CSoundMgr::Get_Instance()->StopSound(CHANNELID::GAMESOUND);
		CSoundMgr::Get_Instance()->PlaySoundW(L"CursorSelect.wav", CHANNELID::GAMESOUND, g_fVolume);
		return;
	}

	if (iX == 3 && iY == 8)
	{
		m_pInventory->Set_OwnerWeapon(WEAPON_TYPE::TELEPORT);
		Get_Inventory(nullptr);
		CSoundMgr::Get_Instance()->StopSound(CHANNELID::GAMESOUND);
		CSoundMgr::Get_Instance()->PlaySoundW(L"CursorSelect.wav", CHANNELID::GAMESOUND, g_fVolume);
		return;
	}

	if (iX == 2 && iY == 7)
	{
		m_pInventory->Set_OwnerWeapon(WEAPON_TYPE::STRUCTURE);
		Get_Inventory(nullptr);
		CSoundMgr::Get_Instance()->StopSound(CHANNELID::GAMESOUND);
		CSoundMgr::Get_Instance()->PlaySoundW(L"CursorSelect.wav", CHANNELID::GAMESOUND, g_fVolume);
		return;
	}

	if (iX == 0 && iY == 9)
	{
		m_pInventory->Set_OwnerWeapon(WEAPON_TYPE::HOLY);
		Get_Inventory(nullptr);
		CSoundMgr::Get_Instance()->StopSound(CHANNELID::GAMESOUND);
		CSoundMgr::Get_Instance()->PlaySoundW(L"CursorSelect.wav", CHANNELID::GAMESOUND, g_fVolume);
		return;
	}

	CSoundMgr::Get_Instance()->StopSound(CHANNELID::GAMESOUND);
	CSoundMgr::Get_Instance()->PlaySoundW(L"WARNINGBEEP.WAV", CHANNELID::GAMESOUND, g_fVolume);
}

void CUIMgr::Inventory_KeyInput(void)
{
	if (CKeyMgr::Get_Inst()->Key_Down(VK_LBUTTON))
	{
		Select_Inventory();
	}
}


void CUIMgr::Get_Inventory(CInventory * _pInventory)
{
	if (!m_bInven)
	{
		m_pInventory = _pInventory;
		m_InvenState = INVEN_UI_STATE::DRAW;
		m_bInven = true;
		CCameraMgr::Get_Inst()->ShowMouse();
	}
	else
	{
		m_pInventory = nullptr;
		m_InvenState = INVEN_UI_STATE::PUT;
		CCameraMgr::Get_Inst()->PutMouse();
	}
		
}
