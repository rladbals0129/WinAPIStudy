#pragma once
#include "GameNode.h"
#include "TempSoundScene.h"
#include "Rocket.h"
#include "EnemyManager.h"
#include "AniScene.h"
class SecondScene : public GameNode
{
private:
	int _offsetX, _offsetY;
	int _bgSpeed; //�����뺯��

	TempSoundScene* _temp;

	Rocket* _rocket;
	EnemyManager* _em;

	AniScene* _as;
	float _x, _y;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

	virtual void collision(void);

	SecondScene();
	~SecondScene();
};

/*
�ִϸ��̼� Ŭ������ ���� �Լ� �ϼ�

-�̿ϼ� �Լ� �ϼ���Ű��
��setPlayFrame()
�� setPllayFrame()
�� setFPS()

����3 ������Ʈ������ �����۾� (�ڵ� x ->���ҽ�)
��*/