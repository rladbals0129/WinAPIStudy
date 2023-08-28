#pragma once
#include "GameNode.h"
#include "Rocket.h"
#include "EnemyManager.h"

class ShootingScene : public GameNode
{
private:
	int _offsetX, _offsetY;
	int _bgSpeed; //루프용변수
	
	char _text[64];
	

	Rocket* _rocket;
	EnemyManager* _em;

	
	float _x, _y;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

	virtual void collision(void);

	//ShootingScene();
	//~ShootingScene();
};

