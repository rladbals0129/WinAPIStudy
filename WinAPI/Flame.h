#pragma once
#include "GameNode.h"

#define FLAME_COUNT 4.0f

//추상화를 전제 해야함.. (다른쪽에서 활용도가 있냐없냐)
class Flame : public GameNode
{
private:
	GImage* _image;
	RECT _rc;


	float* _posX = nullptr;
	float* _posY = nullptr;
	float _flameTick;

public:
	HRESULT init(const char* imageName,float* x, float* y); //위치를 맞출거면 디테일을 맞춰줄x y값 매개변수 추가
	void release(void);
	void update(void);
	void render();

	void FlameRender();

};

