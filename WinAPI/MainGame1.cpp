#include "Stdafx.h"
#include "MainGame1.h"




HRESULT MainGame1::init(void)
{
	GameNode::init();
	//플레이어 초기화
	_playerRC = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 200, 40, 40);
	
	//적 모양,이동속도,죽음여부 초기화
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		_enemy[i].rc = RectMakeCenter(
			RND->getFromIntTo(20, WINSIZE_X - 20),
			-(RND->getFromIntTo(80, WINSIZE_Y * 2)),
			20, 20);
		_enemy[i].speed = RND->getFromIntTo(2, 8);
		_enemy[i].die = false;
	}

	return S_OK;
}

void MainGame1::release(void)
{
	GameNode::release();
}

void MainGame1::update(void)
{
	GameNode::update();

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && WINSIZE_X > _playerRC.right)
	{
		_playerRC.left += PLAYER_SPEED;
		_playerRC.right += PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && 0 < _playerRC.left)
	{
		_playerRC.left -= PLAYER_SPEED;
		_playerRC.right -= PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && 0 < _playerRC.top)
	{
		_playerRC.top -= PLAYER_SPEED;
		_playerRC.bottom -= PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && WINSIZE_Y > _playerRC.bottom)
	{
		_playerRC.top += PLAYER_SPEED;
		_playerRC.bottom += PLAYER_SPEED;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		fireBullet();
	}

	//총알 이동
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!_bullet[i].fire)continue;
		_bullet[i].rc.top -= 14;
		_bullet[i].rc.bottom -= 14;

		if (_bullet[i].rc.bottom < 0) _bullet[i].fire = false;
	}

	//적 객체 이동
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (_enemy[i].die) continue;

		_enemy[i].rc.top += _enemy[i].speed;
		_enemy[i].rc.bottom += _enemy[i].speed;

		if (_enemy[i].rc.top > WINSIZE_Y)	//화면밖으로 넘어가면 위로 올려준다
		{
			_enemy[i].rc = RectMakeCenter(
				RND->getFromIntTo(20, WINSIZE_X - 20),
				-(RND->getFromIntTo(80, WINSIZE_Y * 2)),
				20, 20);
		}
	}



}

void MainGame1::render(HDC hdc)
{
	DrawRectMake(hdc, _playerRC);

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (_enemy[i].die) continue;

		Rectangle(hdc, _enemy[i].rc.left, _enemy[i].rc.top, _enemy[i].rc.right, _enemy[i].rc.bottom);
	}

	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!_bullet[i].fire) continue;
		Ellipse(hdc, _bullet[i].rc.left, _bullet[i].rc.top, _bullet[i].rc.right, _bullet[i].rc.bottom);
	}
}

void MainGame1::fireBullet(void)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (_bullet[i].fire)continue;

		_bullet[i].fire = true;
		_bullet[i].rc = RectMakeCenter
		(
			_playerRC.left + (_playerRC.right - _playerRC.left) / 2,
			_playerRC.top + (_playerRC.bottom - _playerRC.top) / 2 - 24, 10, 10
		);
		break;
	}
}








MainGame1::MainGame1()
{
}


MainGame1::~MainGame1()
{
}
/*
과제 1. 종스크롤 슈팅 게임

- 플레이어 체력바 설정
ㄴ 적과 충돌하면 체력이 감소되고 체력바는 3단계로 처리
ㄴ 빨 / 주 / 초

- 플레이어가 발사한 총알로 적을 제거

과제 2. 1 VS 1 횡스크롤 슈팅 게임

- 왼쪽에 1P / 오른쪽에 2P

- 체력 바는 대전게임처럼 중앙을 기준으로 좌우 배치
ㄴ 체력 바 상태에 따라 녹 / 노 / 빨

- 공격 당하면 당한쪽은 당연히 체력이 감소해야 한다.

※ 필수 :
스킬 2개 + 2개 = 4개
아이템을 2종 구현해 온다.

*/
