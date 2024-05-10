#include "stdafx.h"
#include "EffectMgr.h"
#include "Sprite_Effect_Circle.h"
#include "Sprite_Effect_Ellipse.h"
#include "Sprite_Effect_Exhaust.h"
#include "Sprite_Effect_Smoke.h"
#include "Sprite_Effect_Text.h"
#include "Sprite_SlideSmoke.h"
#include "Sprite_MinusHp.h"
#include "Sprite_Bubble.h"
#include "Sprite_Basehit.h"
#include "Sprite_Star.h"
#include "Sprite_Marker.h"


CEffectMgr*			CEffectMgr::m_pInstance = nullptr;



CEffectMgr::CEffectMgr()
{

}


CEffectMgr::~CEffectMgr()
{
	Release();
}

void CEffectMgr::Initialize(void)
{
	Initialize_Circle();
	Initialize_Ellipse();
	Initialize_Exhaust();
	Initialize_Smoke();
	Initialize_Text();
	Initialize_SlideSmoke();
	Initialize_MinusHp();
	Initialize_Bubble();
	Initialize_Basehit();

	m_vecRenderList.resize(5,list<CSprite*>());

	m_pMarker = new CSprite_Marker;
	m_pMarker->Initialize(nullptr);
}

void CEffectMgr::Update(void)
{
	for (auto& Veciter : m_vecRenderList)
	{
		for (auto& Listiter : Veciter)
		{
			Listiter->Update();
		}
	}

	if (m_bMarker)
		m_pMarker->Update();
}

void CEffectMgr::LateUpdate(void)
{
	for (auto& Veciter : m_vecRenderList)
	{
		for (auto& Listiter = Veciter.begin(); Listiter != Veciter.end();)
		{
			if ((*Listiter)->Get_SpriteState() == SPRITE_STATE::START)
			{
				(*Listiter)->LateUpdate();
				++Listiter;
			}
			else if ((*Listiter)->Get_SpriteState() == SPRITE_STATE::END)
			{
				Listiter = Veciter.erase(Listiter);
			}
		}
	}
	if (m_bMarker)
		m_pMarker->LateUpdate();

}

void CEffectMgr::Release(void)
{
	for (auto& Mapiter : m_mapEffectList)
	{
		for (auto& Listiter : *(Mapiter.second))
		{
			Safe_Delete(Listiter);
		}
		Mapiter.second->clear();
	}
	m_mapEffectList.clear();

	Safe_Delete(m_pMarker);
}

void CEffectMgr::Render(HDC _hDC)
{
	for (auto& Veciter : m_vecRenderList)
	{
		for (auto& Listiter : Veciter)
		{
			Listiter->Render(_hDC);
		}
	}

	if (m_bMarker)
		m_pMarker->Render(_hDC);
}


void CEffectMgr::Get_Circle(CIRCLE_EFFECT_TYPE _CircleType, CMyVector2 _vPos)
{
	static_cast<CSprite_Effect_Circle*>(*m_Circleiter)->Set_Circle(_CircleType, _vPos);
	m_vecRenderList[1].push_back(*m_Circleiter);

	
	++m_Circleiter;

	if (m_Circleiter == m_CircleList.end())
		m_Circleiter = m_CircleList.begin();
}

void CEffectMgr::Get_Ellipse(ELLIPSE_EFFECT_TYPE _EllipseType, CMyVector2 _vPos)
{
	static_cast<CSprite_Effect_Ellipse*>(*m_Ellipseiter)->Set_Ellipse(_EllipseType, _vPos);
	m_vecRenderList[2].push_back(*m_Ellipseiter);


	++m_Ellipseiter;

	if (m_Ellipseiter == m_EllipseList.end())
		m_Ellipseiter = m_EllipseList.begin();
}

void CEffectMgr::Get_Exhaust(EXHAUST_EFFECT_TYPE _ExhaustType, CMyVector2 _vPos)
{
	static_cast<CSprite_Effect_Exhaust*>(*m_Exhaustiter)->Set_Exhaust(_ExhaustType, _vPos);
	m_vecRenderList[0].push_back(*m_Exhaustiter);


	++m_Exhaustiter;

	if (m_Exhaustiter == m_ExhaustList.end())
		m_Exhaustiter = m_ExhaustList.begin();
}

void CEffectMgr::Get_Smoke(SMOKE_EFFECT_TYPE _SmokeType, CMyVector2 _vPos)
{
	static_cast<CSprite_Effect_Smoke*>(*m_Smokeiter)->Set_Smoke(_SmokeType, _vPos);
	m_vecRenderList[0].push_back(*m_Smokeiter);


	++m_Smokeiter;

	if (m_Smokeiter == m_SmokeList.end())
		m_Smokeiter = m_SmokeList.begin();
}

void CEffectMgr::Get_Random_Text(CMyVector2 _vPos)
{
	static_cast<CSprite_Effect_Text*>(*m_Textiter)->Random_Text(_vPos);
	m_vecRenderList[4].push_back(*m_Textiter);


	++m_Textiter;

	if (m_Textiter == m_TextList.end())
		m_Textiter = m_TextList.begin();
}

void CEffectMgr::Get_SlideSmoke(CMyVector2 _vPos)
{
	static_cast<CSprite_SlideSmoke*>(*m_SlideSmokeiter)->Set_Smoke(_vPos);
	m_vecRenderList[0].push_back(*m_SlideSmokeiter);


	++m_SlideSmokeiter;

	if (m_SlideSmokeiter == m_SlideSmokeList.end())
		m_SlideSmokeiter = m_SlideSmokeList.begin();
}

void CEffectMgr::Get_MinusHp(CMyVector2 _vPos, int _iNum, int _iTeamNum)
{
	static_cast<CSprite_MinusHp*>(*m_MinusHpiter)->Reset_MinusHp(_vPos, _iNum, _iTeamNum);
	m_vecRenderList[0].push_back(*m_MinusHpiter);


	++m_MinusHpiter;

	if (m_MinusHpiter == m_MinusHpList.end())
		m_MinusHpiter = m_MinusHpList.begin();
}

void CEffectMgr::Get_RandomBubble(CMyVector2 _vPos)
{
	static_cast<CSprite_Bubble*>(*m_Bubbleiter)->Random_Bubble(_vPos);
	m_vecRenderList[0].push_back(*m_Bubbleiter);


	++m_Bubbleiter;

	if (m_Bubbleiter == m_BubbleList.end())
		m_Bubbleiter = m_BubbleList.begin();
}

void CEffectMgr::Get_Basehit(CMyVector2 _vPos)
{
	static_cast<CSprite_Basehit*>(*m_Basehititer)->Set_Basehit(_vPos);
	m_vecRenderList[0].push_back(*m_Basehititer);


	++m_Basehititer;

	if (m_Basehititer == m_BasehitList.end())
		m_Basehititer = m_BasehitList.begin();
}

void CEffectMgr::Get_Marker(CMyVector2 _vPos)
{
	static_cast<CSprite_Marker*>(m_pMarker)->Set_Marker(_vPos);
	m_bMarker = true;
}



void CEffectMgr::Initialize_Circle(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Effect/Circle25.bmp", L"Circle25");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Effect/Circle50.bmp", L"Circle50");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Effect/Circle75.bmp", L"Circle75");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Effect/Circle100.bmp", L"Circle100");

	CSprite*		pNewCircle = nullptr;

	for (int i = 0; 50 > i; ++i)
	{
		pNewCircle = new CSprite_Effect_Circle;
		pNewCircle->Initialize(nullptr);
		m_CircleList.push_back(pNewCircle);
		pNewCircle = nullptr;
	}

	m_Circleiter = m_CircleList.begin();

	m_mapEffectList.emplace(L"Circle", &m_CircleList);
}



void CEffectMgr::Initialize_Ellipse(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Effect/Ellipse25.bmp", L"Ellipse25");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Effect/Ellipse50.bmp", L"Ellipse50");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Effect/Ellipse75.bmp", L"Ellipse75");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Effect/Ellipse100.bmp", L"Ellipse100");


	CSprite*		pNewEllipse = nullptr;

	for (int i = 0; 50 > i; ++i)
	{
		pNewEllipse = new CSprite_Effect_Ellipse;
		pNewEllipse->Initialize(nullptr);
		m_EllipseList.push_back(pNewEllipse);
		pNewEllipse = nullptr;
	}

	m_Ellipseiter = m_EllipseList.begin();

	m_mapEffectList.emplace(L"Ellipse", &m_EllipseList);
}

void CEffectMgr::Initialize_Exhaust(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Effect/DarkExhaust.bmp", L"DarkExhaust");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Effect/WhiteExhaust.bmp", L"WhiteExhaust");



	CSprite*		pNewExhaust = nullptr;

	for (int i = 0; 300 > i; ++i)
	{
		pNewExhaust = new CSprite_Effect_Exhaust;
		pNewExhaust->Initialize(nullptr);
		m_ExhaustList.push_back(pNewExhaust);
		pNewExhaust = nullptr;
	}

	m_Exhaustiter = m_ExhaustList.begin();

	m_mapEffectList.emplace(L"Exhaust", &m_ExhaustList);
}

void CEffectMgr::Initialize_Smoke(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Effect/DarkSmoke20.bmp", L"DarkSmoke20");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Effect/DarkSmoke30.bmp", L"DarkSmoke30");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Effect/DarkSmoke40.bmp", L"DarkSmoke40");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Effect/WhiteSmoke25.bmp", L"WhiteSmoke25");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Effect/WhiteSmoke50.bmp", L"WhiteSmoke50");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Effect/WhiteSmoke75.bmp", L"WhiteSmoke75");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Effect/WhiteSmoke100.bmp", L"WhiteSmoke100");


	CSprite*		pNewSmoke = nullptr;

	for (int i = 0; 200 > i; ++i)
	{
		pNewSmoke = new CSprite_Effect_Smoke;
		pNewSmoke->Initialize(nullptr);
		m_SmokeList.push_back(pNewSmoke);
		pNewSmoke = nullptr;
	}

	m_Smokeiter = m_SmokeList.begin();

	m_mapEffectList.emplace(L"Smoke", &m_SmokeList);

}

void CEffectMgr::Initialize_Text(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Effect/TextBiff.bmp", L"TextBiff");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Effect/TextPoot.bmp", L"TextPoot");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Effect/TextPow.bmp", L"TextPow");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Effect/TextFoom.bmp", L"TextFoom");
	
	

	CSprite*		pNewText = nullptr;

	for (int i = 0; 20 > i; ++i)
	{
		pNewText = new CSprite_Effect_Text;
		pNewText->Initialize(nullptr);
		m_TextList.push_back(pNewText);
		pNewText = nullptr;
	}


	m_Textiter = m_TextList.begin();

	m_mapEffectList.emplace(L"Text", &m_TextList);
}

void CEffectMgr::Initialize_SlideSmoke(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Worm/SlideSmoke.bmp", L"SlideSmoke");


	CSprite*		pNewSmoke = nullptr;

	for (int i = 0; 100 > i; ++i)
	{
		pNewSmoke = new CSprite_SlideSmoke;
		pNewSmoke->Initialize(nullptr);
		m_SlideSmokeList.push_back(pNewSmoke);
		pNewSmoke = nullptr;
	}

	m_SlideSmokeiter = m_SlideSmokeList.begin();

	m_mapEffectList.emplace(L"SlideSmoke", &m_SlideSmokeList);
}

void CEffectMgr::Initialize_MinusHp(void)
{
	CSprite*		pNewMinusHp = nullptr;

	for (int i = 0; 20 > i; ++i)
	{
		pNewMinusHp = new CSprite_MinusHp;
		pNewMinusHp->Initialize(nullptr);
		m_MinusHpList.push_back(pNewMinusHp);
		pNewMinusHp = nullptr;
	}

	m_MinusHpiter = m_MinusHpList.begin();

	m_mapEffectList.emplace(L"MinusHp", &m_MinusHpList);
}

void CEffectMgr::Initialize_Bubble(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Effect/Bubble/Bubble1.bmp", L"Bubble1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Effect/Bubble/Bubble2.bmp", L"Bubble2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Effect/Bubble/Bubble3.bmp", L"Bubble3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Effect/Bubble/Bubble4.bmp", L"Bubble4");

	
	CSprite*		pBubble = nullptr;

	for (int i = 0; 50 > i; ++i)
	{
		pBubble = new CSprite_Bubble;
		pBubble->Initialize(nullptr);
		m_BubbleList.push_back(pBubble);
		pBubble = nullptr;
	}

	m_Bubbleiter = m_BubbleList.begin();

	m_mapEffectList.emplace(L"Bubble", &m_BubbleList);
}

void CEffectMgr::Initialize_Basehit(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Image/Weapon/Effect/Basehit.bmp", L"Basehit");


	CSprite*		pBase = nullptr;

	for (int i = 0; 20 > i; ++i)
	{
		pBase = new CSprite_Basehit;
		pBase->Initialize(nullptr);
		m_BasehitList.push_back(pBase);
		pBase = nullptr;
	}

	m_Basehititer = m_BasehitList.begin();

	m_mapEffectList.emplace(L"Basehit", &m_BasehitList);
}


