#pragma once
#include <vector>
#include "Scene.h"
#include "Enum.h"

	class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();

public:
	static CSceneMgr*		Get_Inst(void)
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CSceneMgr;
		}
		return m_pInstance;
	}

	static void					Destroy_Inst(void)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}

	void		Initialize(void);
	void		Update(void);
	void		LateUpdate(void);
	void		Release(void);
	void		Render(HDC _hDC);

	void			Change_Scene(void);
	void			Set_Next_Scene(SCENE_TYPE _SceneType);
	CScene*			Make_Scene(SCENE_TYPE _SceneType);

	void			Set_Intro(bool _bIntro) { m_bIntro = _bIntro; }
	bool			Is_Intro(void) { return m_bIntro; }

	void			Set_GameEnd(void) { m_bEnd = true; }
	bool			Is_End(void) { return m_bEnd; }
private:
	vector<CScene*>			m_vecScene_List;
	CScene*					m_pCurrScene;
	CScene*					m_pPrevScene;

	SCENE_TYPE				m_NextScene;
	bool					m_bChange;

	static CSceneMgr*		m_pInstance;


	bool					m_bIntro;

	bool					m_bEnd;
};

