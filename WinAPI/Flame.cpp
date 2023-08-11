#include "stdafx.h"
#include "Flame.h"



HRESULT Flame::init(const char* imageName, float* x, float* y)
{

	_image = IMAGEMANAGER->addFrameImage("부스터", "Resources/Images/Object/Flame.bmp",
		0,0,
		432, 297,
		9, 1,
		true,
		RGB(255, 0, 255));
	_posX = x;
	_posY = y;

	_rc = RectMakeCenter((int)_posX,(int)_posY , _image->getFrameWidth(), _image->getFrameHeight());
	_flameTick = 7.0f; //getTickCount API공용함수 쓰기 위한 변수

	return S_OK;
}

void Flame::release(void)
{
}

void Flame::update(void)
{
	if (FLAME_COUNT + _flameTick <= GetTickCount())
	{
		_flameTick = GetTickCount();
		_image->setFrameX(_image->getFrameX() + 1);

		if (_image->getFrameX() >= _image->getMaxFrameX())
		{
			_image->setFrameX(0);
		}
	}

	_rc = RectMakeCenter(*_posX, *_posY+180, _image->getFrameWidth(),
		_image->getFrameHeight());

}

void Flame::render()
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _image->getFrameX(), _image->getFrameY());
}

void Flame::FlameRender()
{

}
