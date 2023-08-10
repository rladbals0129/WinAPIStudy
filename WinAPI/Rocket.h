#pragma once
#include "GameNode.h"
//클래스를 만들면 가장 먼저...
// 설계와의 싸움

#define ROCKET_SPEED 3.0f

class Rocket : public GameNode //player
{
private:
	GImage* _image; //매니저클래스가 있는데 왜 들어온거지??
	//대상 객채를 바꿔줄수 있다. 확장성을 위해
	

	RECT _rc;
	float _x, _y;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();
};

//얘가 왜 필요한가, 굳이 얘가 있어야 하나 