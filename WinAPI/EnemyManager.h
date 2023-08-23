#pragma once
#include "GameNode.h"
#include "Enemy.h"
#include "Bullets.h"

class Rocket;


class EnemyManager : public GameNode
{
private:
	typedef vector<Enemy*> vEnemy;						//���� ������ �����ϱ� �����Ǹ� ���� typedef�� �������.
	typedef vector<Enemy*>::iterator viEnemy;

private:
	vEnemy _vMinion; //������ �θ�ä�� ������ �Ļ���ų �غ�
	viEnemy _viMinion;

	Bullet* _bullet;
	Rocket* _rocket;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

	void setMinion(void);
	void removeMinion(int arrNum);

	void minionBulletFire(void);
	void collision(void);

	vector<Enemy*> getMinions(void) { return _vMinion; }
	
	Bullet* getBullet(void) { return _bullet; }

	void setRocketMemoryAddress(Rocket* rk) { _rocket = rk; }

};

