#pragma once
#include "GameNode.h"

#define BULLET_MAX	10
#define PLAYER_SPEED 5
#define ENEMY_MAX	80
//80개의 적 객체에 stl을 사용해야 할까??
// 적 객체가 가지고있는 속성을 생각 ->단일이미지면x
//애니메이션이 많이 들어가면 사용을 고려

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