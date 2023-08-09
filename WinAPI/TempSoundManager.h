#pragma once
#include "SingletonBase.h"
//윈도우 내장 라이브러리(재생)
// 시간 / v사운드 ->PlaySound()
#include <mmsystem.h>
#include <mciapi.h>//장치관리자에 접근하기 위한 헤더파일
// mciSendString() 이라는 함수를 사용하기 위해 추가를 했다.

#pragma comment(lib, "Winmm.lib")

class TempSoundManager : public SingletonBase <TempSoundManager>
{
public:

	HRESULT init(void);

	//MP3
	void addMp3FileWithKey(string key, string fileName);
	//WAV
	void addWaveFileWithKey(string key, string fileName);
	//효과음
	void playEffectSoundWave(char* fileName);
	//MP3재생
	void playSoundWithKey(string key);
	//정지
	void stopMp3WithKey(string key);


	TempSoundManager();
	~TempSoundManager();
};

