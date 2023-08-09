#include "stdafx.h"
#include "SecondScene.h"


HRESULT SecondScene::init(void)
{
	IMAGEMANAGER->addImage("��� ����", "Resources/Images/BackGround/bg.bmp",
		1570, WINSIZE_Y);

	_offsetX = _offsetY = 0;
	_bgSpeed = 0;

	_temp = new TempSoundScene;
	return S_OK;
}

void SecondScene::release(void)
{
	SAFE_DELETE(_temp);
}

void SecondScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (MessageBox(_hWnd, "������ �����Ͻðڽ��ϱ�?", "���� Ȯ��", MB_OKCANCEL) == IDOK)
		{
			PostQuitMessage(0);
		}
	}

	_temp->update();
	_bgSpeed += 3;
	cout << _bgSpeed << endl;
}

void SecondScene::render()
{
	IMAGEMANAGER->loopRender("��� ����", getMemDC(),
		&RectMake(0, 0, WINSIZE_X, WINSIZE_Y),
		_bgSpeed, 0);

	SetBkMode(getMemDC(), TRANSPARENT); // dc�� �׸��� �ؽ�Ʈ���۸� �����ϰ� ���ִ� �Լ�.

	//���� �ؽ�Ʈ
	char str[128];
	wsprintf(str, "����");
	TextOut(getMemDC(), 230, 350, str, strlen(str));

	//���ο� ���
	wsprintf(str, "���ο���");
	FONTMANAGER->drawText(getMemDC(), 100, 400, "�ü�", 70, 600, str, strlen(str),RGB(255,0,0));
	
}

SecondScene::SecondScene()
{
}


SecondScene::~SecondScene()
{
}



//HFONT font;
//HFONT oldFont; //������Ʈ�� �õ���Ʈ�� �޸𸮿� �׷��ΰ� �����ϴ� ����
//
//
/*
//font = CreateFopnt
//(
//	v����ũ��, ������, ����(��ü), ���� ����, v���� ����,
//	����( t / f ), ����( t / f ), ��Ҽ�,
//	v���ڼ���, ��� ��Ȯ��, Ŭ���� ��Ȯ��, ����� ��, �ڰ�, v��Ʈ
//);
//*/
//
//
//
//font = CreateFont
//(
//	70, 0, 0, 0, 600,
//	0, 0, 1,
//	HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("�ü�")
//); // �� �ѱ���2����Ʈ�� ����ߴ�
//
//oldFont = (HFONT)SelectObject(getMemDC(), font);
//
//wsprintf(str, "���ο� ��Ʈ");
//TextOut(getMemDC(), 100, 400, str, strlen(str));
//
//SelectObject(getMemDC(), oldFont);
//DeleteObject(font);// �õ���Ʈ�� �־��ְ� ���̻󾵸������ ����Ʈ���ش�