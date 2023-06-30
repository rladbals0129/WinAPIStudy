#pragma once
#include "GameNode.h"
class MainGame4 : public GameNode
{
private:
	int _alphaA;
	bool _isAlphaIncrese;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

};

