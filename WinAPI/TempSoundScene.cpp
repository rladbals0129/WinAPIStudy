#include "stdafx.h"
#include "TempSoundScene.h"


HRESULT TempSoundScene::init(void)
{
	TEMPSOUNDMANAGER->addMp3FileWithKey("�뷡", "Resources/Sound/Second Run.mp3");

	return S_OK;
}

void TempSoundScene::update(void)
{

	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		TEMPSOUNDMANAGER->playSoundWithKey("�뷡");
	}

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		TEMPSOUNDMANAGER->playEffectSoundWave("Resources/Sound/track_sum_14.wav");
	}
}

TempSoundScene::TempSoundScene()
{
}


TempSoundScene::~TempSoundScene()
{
}
