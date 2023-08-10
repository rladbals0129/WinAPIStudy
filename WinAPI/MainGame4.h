#pragma once
#include "GameNode.h"
#include "StartScene.h"
#include "SecondScene.h"
#include "C3DVector.h"
#include "C3DMatrix.h"
#include "Rocket.h"
//#include "ResourceClass.h"

class MainGame4 : public GameNode
{
private:
	int _alphaA;
	bool _isAlphaIncrese;

	//ResourceClass _re; //리소스를 관리해주는 클래스
	StartScene* _start;
	SecondScene* _second;
	Rocket* _rocket;

	GameNode* _currentScene; //손대기x
	// ㄴ 런타임때 무언갈 바꿔주기 위해 올려둔거다.
	// 윈메인에서 init함수는 너무 늦게 호출된다 (프로시저 호출될떄 호출되잖아)
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

	MainGame4() : _currentScene(nullptr) {} // ㄴ 그러니 생성자에서 winMain에서 동적할당이 됨과 동시에 세팅해주자
};



