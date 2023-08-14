#include "stdafx.h"
#include "Rocket.h"

HRESULT Rocket::init(void)
{
	_x = static_cast<float>(WINSIZE_X / 2);
	_y = static_cast<float>(WINSIZE_Y / 2);

	//�̷��Ծ��� Ȯ�强�� ������
	//IMAGEMANAGER->addImage("����", "Resources/Images/Object/Rocket.bmp", 52, 64, true, RGB(255, 0, 255));

	//  �������� �̷��� �ٲ��?
	_image = IMAGEMANAGER->addImage("����", "Resources/Images/Object/Rocket.bmp", 52, 64, true, RGB(255, 0, 255));
	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
	//�׳� ���� �𸣰����� Ȯ�强�� �þ.
	//api Ư���� rect�� ���ڴ�.
	//��ü�� �°Բ� ������ ���شٸ� 
	/*
			��  �̷��� ���ϰ� �׳� 52 64 ������������� Ȯ�强�� ������. �ٸ����� �Ⱦ��� �׳� �̰Ÿ����ڴܼҸ�.

			_x,_y �긦 �������� ����� ��������.
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
