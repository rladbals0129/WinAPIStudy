#include "stdafx.h"
#include "ShootingScene.h"


HRESULT ShootingScene::init(void)
{
	IMAGEMANAGER->addImage("전장", "Resources/Images/BackGround/bgIce.bmp",
		WINSIZE_X, WINSIZE_Y);

	_offsetX = _offsetY = 0;
	_bgSpeed = 0;

	

	_rocket = new Rocket;
	_rocket->init();
	_em = new EnemyManager;
	_em->init();

	_em->setRocketMemoryAddress(_rocket);
	_rocket->setEnemyManagerMemoryAddress(_em);

	_x = _y = 0.f;

	wsprintf(_text, "ShootingScene");

	return S_OK;
}

void ShootingScene::release(void)
{
	

	_rocket->release();
	_em->release();
	
	SAFE_DELETE(_rocket);
	SAFE_DELETE(_em);


}

void ShootingScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (MessageBox(_hWnd, "게임을 종료하시겠습니까?", "종료 확인", MB_OKCANCEL) == IDOK)
		{
			PostQuitMessage(0);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		SCENEMANAGER->changeScene("시작");
	}
	_rocket->update();
	_em->update();
	
	collision();
	_y -= 2;
	
	//_bgSpeed += 3;
	cout << _bgSpeed << endl;
}

void ShootingScene::render()
{
	//IMAGEMANAGER->loopRender("배경 루프", getMemDC(),
	//	&RectMake(0, 0, WINSIZE_X, WINSIZE_Y),
	//	_bgSpeed, 0);

	RECT rc = { 0,0, WINSIZE_X,WINSIZE_Y };
	IMAGEMANAGER->findImage("전장")->loopRender(getMemDC(), &rc, _x, _y);


	SetBkMode(getMemDC(), TRANSPARENT); // dc를 그릴때 텍스트버퍼를 투명하게 해주는 함수.


	_rocket->render();
	_em->render();

	TextOut(getMemDC(), WINSIZE_X / 2, WINSIZE_Y / 2, _text, strlen(_text));

	
}
