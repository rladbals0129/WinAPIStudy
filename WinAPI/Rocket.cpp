#include "stdafx.h"
#include "Rocket.h"

HRESULT Rocket::init(void)
{
	_x = static_cast<float>(WINSIZE_X / 2);
	_y = static_cast<float>(WINSIZE_Y / 2);

	//이렇게쓰면 확장성이 닫힌다
	//IMAGEMANAGER->addImage("로켓", "Resources/Images/Object/Rocket.bmp", 52, 64, true, RGB(255, 0, 255));

	//  ↓하지만 이렇게 바뀌면?
	_image = IMAGEMANAGER->addImage("로켓", "Resources/Images/Object/Rocket.bmp", 52, 64, true, RGB(255, 0, 255));
	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
	//그냥 보면 모르겠지만 확장성이 늘어남.
	//api 특성상 rect를 쓰겠다.
	//객체에 맞게끔 세팅을 해준다면 
	/*
			↑  이렇게 안하고 그냥 52 64 상수때려박으면 확장성이 막힌다. 다른곳에 안쓰고 그냥 이거만쓰겠단소리.

			_x,_y 얘를 연결해줄 방법을 생각하자.
	*/

	_flame = new Flame;
	_flame->init("Flame.bmp", &_x, &_y);

	_missile = new MissileM1;
	_missile->init(5, 600.f);
//	spRocket.push_back(std::shared_ptr<Rocket>(new Rocket));

	
	

	

	return S_OK;
}

void Rocket::release(void)
{
	_flame->release();
	SAFE_DELETE(_flame);

	_missile->release();
	SAFE_DELETE(_missile);
}

void Rocket::update(void)
{

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _rc.right < WINSIZE_X)
	{
		_x += ROCKET_SPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _rc.left > 0)
	{
		_x -= ROCKET_SPEED;

	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _rc.bottom < WINSIZE_Y)
	{
		_y += ROCKET_SPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && _rc.top > 0)
	{
		_y -= ROCKET_SPEED;
	}

	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_missile->fire((_rc.left + _rc.right )/2,_y - 60);
	}


	_flame->update();
	_missile->update();
}

void Rocket::render()
{
	_image->render(getMemDC(), _rc.left, _rc.top);
	_flame->render();
	_missile->render();
}
