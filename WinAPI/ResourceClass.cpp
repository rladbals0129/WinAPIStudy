#include "stdafx.h"
#include "ResourceClass.h"


HRESULT ResourceClass::init(void)
{
	IMAGEMANAGER->addImage("��� ����", "Resources/Images/BackGround/bg.bmp",
		1570, WINSIZE_Y);
	//���� �̹���.....
	IMAGEMANAGER->addImage("��� ����", "Resources/Images/BackGround/bg.bmp",
		1570, WINSIZE_Y);
	IMAGEMANAGER->addImage("��� ����", "Resources/Images/BackGround/bg.bmp",
		1570, WINSIZE_Y);
	IMAGEMANAGER->addImage("��� ����", "Resources/Images/BackGround/bg.bmp",
		1570, WINSIZE_Y);
	IMAGEMANAGER->addImage("��� ����", "Resources/Images/BackGround/bg.bmp",
		1570, WINSIZE_Y);
	IMAGEMANAGER->addImage("��� ����", "Resources/Images/BackGround/bg.bmp",
		1570, WINSIZE_Y);
	IMAGEMANAGER->addImage("��� ����", "Resources/Images/BackGround/bg.bmp",
		1570, WINSIZE_Y);
	IMAGEMANAGER->addImage("��� ����", "Resources/Images/BackGround/bg.bmp",
		1570, WINSIZE_Y);

	return S_OK;
}


ResourceClass::ResourceClass()
{
}


ResourceClass::~ResourceClass()
{
}
