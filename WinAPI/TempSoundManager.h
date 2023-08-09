#pragma once
#include "SingletonBase.h"
//������ ���� ���̺귯��(���)
// �ð� / v���� ->PlaySound()
#include <mmsystem.h>
#include <mciapi.h>//��ġ�����ڿ� �����ϱ� ���� �������
// mciSendString() �̶�� �Լ��� ����ϱ� ���� �߰��� �ߴ�.

#pragma comment(lib, "Winmm.lib")

class TempSoundManager : public SingletonBase <TempSoundManager>
{
public:

	HRESULT init(void);

	//MP3
	void addMp3FileWithKey(string key, string fileName);
	//WAV
	void addWaveFileWithKey(string key, string fileName);
	//ȿ����
	void playEffectSoundWave(char* fileName);
	//MP3���
	void playSoundWithKey(string key);
	//����
	void stopMp3WithKey(string key);


	TempSoundManager();
	~TempSoundManager();
};

