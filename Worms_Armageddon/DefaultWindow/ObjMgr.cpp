#include "stdafx.h"
#include "ObjMgr.h"
#include "Template.h"
#include "Obj_FlameParticle.h"
#include "EffectMgr.h"
#include "Obj_Structure.h"

CObjMgr*					CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{

}


CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Add_Obj(OBJ_TYPE _ObjType, CObj * _pObj)
{
	m_Obj_List[(UINT)_ObjType].push_back(_pObj);
}

void CObjMgr::Delete_Obj(OBJ_TYPE _ObjType, CObj * _pObj)
{
	for (list<CObj*>::iterator iter = m_Obj_List[(UINT)_ObjType].begin();
		iter != m_Obj_List[(UINT)_ObjType].end();)
	{
		if (*iter == _pObj)
		{
			Safe_Delete(*iter);
			iter = m_Obj_List[(UINT)_ObjType].erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CObjMgr::Get_Flame(CMyVector2 _vPos, int iCount)
{
	for (int i = 0; iCount > i; ++i)
	{
		(*m_Flameiter)->Set_Alive();
		static_cast<CObj_FlameParticle*>(*m_Flameiter)->Reset(_vPos);
		Add_Obj(OBJ_TYPE::FLAMEPARTICLE, *m_Flameiter);
		++m_Flameiter;

		if (m_Flameiter == m_FlameList.end())
			m_Flameiter = m_FlameList.begin();
	}
}

void CObjMgr::Delete_Structure(CMyVector2 _vExplosion)
{
	for (auto& iter : m_Obj_List[(UINT)OBJ_TYPE::STRUCTURE])
	{
		static_cast<CObj_Structure*>(iter)->Delete_Structure(_vExplosion);
	}
}



void CObjMgr::Initialize(void)
{
	Initialize_Flame();
}

void CObjMgr::Update(void)
{
	for (auto& Mapiter : m_Obj_List)
	{
		for (auto& Listiter : Mapiter.second)
		{
			Listiter->Update();
		}
	}
}

void CObjMgr::LateUpdate(void)
{
	for (auto& Mapiter : m_Obj_List)
	{
		for (auto& Listiter = Mapiter.second.begin(); Listiter != Mapiter.second.end();)
		{
			(*Listiter)->LateUpdate();

			if ((*Listiter)->Is_Dead())
			{
				if ((*Listiter)->Get_ObjTyep() == OBJ_TYPE::FLAMEPARTICLE)
				{
					Listiter = Mapiter.second.erase(Listiter);
				}
				else
				{
					Safe_Delete(*Listiter);
					Listiter = Mapiter.second.erase(Listiter);
				}
			}
			else
			{
				++Listiter;
			}
		}
	}

	
}

void CObjMgr::Release(void)
{
	for (auto& Mapiter : m_Obj_List)
	{
		for (auto& Listiter : Mapiter.second)
		{
			if(Listiter->Get_ObjTyep() != OBJ_TYPE::FLAMEPARTICLE)
				Safe_Delete(Listiter);
		}
	}
	m_Obj_List.clear();

	for (auto& Listiter : m_FlameList)
	{
		Safe_Delete(Listiter);
	}
	m_FlameList.clear();
}

void CObjMgr::Render(HDC _hDC)
{
	for (auto& Mapiter : m_Obj_List)
	{
		for (auto& Listiter : Mapiter.second)
		{
			Listiter->Render(_hDC);
		}
	}
	
}


void CObjMgr::Initialize_Flame(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Effect/Flame1.bmp", L"Flame1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Effect/Flame1.bmp", L"Flame2");

	CObj* pNewFlame = nullptr;

	for (int i = 0; 40 > i; ++i)
	{
		pNewFlame = new CObj_FlameParticle;
		pNewFlame->Initialize();
		m_FlameList.push_back(pNewFlame);
	}

	m_Flameiter = m_FlameList.begin();
}
