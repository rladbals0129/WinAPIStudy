#pragma once
#include "GameNode.h"
//Ŭ������ ����� ���� ����...
// ������� �ο�

#define ROCKET_SPEED 3.0f

class Rocket : public GameNode //player
{
private:
	GImage* _image; //�Ŵ���Ŭ������ �ִµ� �� ���°���??
	//��� ��ä�� �ٲ��ټ� �ִ�. Ȯ�强�� ����
	

	RECT _rc;
	float _x, _y;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();
};

//�갡 �� �ʿ��Ѱ�, ���� �갡 �־�� �ϳ� 