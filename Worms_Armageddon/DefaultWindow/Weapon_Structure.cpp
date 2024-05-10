#include "stdafx.h"
#include "Weapon_Structure.h"
#include "Template.h"
#include "Obj_Structure.h"
#include "KeyMgr.h"
#include "Obj_Worm.h"
#include "ObjMgr.h"
#include "GameMgr.h"
#include "SoundMgr.h"


CWeapon_Structure::CWeapon_Structure()
{
}


CWeapon_Structure::~CWeapon_Structure()
{
	Release();
}

void CWeapon_Structure::Update(void)
{
	if (CCameraMgr::Get_Inst()->Is_Mouse() == false && m_WeaponState == WEAPON_STATE::IDLE)
	{
		CCameraMgr::Get_Inst()->ShowMouse();
		m_pMousePoint = CCameraMgr::Get_Inst()->Get_Mouse();
	}

	float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
	float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();

	m_vMousePos.fX = m_pMousePoint->x - fScrollX;
	m_vMousePos.fY = m_pMousePoint->y - fScrollY;


	Key_Input();
}

void CWeapon_Structure::Initialize(CObj * _pOwner)
{
	m_WeaponType = WEAPON_TYPE::STRUCTURE;
	m_WeaponState = WEAPON_STATE::IDLE;


	m_pOwner = _pOwner;




	m_pAim = nullptr;

	m_pStructure = new CImage_Structure;
	m_pStructure->Initialize(nullptr);

	static_cast<CImage_Structure*>(m_pStructure)->Set_Pos(&m_vMousePos);

	return;
}

void CWeapon_Structure::LateUpdate(void)
{
}

void CWeapon_Structure::Render(HDC _hDC)
{
	if(m_WeaponState == WEAPON_STATE::IDLE)
		m_pStructure->Render(_hDC);
}

void CWeapon_Structure::Release(void)
{
	Safe_Delete(m_pStructure);
}

void CWeapon_Structure::Key_Input(void)
{
	if (CKeyMgr::Get_Inst()->Key_Down(VK_LBUTTON))
	{
		Shoot();
		CSoundMgr::Get_Instance()->StopSound(CHANNELID::WEAPONSOUND);
		CSoundMgr::Get_Instance()->PlaySoundW(L"GIRDERIMPACT.WAV", CHANNELID::WEAPONSOUND, g_fVolume);

		//Å×½ºÆ® 
		m_WeaponState = WEAPON_STATE::SHOOTEND;

		m_fShootPower = 0.0f;

		static_cast<CObj_Worm*>(m_pOwner)->Set_State(WORM_STATE::IDLE);
		static_cast<CObj_Worm*>(m_pOwner)->Put_Weapon();

		if (CCameraMgr::Get_Inst()->Is_Mouse() == true)
		{
			CCameraMgr::Get_Inst()->PutMouse();
		}
	}
}

void CWeapon_Structure::Shoot(void)
{ 
	CObj*		pNewStructure;
	pNewStructure = new CObj_Structure;
	pNewStructure->Initialize();
	static_cast<CObj_Structure*>(pNewStructure)->Set_Structure(m_vMousePos);
	CObjMgr::Get_Inst()->Add_Obj(OBJ_TYPE::STRUCTURE, pNewStructure);
	
	CGameMgr::Get_Inst()->Set_TurnEnd();

}

void CWeapon_Structure::ResetWeapon(void)
{
	m_WeaponState = WEAPON_STATE::IDLE;
}
