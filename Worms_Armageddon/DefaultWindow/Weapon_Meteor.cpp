#include "stdafx.h"
#include "Weapon_Meteor.h"
#include "BmpMgr.h"
#include "Obj_Projectile_Meteor.h"
#include "KeyMgr.h"
#include "Obj_Worm.h"
#include "ObjMgr.h"
#include "Template.h"

CWeapon_Meteor::CWeapon_Meteor()
{
}


CWeapon_Meteor::~CWeapon_Meteor()
{
	Release();
}

void CWeapon_Meteor::Update(void)
{
	Key_Input();

}

void CWeapon_Meteor::Initialize(CObj * _pOwner)
{
	m_WeaponType = WEAPON_TYPE::METEOR;
	m_WeaponState = WEAPON_STATE::IDLE;

	m_pOwner = _pOwner;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/MeteorIcon.bmp", L"MeteorIcon");
	m_MeteorIcon = CBmpMgr::Get_Instance()->Find_Image(L"MeteorIcon");

	m_pAim = nullptr;

	m_vecMeteors.reserve(20);

	for (int i = 0; 20 > i; ++i)
	{
		m_vecMeteors.push_back(new CObj_Projectile_Meteor);
	}

	for (auto& iter : m_vecMeteors)
	{
		iter->Initialize();
	}


	return;
}

void CWeapon_Meteor::LateUpdate(void)
{
}

void CWeapon_Meteor::Render(HDC _hDC)
{
	if(m_WeaponState == WEAPON_STATE::IDLE)
		IconRender(_hDC);
}

void CWeapon_Meteor::Release(void)
{
	if (!m_vecMeteors.empty())
	{
		for (auto& iter : m_vecMeteors)
		{
			Safe_Delete(iter);
		}
	}

	m_vecMeteors.clear();
}

void CWeapon_Meteor::Key_Input(void)
{
	if (CKeyMgr::Get_Inst()->Key_Down(VK_SPACE))
	{

		Shoot();


		//테스트 
		m_WeaponState = WEAPON_STATE::SHOOTEND;

		static_cast<CObj_Worm*>(m_pOwner)->Set_State(WORM_STATE::IDLE);
		static_cast<CObj_Worm*>(m_pOwner)->Put_Weapon();
	}
}

void CWeapon_Meteor::Shoot(void)
{
	int iIndex = 1;

	for (auto& iter : m_vecMeteors)
	{
		static_cast<CObj_Projectile_Meteor*>(iter)->Set_Meteor(iIndex);
		CObjMgr::Get_Inst()->Add_Obj(OBJ_TYPE::PROJECTILE, iter);
		++iIndex;
	}

	m_vecMeteors.clear();
}

void CWeapon_Meteor::ResetWeapon(void)
{

}

void CWeapon_Meteor::IconRender(HDC _hDC)
{
	float fScrollX = CCameraMgr::Get_Inst()->Get_ScrollX();
	float fScrollY = CCameraMgr::Get_Inst()->Get_ScrollY();

	if (m_pOwner->Get_ObjDir() == OBJ_DIR::LEFT)
	{
		GdiTransparentBlt(_hDC,
			int(m_pOwner->Get_Pos().fX - 25.0f - 36.0f) + fScrollX, // 복사받을 x위치의 좌표
			int(m_pOwner->Get_Pos().fY - 50.0f) + fScrollY, // 복사 받을 y위치의 좌표)
			36, // 복사 받을 가로 길이
			36, // 복사 받을 세로 길이
			m_MeteorIcon,	// 복사할 비트맵 이미지 dc
			0,		// 비트맵을 출력할 시작 x좌표
			0,		// 비트맵을 출력할 시작 y좌표
			36, // 복사할 비트맵의 가로 사이즈
			36,// 복사할 비트맵의 세로 사이즈
			RGB(128, 128, 192)); //제거하고자 하는 색상
	}
	else if (m_pOwner->Get_ObjDir() == OBJ_DIR::RIGHT)
	{
		GdiTransparentBlt(_hDC,
			int(m_pOwner->Get_Pos().fX + 25.0f) + fScrollX, // 복사받을 x위치의 좌표
			int(m_pOwner->Get_Pos().fY - 50.0f) + fScrollY, // 복사 받을 y위치의 좌표)
			36, // 복사 받을 가로 길이
			36, // 복사 받을 세로 길이
			m_MeteorIcon,	// 복사할 비트맵 이미지 dc
			0,		// 비트맵을 출력할 시작 x좌표
			0,		// 비트맵을 출력할 시작 y좌표
			36, // 복사할 비트맵의 가로 사이즈
			36,// 복사할 비트맵의 세로 사이즈
			RGB(128, 128, 192)); //제거하고자 하는 색상
	}

}
