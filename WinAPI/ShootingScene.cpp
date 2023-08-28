#include "stdafx.h"
#include "ShootingScene.h"


HRESULT ShootingScene::init(void)
{
	IMAGEMANAGER->addImage("����", "Resources/Images/BackGround/bgIce.bmp",
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
		if (MessageBox(_hWnd, "������ �����Ͻðڽ��ϱ�?", "���� Ȯ��", MB_OKCANCEL) == IDOK)
		{
			PostQuitMessage(0);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		SCENEMANAGER->changeScene("����");
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
	//IMAGEMANAGER->loopRender("��� ����", getMemDC(),
	//	&RectMake(0, 0, WINSIZE_X, WINSIZE_Y),
	//	_bgSpeed, 0);

	RECT rc = { 0,0, WINSIZE_X,WINSIZE_Y };
	IMAGEMANAGER->findImage("����")->loopRender(getMemDC(), &rc, _x, _y);


	SetBkMode(getMemDC(), TRANSPARENT); // dc�� �׸��� �ؽ�Ʈ���۸� �����ϰ� ���ִ� �Լ�.


	_rocket->render();
	_em->render();

	TextOut(getMemDC(), WINSIZE_X / 2, WINSIZE_Y / 2, _text, strlen(_text));

	
}
