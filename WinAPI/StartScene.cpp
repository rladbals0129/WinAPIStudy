#include "stdafx.h"
#include "StartScene.h"


HRESULT StartScene::init(void)
{
	IMAGEMANAGER->addImage("시작화면", "Resources/Images/BackGround/StartBg.bmp",
		WINSIZE_X, WINSIZE_Y);
	
	wsprintf(_text, "StartScene");
	return S_OK;
}

void StartScene::release(void)
{
	
}

void StartScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		SCENEMANAGER->changeScene("슈팅");
	}
}

void StartScene::render()
{
	IMAGEMANAGER->render("시작화면", getMemDC());
	TextOut(getMemDC(), WINSIZE_X / 2, WINSIZE_Y / 2, _text, strlen(_text));

	/*IMAGEMANAGER->alphaRender("시작화면", getMemDC(), 0, 0, _bgAlpha);
	
	if (_bgAlpha >= 160)
	{
		IMAGEMANAGER->alphaRender("텍스트 알파", getMemDC(), 130, WINSIZE_Y / 2 + 200, _alpha);
	}*/
}

StartScene::StartScene()
{
}


StartScene::~StartScene()
{
}
