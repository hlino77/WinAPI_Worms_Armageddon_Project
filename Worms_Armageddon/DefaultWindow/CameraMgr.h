#pragma once
#include "Enum.h"
#include "MyVector2.h"
#include "Obj.h"

class CCameraMgr
{
private:
	CCameraMgr();
	~CCameraMgr();

public:
	static CCameraMgr*		Get_Inst(void)
	{
		if (!m_pInstance)
			m_pInstance = new CCameraMgr;

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

	void			Update(void);
	void			LateUpdate(void);
	void			Initialize(void);

	float			Get_ScrollX(void) { return m_fScrollX; }
	float			Get_ScrollY(void) { return m_fScrollY; }
	POINT*			Get_Mouse(void) { return &m_Mouse; }

	CMyVector2&		Get_CameraPos(void) { return m_vCameraPos; }
	RECT&			Get_CameraRect(void) { return m_tCameraRect; }

	bool			Is_Mouse(void) { return m_bMouse; }

	void			Go_Target(CObj* _pObj);
	void			Go_Target(CMyVector2 _vPos);
	void			Follow_Target(CObj* _pObj);

	void			ShowMouse(void);
	void			PutMouse(void);

	void			Camera_Shake(void);
private:
	static CCameraMgr*							m_pInstance;

	float					m_fScrollX;
	float					m_fScrollY;

	CAMERA_STATE			m_CameraState;

	void					Key_Input(void);
	void					MapOut(void);


	CMyVector2				m_vCameraPos;
	RECT					m_tCameraRect;

	void					Set_CameraPos(void);

	POINT					m_Mouse;
	void					Set_Mouse(void);
	void					Mouse_Scroll(void);
	bool					m_bMouseScroll;
	bool					m_bMouse;

	HWND					m_hWindow;
	RECT					m_ClientRect;
	POINT					m_Center;

	void					Set_CenterPoint(void);

	CObj*					m_pTarget;
	CMyVector2*				m_pTargetPos;
	CMyVector2				m_vGoTargetPos;

	bool					m_bGoTarget;
	bool					m_bStopY;
	bool					m_bStopX;


	void					FollowTargetUpdate(void);
	void					GoTargetUpdate(void);

	void					FollowTargetLateUpdate(void);
	void					GoTargetLateUpdate(void);


	void					MouseUpdate(void);
	void					Show_Cursor(void);

	DWORD					m_iShakeDelay;
	DWORD					m_iShakeStart;

	float					m_fPrevScrollX;
	float					m_fPrevScrollY;

	void					ShakeUpdate(void);
	void					ShakeLateUpdate(void);



};


