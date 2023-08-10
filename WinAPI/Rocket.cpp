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

	//�׳� ���� �𸣰����� Ȯ�强�� �þ.
	//api Ư���� rect�� ���ڴ�.
	//��ü�� �°Բ� ������ ���شٸ� 
	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());

	/*
			��  �̷��� ���ϰ� �׳� 52 64 ������������� Ȯ�强�� ������. �ٸ����� �Ⱦ��� �׳� �̰Ÿ����ڴܼҸ�.

			_x,_y �긦 �������� ����� ��������.
	*/

	

	return S_OK;
}

void Rocket::release(void)
{
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

	}
}

void Rocket::render()
{
	_image->render(getMemDC(), _rc.left, _rc.top);
}