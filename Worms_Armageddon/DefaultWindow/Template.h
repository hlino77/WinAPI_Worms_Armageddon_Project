#pragma once
#include "stdafx.h"

template<typename T>
void	Safe_Delete(T& _Temp)
{
	if (_Temp)
	{
		delete _Temp;
		_Temp = nullptr;

		return;
	}
}

struct CDeleteMap
{
	template<typename T>
	void operator()(T& Temp)
	{
		if (Temp.second)
		{
			delete Temp.second;
			Temp.second = nullptr;
		}
	}
};


struct tagFinder
{
public:
	tagFinder(const TCHAR* pString) : m_pString(pString) {}

public:
	template<typename T>
	bool	operator()(T& MyPair)
	{
		return !lstrcmp(m_pString, MyPair.first);
	}

private:
	const TCHAR* m_pString;
};

//struct ObjFinder
//{
//public:
//	ObjFinder(CObj_HIB* _pObj) : m_pObj(_pObj) {}
//
//public:
//	bool		operator()(CObj_HIB*  _CmpObj)
//	{
//		if (m_pObj == _CmpObj)
//			return true;
//
//		return false;
//	}
//
//private:
//	CObj_HIB*  m_pObj;
//};