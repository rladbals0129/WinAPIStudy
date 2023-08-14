#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy(void) : _rc(RectMake(0, 0, 0, 0)),
_currentFrameX(0),
_currentFrameY(0),
_x(0.f),
_y(0.f),
_worldTimeCount(0.f),
_rndTimeCount(0.f)
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
	//���⼭ ����x
	// ������ �������� �ٸ���.
	// ����� ������ Ŭ�����ε� �������� �����ع�����....�ȴ� ->�ڽı���
}

void Enemy::draw(void) //����� ������ Ŭ������ ������ ���������� ���ؾ���
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

/*
����1. �����̴� �� ���� �߰�

- �������� ���� �ٸ��� �ؿ´�.
�� ������ �� 3������ ����� ok

����2. ���� ���庯�� �߰� (����)
- F1 : �Ϲݹ̻���

- F2 : ��ź

- F3 : �̴Ϸ���

- F4 : ����

- F5 : �����̻���

- F6 : ������

- F7 : ��Ȧ
�� ������ �޴����� �ƴ������� ����
�� ��Ȧ�� ������ ����� ���ϼ��� ��ų�� ������ ƨ�ܳ����� ������ ��������.


*/
