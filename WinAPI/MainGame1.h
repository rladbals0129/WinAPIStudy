#pragma once
#include "GameNode.h"

#define BULLET_MAX	10
#define PLAYER_SPEED 5
#define ENEMY_MAX	80
//80���� �� ��ü�� stl�� ����ؾ� �ұ�??
// �� ��ü�� �������ִ� �Ӽ��� ���� ->�����̹�����x
//�ִϸ��̼��� ���� ���� ����� ���

struct tagBullet
{
	RECT rc;
	bool fire;
};

struct tagEnemy
{
	RECT rc;
	int speed;
	bool die;
};

class MainGame1 : public GameNode
{
private:
	tagBullet _bullet[BULLET_MAX];
	tagEnemy _enemy[ENEMY_MAX];

	RECT _playerRC;
	
public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void fireBullet(void);

	MainGame1();
	~MainGame1();
};