#pragma once
#include <list>
#include "Sprite.h"

class CEffectMgr
{
private:
	CEffectMgr();
	~CEffectMgr();

public:
	static CEffectMgr*		Get_Inst(void)
	{
		if (!m_pInstance)
			m_pInstance = new CEffectMgr;

		return m_pInstance;
	}
	static void		Destroy_Inst(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}

	}

public:
	void								Initialize(void);
	void								Update(void);
	void								LateUpdate(void);
	void								Release(void);

	void								Render(HDC _hDC);


	void										Get_Circle(CIRCLE_EFFECT_TYPE _CircleType, CMyVector2 _vPos);
	void										Get_Ellipse(ELLIPSE_EFFECT_TYPE _EllipseType, CMyVector2 _vPos);
	void										Get_Exhaust(EXHAUST_EFFECT_TYPE _ExhaustType, CMyVector2 _vPos);
	void										Get_Smoke(SMOKE_EFFECT_TYPE _SmokeType, CMyVector2 _vPos);
	void										Get_Random_Text(CMyVector2 _vPos);
	void										Get_SlideSmoke(CMyVector2 _vPos);
	void										Get_MinusHp(CMyVector2 _vPos,int _iNum, int _iTeamNum);
	void										Get_RandomBubble(CMyVector2 _vPos);
	void										Get_Basehit(CMyVector2 _vPos);

	void										Get_Marker(CMyVector2 _vPos);
	void										Delete_Marker(void) { m_bMarker = false; }
private:
	static CEffectMgr*							m_pInstance;

	vector<list<CSprite*>>						m_vecRenderList;
	map<const TCHAR*, list<CSprite*>*>			m_mapEffectList;
	

	//원이펙트
	list<CSprite*>								m_CircleList;
	list<CSprite*>::iterator					m_Circleiter;
	void										Initialize_Circle(void);

	//타원 이펙트
	list<CSprite*>								m_EllipseList;
	list<CSprite*>::iterator					m_Ellipseiter;
	void										Initialize_Ellipse(void);

	//배기 가스
	list<CSprite*>								m_ExhaustList;
	list<CSprite*>::iterator					m_Exhaustiter;
	void										Initialize_Exhaust(void);

	//스모크
	list<CSprite*>								m_SmokeList;
	list<CSprite*>::iterator					m_Smokeiter;
	void										Initialize_Smoke(void);

	//텍스트
	list<CSprite*>								m_TextList;
	list<CSprite*>::iterator					m_Textiter;
	void										Initialize_Text(void);

	//슬라이딩 스모크
	list<CSprite*>								m_SlideSmokeList;
	list<CSprite*>::iterator					m_SlideSmokeiter;
	void										Initialize_SlideSmoke(void);

	//Hp이펙트
	list<CSprite*>								m_MinusHpList;
	list<CSprite*>::iterator					m_MinusHpiter;
	void										Initialize_MinusHp(void);

	//버블
	list<CSprite*>								m_BubbleList;
	list<CSprite*>::iterator					m_Bubbleiter;
	void										Initialize_Bubble(void);

	//베이스힛
	list<CSprite*>								m_BasehitList;
	list<CSprite*>::iterator					m_Basehititer;
	void										Initialize_Basehit(void);

	
	//마커
	CSprite*									m_pMarker;
	bool										m_bMarker;
};

