#include "stdafx.h"
#include "Obj_Structure.h"
#include "Template.h"
#include "Obj_Map.h"
#include "ObjMgr.h"


CObj_Structure::CObj_Structure()
{
}


CObj_Structure::~CObj_Structure()
{
	Release();
}

void CObj_Structure::Initialize(void)
{
	m_pStructure = new CImage_Structure;
	m_pStructure->Initialize(this);

	m_vPos.fCX = 70.0f;
	m_vPos.fCY = 20.0f;

	


}

void CObj_Structure::Update(void)
{
}

void CObj_Structure::LateUpdate(void)
{
}

void CObj_Structure::Release(void)
{
	Safe_Delete(m_pStructure);
}

void CObj_Structure::Render(HDC _hDC)
{
	m_pStructure->Render(_hDC);
}

void CObj_Structure::MapOut(void)
{
}

void CObj_Structure::Set_Structure(CMyVector2 _vPos)
{
	m_vPos.fX = _vPos.fX; 
	m_vPos.fY = _vPos.fY;

	static_cast<CImage_Structure*>(m_pStructure)->Set_Pos(&m_vPos);

	vector<bool>* vecMapInfo = static_cast<CObj_Map*>(CObjMgr::Get_Inst()->Get_ObjList(OBJ_TYPE::MAP)->front())->Get_MapInfo();

	int iX = m_vPos.fX - m_vPos.fCX * 0.5f;
	int iY = m_vPos.fY - m_vPos.fCY * 0.5f;

	for (int y = 0; (int)(m_vPos.fCY) > y; ++y)
	{
		for (int x = 0; (int)(m_vPos.fCX) > x; ++x)
		{
			(*vecMapInfo)[iX + x + ((iY + y) * 4000)] = true;
		}
	}
}

void CObj_Structure::Delete_Structure(CMyVector2 _vExplosion)
{
	float fLengthX = m_vPos.fCX * 0.5f + _vExplosion.fCX * 0.5f;
	float fLengthY = m_vPos.fCY * 0.5f + _vExplosion.fCY * 0.5f;

	float fWidth = fabs(m_vPos.fX - _vExplosion.fX);
	float fHeight = fabs(m_vPos.fY - _vExplosion.fY);

	if (fLengthX < fWidth)
		return;

	if (fLengthY < fHeight)
		return;

	static_cast<CImage_Structure*>(m_pStructure)->Delete_Structure(_vExplosion);
}
