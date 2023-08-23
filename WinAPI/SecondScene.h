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
	int _bgSpeed; //루프용변수

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
애니메이션 클래스에 속한 함수 완성

-미완성 함수 완성시키기
ㄴsetPlayFrame()
ㄴ setPllayFrame()
ㄴ setFPS()

과제3 세미포트폴리오 선행작업 (코드 x ->리소스)
ㅇ*/