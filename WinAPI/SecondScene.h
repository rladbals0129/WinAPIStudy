#pragma once
#include "GameNode.h"
#include "TempSoundScene.h"
#include "Rocket.h"
#include "EnemyManager.h"
class SecondScene : public GameNode
{
private:
	int _offsetX, _offsetY;
	int _bgSpeed; //루프용변수

	TempSoundScene* _temp;

	Rocket* _rocket;
	EnemyManager* _em;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

	SecondScene();
	~SecondScene();
};

