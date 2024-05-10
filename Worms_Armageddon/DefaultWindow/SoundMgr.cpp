#include "stdafx.h"
#include "SoundMgr.h"
#include <algorithm>
#include "TimeMgr.h"


CSoundMgr* CSoundMgr::m_pInstance = nullptr;
CSoundMgr::CSoundMgr()
{
	m_pSystem = nullptr;
}


CSoundMgr::~CSoundMgr()
{
	Release();
}

void CSoundMgr::Initialize()
{
	// ���带 ����ϴ� ��ǥ��ü�� �����ϴ� �Լ�
	FMOD_System_Create(&m_pSystem);

	// 1. �ý��� ������, 2. ����� ����ä�� �� , �ʱ�ȭ ���) 
	FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);

	LoadSoundFile();

}
void CSoundMgr::Release()
{
	for (auto& Mypair : m_mapSound)
	{
		delete[] Mypair.first;
		FMOD_Sound_Release(Mypair.second);
	}
	m_mapSound.clear();

	FMOD_System_Release(m_pSystem);
	FMOD_System_Close(m_pSystem);
}




void CSoundMgr::PlaySound(TCHAR * pSoundKey, CHANNELID eID, float fVolume)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	// iter = find_if(m_mapSound.begin(), m_mapSound.end(), CTag_Finder(pSoundKey));
	iter = find_if(m_mapSound.begin(), m_mapSound.end(),
		[&](auto& iter)->bool
	{
		return !lstrcmp(pSoundKey, iter.first);
	});

	if (iter == m_mapSound.end())
		return;

	FMOD_BOOL bPlay = FALSE;

	if (FMOD_Channel_IsPlaying(m_pChannelArr[eID], &bPlay))
	{
		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[eID]);
	}

	FMOD_Channel_SetVolume(m_pChannelArr[eID], fVolume);

	FMOD_System_Update(m_pSystem);
}

void CSoundMgr::PlayBGM(TCHAR * pSoundKey, float fVolume)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	// iter = find_if(m_mapSound.begin(), m_mapSound.end(), CTag_Finder(pSoundKey));
	iter = find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& iter)->bool
	{
		return !lstrcmp(pSoundKey, iter.first);
	});

	if (iter == m_mapSound.end())
		return;

	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[SOUND_BGM]);
	FMOD_Channel_SetMode(m_pChannelArr[SOUND_BGM], FMOD_LOOP_NORMAL);
	FMOD_Channel_SetVolume(m_pChannelArr[SOUND_BGM], fVolume);
	FMOD_System_Update(m_pSystem);
}

void CSoundMgr::StopSound(CHANNELID eID)
{
	FMOD_Channel_Stop(m_pChannelArr[eID]);
}

void CSoundMgr::StopAll()
{
	for (int i = 0; i < MAXCHANNEL; ++i)
		FMOD_Channel_Stop(m_pChannelArr[i]);
}

void CSoundMgr::SetChannelVolume(CHANNELID eID, float fVolume)
{
	FMOD_Channel_SetVolume(m_pChannelArr[eID], fVolume);

	FMOD_System_Update(m_pSystem);
}

void CSoundMgr::Random_BombSound(void)
{
	int iTemp = rand() % 3;
	int iChannel = rand() % 5;

	CHANNELID ChannelID;

	switch (iChannel)
	{
	case 0:
		ChannelID = CHANNELID::BOMBSOUND1;
		break;
	case 1:
		ChannelID = CHANNELID::BOMBSOUND2;
		break;
	case 2:
		ChannelID = CHANNELID::BOMBSOUND3;
		break;
	case 3:
		ChannelID = CHANNELID::BOMBSOUND4;
		break;
	case 4:
		ChannelID = CHANNELID::BOMBSOUND5;
		break;
	}

	switch (iTemp)
	{
	case 0:
		StopSound(ChannelID);
		PlaySound(L"Explosion1.wav", ChannelID, g_fVolume);
		break;
	case 1:
		StopSound(ChannelID);
		PlaySound(L"Explosion2.wav", ChannelID, g_fVolume);
		break;
	case 2:
		StopSound(ChannelID);
		PlaySound(L"Explosion3.WAV", ChannelID, g_fVolume);
		break;
	}
}

void CSoundMgr::Random_WormHit(void)
{
	int iTemp = rand() % 6;
	int iChannel = rand() % 4;

	CHANNELID ChannelID;

	switch (iChannel)
	{
	case 0:
		ChannelID = CHANNELID::WORMSOUND1;
		break;
	case 1:
		ChannelID = CHANNELID::WORMSOUND2;
		break;
	case 2:
		ChannelID = CHANNELID::WORMSOUND3;
		break;
	case 3:
		ChannelID = CHANNELID::WORMSOUND4;
		break;
	}

	switch (iTemp)
	{
	case 0:
		PlaySound(L"OOFF1.WAV", ChannelID, g_fVolume);
		break;
	case 1:
		PlaySound(L"OOFF2.WAV", ChannelID, g_fVolume);
		break;
	case 2:
		PlaySound(L"OOFF3.WAV", ChannelID, g_fVolume);
		break;
	case 3:
		PlaySound(L"OW1.WAV", ChannelID, g_fVolume);
		break;
	case 4:
		PlaySound(L"OW2.WAV", ChannelID, g_fVolume);
		break;
	case 5:
		PlaySound(L"OW3.WAV", ChannelID, g_fVolume);
		break;
	}
}

void CSoundMgr::Random_WormOOFF(void)
{
	int iTemp = rand() % 5;

	switch (iTemp)
	{
	case 0:
		PlaySound(L"OOFF1.WAV", CHANNELID::WORMSOUND, g_fVolume);
		break;
	case 1:
		PlaySound(L"OOFF2.WAV", CHANNELID::WORMSOUND, g_fVolume);
		break;
	case 2:
		PlaySound(L"OOFF3.WAV", CHANNELID::WORMSOUND, g_fVolume);
		break;
	}
}


void CSoundMgr::Random_WormDie(void)
{
	int iTemp = rand() % 2;

	switch (iTemp)
	{
	case 0:
		StopSound(CHANNELID::WORMSOUND);
		PlaySound(L"OHDEAR.WAV", CHANNELID::WORMSOUND, g_fVolume);
		break;
	case 1:
		StopSound(CHANNELID::WORMSOUND);
		PlaySound(L"BYEBYE.WAV", CHANNELID::WORMSOUND, g_fVolume);
		break;
	}
}


void CSoundMgr::LoadSoundFile()
{
	// _finddata_t : <io.h>���� �����ϸ� ���� ������ �����ϴ� ����ü
	_finddata_t fd;

	// _findfirst : <io.h>���� �����ϸ� ����ڰ� ������ ��� ������ ���� ù ��° ������ ã�� �Լ�
	long handle = _findfirst("../Sound/*.*", &fd);

	if (handle == -1)
		return;

	int iResult = 0;

	char szCurPath[128] = "../Sound/";
	char szFullPath[128] = "";

	while (iResult != -1)
	{
		strcpy_s(szFullPath, szCurPath);

		// "../ Sound/Success.wav"
		strcat_s(szFullPath, fd.name);

		FMOD_SOUND* pSound = nullptr;

		FMOD_RESULT eRes = FMOD_System_CreateSound(m_pSystem, szFullPath, FMOD_HARDWARE, 0, &pSound);

		if (eRes == FMOD_OK)
		{
			int iLength = strlen(fd.name) + 1;

			TCHAR* pSoundKey = new TCHAR[iLength];
			ZeroMemory(pSoundKey, sizeof(TCHAR) * iLength);

			// �ƽ�Ű �ڵ� ���ڿ��� �����ڵ� ���ڿ��� ��ȯ�����ִ� �Լ�
			MultiByteToWideChar(CP_ACP, 0, fd.name, iLength, pSoundKey, iLength);

			m_mapSound.emplace(pSoundKey, pSound);
		}
		//_findnext : <io.h>���� �����ϸ� ���� ��ġ�� ������ ã�� �Լ�, ���̻� ���ٸ� -1�� ����
		iResult = _findnext(handle, &fd);
	}

	FMOD_System_Update(m_pSystem);

	_findclose(handle);
}
