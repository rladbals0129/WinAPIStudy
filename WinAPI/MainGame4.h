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

	//ResourceClass _re; //���ҽ��� �������ִ� Ŭ����
	StartScene* _start;
	SecondScene* _second;
	Rocket* _rocket;

	GameNode* _currentScene; //�մ��x
	// �� ��Ÿ�Ӷ� ���� �ٲ��ֱ� ���� �÷��аŴ�.
	// �����ο��� init�Լ��� �ʹ� �ʰ� ȣ��ȴ� (���ν��� ȣ��ɋ� ȣ����ݾ�)
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

	MainGame4() : _currentScene(nullptr) {} // �� �׷��� �����ڿ��� winMain���� �����Ҵ��� �ʰ� ���ÿ� ����������
};



