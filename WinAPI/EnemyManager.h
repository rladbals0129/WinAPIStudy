#pragma once
#include "GameNode.h"
#include "Enemy.h"

class EnemyManager : public GameNode
{
private:
	typedef vector<Enemy*> vEnemy;						//���� ������ �����ϱ� �����Ǹ� ���� typedef�� �������.
	typedef vector<Enemy*>::iterator viEnemy;

private:
	vEnemy _vMinion; //������ �θ�ä�� ������ �Ļ���ų �غ�
	viEnemy _viMinion;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

	void setMinion(void);
};

