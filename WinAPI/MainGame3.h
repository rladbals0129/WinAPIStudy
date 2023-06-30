#pragma once
#include "GameNode.h"
class MainGame3 : public GameNode
{
private:
	GImage* _bgImage;
	GImage* _plImage;
	

	RECT _rc;

	int _countA, _countB;
	int _alphaA, _alphaB;
	int _alphaNum;

	bool _isAlphaIncrese;


	GImage* _nine;

	int _count;
	int _alphaA2;
	int _index;
	bool _isLeft;
	bool _isAlphaIncrese2;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

};

