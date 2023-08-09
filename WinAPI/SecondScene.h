#pragma once
#include "GameNode.h"
#include "TempSoundScene.h"
class SecondScene : public GameNode
{
private:
	int _offsetX, _offsetY;
	int _bgSpeed; //루프용변수

	TempSoundScene* _temp;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

	SecondScene();
	~SecondScene();
};

