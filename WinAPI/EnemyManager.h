#pragma once
#include "GameNode.h"
#include "Enemy.h"

class EnemyManager : public GameNode
{
private:
	typedef vector<Enemy*> vEnemy;						//적은 종류가 많으니까 재정의를 위해 typedef를 붙혀줬다.
	typedef vector<Enemy*>::iterator viEnemy;

private:
	vEnemy _vMinion; //고정된 부모객채를 가지고 파생시킬 준비
	viEnemy _viMinion;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

	void setMinion(void);
};

