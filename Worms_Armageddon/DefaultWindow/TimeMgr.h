#pragma once
class CTimeMgr
{
private:
	CTimeMgr();
	~CTimeMgr();

public:
	static CTimeMgr*		Get_Inst(void)
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CTimeMgr;
		}
		return m_pInstance;
	}

	static void					Destroy_Inst(void)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}

	void						Initialize(void);
	void						Update(void);
	void						Release(void);
	float						Get_DeltaTime(void) { return m_DeltaTime * 0.001f; }
	float						Get_Time(void) { return m_Time * 0.001f; }



private:
	DWORD						m_prevTime;
	DWORD						m_DeltaTime;
	static CTimeMgr*			m_pInstance;
	DWORD						m_Time;
};

