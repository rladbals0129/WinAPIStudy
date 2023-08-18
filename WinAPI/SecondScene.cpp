#include "stdafx.h"
#include "SecondScene.h"


HRESULT SecondScene::init(void)
{
	IMAGEMANAGER->addImage("슈팅맵", "Resources/Images/BackGround/ShootingBG.bmp",
		WINSIZE_X, WINSIZE_Y);

	_offsetX = _offsetY = 0;
	_bgSpeed = 0;

	_temp = new TempSoundScene;

	_rocket = new Rocket;
	_rocket->init();
	_em = new EnemyManager;
	_em->init();
	//std::shared_ptr<Rocket> PlayerA = std::make_shared<Rocket>();
	//std::shared_ptr<Rocket> PlayerB = PlayerA->get_shared_ptr();

	//PlayerA.use_count();

	return S_OK;
}

void SecondScene::release(void)
{
	SAFE_DELETE(_temp);
}

void SecondScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (MessageBox(_hWnd, "게임을 종료하시겠습니까?", "종료 확인", MB_OKCANCEL) == IDOK)
		{
			PostQuitMessage(0);
		}
	}
	_rocket->update();
	_em->update();
	_temp->update();
	collision();
	//_bgSpeed += 3;
	cout << _bgSpeed << endl;
}

void SecondScene::render()
{
	//IMAGEMANAGER->loopRender("배경 루프", getMemDC(),
	//	&RectMake(0, 0, WINSIZE_X, WINSIZE_Y),
	//	_bgSpeed, 0);

	IMAGEMANAGER->findImage("슈팅맵")->render(getMemDC());

	SetBkMode(getMemDC(), TRANSPARENT); // dc를 그릴때 텍스트버퍼를 투명하게 해주는 함수.

	//기존 텍스트
	char str[128];
	wsprintf(str, "기존");
	TextOut(getMemDC(), 230, 350, str, strlen(str));

	//새로운 방식
	wsprintf(str, "새로운방식");
	FONTMANAGER->drawText(getMemDC(), 100, 400, "궁서", 70, 600, str, strlen(str),RGB(255,0,0));
	_rocket->render();
	_em->render();
}

SecondScene::SecondScene()
{
}


SecondScene::~SecondScene()
{
}





/*
과제1. 로켓에 flame이미지 추가

- Flame 이미지는 프레임으로 렌더를 시킨다.

※ Flame 클래스에는 로켓에 대한 정보가 있으면 안되며 MainGame 또한 Flame에 대한 정보를 알 필요가 없다.

- 로켓에 플레임을 넣어야되나?

과제2. 


*/