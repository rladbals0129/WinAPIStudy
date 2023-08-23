#include "stdafx.h"
#include "Enemy.h"



Enemy::Enemy(void) : _rc(RectMake(0, 0, 0, 0)),
_currentFrameX(0),
_currentFrameY(0),
_x(0.f),
_y(0.f),
_worldTimeCount(0.f),
_rndTimeCount(0.f),
_rndFireCount(0.f),
_bulletFireCount(0.f)
{
}

HRESULT Enemy::init(void)
{
	//! Do Nothing
	return S_OK;
}

HRESULT Enemy::init(const char* imageName, POINT position)
{
	_worldTimeCount = GetTickCount();
	_rndTimeCount = RND->getFromFloatTo(50, 150);

	_bulletFireCount = TIMEMANAGER->getWorldTime();
	_rndFireCount = RND->getFromFloatTo(0.5f, 4.5f);



	_image = IMAGEMANAGER->findImage(imageName);
	_rc = RectMakeCenter(position.x, position.y,
		_image->getFrameWidth(), _image->getFrameHeight());
	return S_OK;
}

void Enemy::release(void)
{	
	//! Do Nothing
}

void Enemy::update(void)
{
	move();
}

void Enemy::render(void)
{
	draw();
	animation();
}

void Enemy::move(void)
{
	//여기서 구현x
	// 적마다 움직임이 다르다.
	// 상속을 전제한 클래스인데 움직임을 정의해버리면....안댐 ->자식구현
}

void Enemy::draw(void) //상속이 전제된 클래스기 때문에 유지보수가 편해야함
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top,
		_currentFrameX, _currentFrameY);
}

void Enemy::animation(void)
{
	if (_rndTimeCount + _worldTimeCount <= GetTickCount())
	{
		_worldTimeCount = GetTickCount();
		_currentFrameX++;
		if (_image->getMaxFrameX() < _currentFrameX)
		{
			_currentFrameX = 0;
		}
	}
}


bool Enemy::bulletCouintFire(void)
{
	if (_rndFireCount + _bulletFireCount <= TIMEMANAGER->getWorldTime())
	{
		_bulletFireCount = TIMEMANAGER->getWorldTime();
		_rndFireCount = RND->getFromFloatTo(2.f, 6.f);

		return true;
	}

	return false;
}


/*
과제1. 움직이는 적 패턴 추가

- 움직임을 서로 다르게 해온다.
ㄴ 패턴은 총 3가지를 만들면 ok

과제2. 로켓 무장변경 추가 (무기)
- F1 : 일반미사일

- F2 : 산탄

- F3 : 미니로켓

- F4 : 쉴드

- F5 : 유도미사일

- F6 : 레이저

- F7 : 블랙홀
ㄴ 영향을 받는적과 아닌적으로 구분
ㄴ 블랙홀의 중점에 가까운 적일수록 스킬이 끝나면 튕겨나가는 관성이 강해진다.


*/
