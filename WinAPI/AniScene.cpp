#include "stdafx.h"
#include "AniScene.h"

HRESULT AniScene::init(void)
{
	_image = IMAGEMANAGER->addImage("코끼리", "Resources/Images/Object/Elephant.bmp",
		660, 268, true, RGB(255, 0, 255)); 

	_animA = new Animation;//한프레임 사이즈 꼭 확인하기 gdi에선 확인하는게 좋다
	_animA->init(_image->getWidth(),_image->getHeight(),110,67);//한프레임 너비높이
	_animA->setDefPlayFrame(false, true);
	_animA->setFPS(12);
	return S_OK;
}

void AniScene::release(void)
{
	_animA->release();
	SAFE_DELETE(_animA);
}

void AniScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		_animA->AniStart();
	}

	_animA->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
}

void AniScene::render()
{

	_image->aniRender(getMemDC(), WINSIZE_X / 2 - 50, WINSIZE_Y / 2, _animA);

}
