#include "stdafx.h"
#include "SoundManager.h"

SoundManager::SoundManager() : _system(nullptr),
							   _channel(nullptr),			//싱글톤객체기때문에 생성자에서 호출해야함.
							   _sound(nullptr)
{
}

HRESULT SoundManager::init(void)
{
	System_Create(&_system);

	//  FMOD_RESULT F_API init       
	//             (int maxchannels, FMOD_INITFLAGS flags, void *extradriverdata);
	//														음원 음질을 조절 가능
	//															ㄴ 이걸이용해 보스5분음원 처음30초웅장 나머지4분30초 메모리줄임

	_system->init(totalSoundChannel, FMOD_INIT_NORMAL, 0);

	//채널 수 만큼 메모리 버퍼 및 사운드 생성 -> 채널수와 사운드수는 서로 맞춰주는 것이 좋다.
	// ㄴ 1 : 1 매칭

	_sound = new Sound*[totalSoundChannel];
	_channel = new Channel*[totalSoundChannel];

	//메모리 한번 싹 밀어줌
	//ZeroMemory를 안쓰는 이유는 유사시에 0을 다른 수로 바꿔주기 위해서. 
	memset(_sound, 0, sizeof(Sound*) * (totalSoundChannel));
	memset(_channel, 0, sizeof(Channel*) * (totalSoundChannel));

	return S_OK;
}

void SoundManager::release(void)
{
	if (_channel != nullptr || _sound != nullptr)
	{
		for (int i = 0; i < totalSoundChannel; i++)
		{
			if (_channel != nullptr)
			{
				if (_channel[i]) _channel[i]->stop();
			}
			if (_sound != nullptr)
			{	//채널을 추가하려면 여기에 코드가 추가되어야함(반복문 채널갯수). 2.0이기에 안씀
				if (_sound[i]) _sound[i]->release();
			}
		}
	}

	SAFE_DELETE_ARRAY(_channel);
	SAFE_DELETE_ARRAY(_sound);

	if (_system != nullptr)
	{
		_system->release();  //이게 어떻게 돌아가는지 알아야 프로그래머다
		_system->close();		//물경력 엔진쓰는 멍청이가 되지말자 
	}
}

void SoundManager::update(void)
{
	//_system->update() : 볼륨변경 , 재생이 끝난 사운드를 채널에서 빼는 등 다양한 작업을 "자동"으로 해준다.
	_system->update();
}

void SoundManager::addSound(string keyName, string soundName, bool background, bool loop)
{
	if (loop)
	{
		if (background)
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
		//효과음
		else
		{
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);

			/*
			crateStream	 vs createSound
			ㄴ 인자도 동일 -> 내부에 메모리를 계속 유지하느냐 아니냐의 차이가 존재한다.

			매개변수
			1. 파일이름 2. 사운드를 열기 위한 FMOD 옵션 
			3. 사운드에 대한 정보값을 개발자에게 전달해줄것인지? 아닌지? (0 -> 무시)
			4. 사운드 오브젝트 변수의 주소
			*/
		}
	}
	else
	{
		// FMOD_DEFAULT : Once
		_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
	}

	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));


}

void SoundManager::play(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]); 
			_channel[count]->setVolume(volume); //사운드는 비선형이기때문에 _sound[count]는 안댐
			break;
		}
		
	}

}

void SoundManager::stop(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			
			_channel[count]->stop();
			break;
		}

	}
}

void SoundManager::pause(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{

			_channel[count]->setPaused(true);
			break;
		}

	}
}

void SoundManager::resume(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{

			_channel[count]->setPaused(false);
			break;
		}

	}
}

bool SoundManager::isPlaySound(string keyName)
{


	arrSoundsIter iter = _mTotalSounds.begin();


	bool isPlay;
	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isPlay);
			break;
		}

	}
	return isPlay;
}

bool SoundManager::isPauseSound(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();


	bool isPause;
	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isPause);
			break;
		}

	}
	return isPause;
}

