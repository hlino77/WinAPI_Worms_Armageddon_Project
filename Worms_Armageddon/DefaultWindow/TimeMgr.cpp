#include "stdafx.h"
#include "TimeMgr.h"
#include "Define.h"

CTimeMgr*		CTimeMgr::m_pInstance = nullptr;

CTimeMgr::CTimeMgr()
	:m_prevTime(0), m_DeltaTime(0), m_Time(0)
{
}


CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::Initialize(void)
{
	m_prevTime = GetTickCount();
}

void CTimeMgr::Update(void)
{
	m_DeltaTime = GetTickCount() - m_prevTime;


	m_prevTime = GetTickCount();


	m_Time += m_DeltaTime;


}



void CTimeMgr::Release(void)
{

}
