#include "stdafx.h"
#include "SecondScene.h"


HRESULT SecondScene::init(void)
{
	IMAGEMANAGER->addImage("전장", "Resources/Images/BackGround/bgIce.bmp",
		WINSIZE_X, WINSIZE_Y);

	_offsetX = _offsetY = 0;
	_bgSpeed = 0;

	_temp = new TempSoundScene;

	_rocket = new Rocket;
	_rocket->init();
	_em = new EnemyManager;
	_em->init();

	_em->setRocketMemoryAddress(_rocket);
	_rocket->setEnemyManagerMemoryAddress(_em);

	_as = new AniScene;
	_as->init();

	_x = _y = 0.f;
	//std::shared_ptr<Rocket> PlayerA = std::make_shared<Rocket>();
	//std::shared_ptr<Rocket> PlayerB = PlayerA->get_shared_ptr();

	//PlayerA.use_count();

	return S_OK;
}

void SecondScene::release(void)
{
	SAFE_DELETE(_temp);

	_rocket->release();
	_em->release();
	_as->release();
	SAFE_DELETE(_rocket);
	SAFE_DELETE(_em);
	SAFE_DELETE(_as);
	
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
	//collision();
	_y -= 2;
	_as->update();
	//_bgSpeed += 3;
	cout << _bgSpeed << endl;
}

void SecondScene::render()
{
	//IMAGEMANAGER->loopRender("배경 루프", getMemDC(),
	//	&RectMake(0, 0, WINSIZE_X, WINSIZE_Y),
	//	_bgSpeed, 0);

	RECT rc = { 0,0, WINSIZE_X,WINSIZE_Y };
	IMAGEMANAGER->findImage("전장")->loopRender(getMemDC(),&rc,_x,_y);


	SetBkMode(getMemDC(), TRANSPARENT); // dc를 그릴때 텍스트버퍼를 투명하게 해주는 함수.


	_rocket->render();
	_em->render();


	_as->render();
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

/*
27일차 과제

1. 팀포폴 ppt 발표 준비
ㄴ 발표일 : 명일
ㄴ 발표자 : 

2. 세미포트폴리오 (장르 : 슈팅)
ㄴ 27(일)까지 ->월요일 제출

꼭 들어가야 할것 : 새로운 이미지 필수 (1945,동방 시리즈)
1. 스타트씬 게임씬 + 플레이어 선택 씬
2. 적을 죽이면 점수를 획득하는 시스템
3. 플레이어 -> 체력 / 라이프
4. 적을 모두 죽이면 보스출현(보스 출현에 대해서는 자연스럽게)
	ㄴ적은 최소2 + @ +중간보스
5. 보스를 죽이면 게임 루프를 다시 가능하한 구조로
6. 아이템
*/