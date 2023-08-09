#include "stdafx.h"
#include "ResourceClass.h"


HRESULT ResourceClass::init(void)
{
	IMAGEMANAGER->addImage("배경 루프", "Resources/Images/BackGround/bg.bmp",
		1570, WINSIZE_Y);
	//많은 이미지.....
	IMAGEMANAGER->addImage("배경 루프", "Resources/Images/BackGround/bg.bmp",
		1570, WINSIZE_Y);
	IMAGEMANAGER->addImage("배경 루프", "Resources/Images/BackGround/bg.bmp",
		1570, WINSIZE_Y);
	IMAGEMANAGER->addImage("배경 루프", "Resources/Images/BackGround/bg.bmp",
		1570, WINSIZE_Y);
	IMAGEMANAGER->addImage("배경 루프", "Resources/Images/BackGround/bg.bmp",
		1570, WINSIZE_Y);
	IMAGEMANAGER->addImage("배경 루프", "Resources/Images/BackGround/bg.bmp",
		1570, WINSIZE_Y);
	IMAGEMANAGER->addImage("배경 루프", "Resources/Images/BackGround/bg.bmp",
		1570, WINSIZE_Y);
	IMAGEMANAGER->addImage("배경 루프", "Resources/Images/BackGround/bg.bmp",
		1570, WINSIZE_Y);

	return S_OK;
}


ResourceClass::ResourceClass()
{
}


ResourceClass::~ResourceClass()
{
}
