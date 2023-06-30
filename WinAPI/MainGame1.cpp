#include "Stdafx.h"
#include "MainGame1.h"




HRESULT MainGame1::init(void)
{
	GameNode::init();
	//�÷��̾� �ʱ�ȭ
	_playerRC = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 200, 40, 40);
	
	//�� ���,�̵��ӵ�,�������� �ʱ�ȭ
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

	//�Ѿ� �̵�
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!_bullet[i].fire)continue;
		_bullet[i].rc.top -= 14;
		_bullet[i].rc.bottom -= 14;

		if (_bullet[i].rc.bottom < 0) _bullet[i].fire = false;
	}

	//�� ��ü �̵�
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (_enemy[i].die) continue;

		_enemy[i].rc.top += _enemy[i].speed;
		_enemy[i].rc.bottom += _enemy[i].speed;

		if (_enemy[i].rc.top > WINSIZE_Y)	//ȭ������� �Ѿ�� ���� �÷��ش�
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
���� 1. ����ũ�� ���� ����

- �÷��̾� ü�¹� ����
�� ���� �浹�ϸ� ü���� ���ҵǰ� ü�¹ٴ� 3�ܰ�� ó��
�� �� / �� / ��

- �÷��̾ �߻��� �Ѿ˷� ���� ����

���� 2. 1 VS 1 Ⱦ��ũ�� ���� ����

- ���ʿ� 1P / �����ʿ� 2P

- ü�� �ٴ� ��������ó�� �߾��� �������� �¿� ��ġ
�� ü�� �� ���¿� ���� �� / �� / ��

- ���� ���ϸ� �������� �翬�� ü���� �����ؾ� �Ѵ�.

�� �ʼ� :
��ų 2�� + 2�� = 4��
�������� 2�� ������ �´�.

*/
