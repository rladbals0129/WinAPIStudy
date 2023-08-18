#include "stdafx.h"
#include "SecondScene.h"


HRESULT SecondScene::init(void)
{
	IMAGEMANAGER->addImage("���ø�", "Resources/Images/BackGround/ShootingBG.bmp",
		WINSIZE_X, WINSIZE_Y);

	_offsetX = _offsetY = 0;
	_bgSpeed = 0;

	_temp = new TempSoundScene;

	_rocket = new Rocket;
	_rocket->init();
	_em = new EnemyManager;
	_em->init();
	//std::shared_ptr<Rocket> PlayerA = std::make_shared<Rocket>();
	//std::shared_ptr<Rocket> PlayerB = PlayerA->get_shared_ptr();

	//PlayerA.use_count();

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
	_rocket->update();
	_em->update();
	_temp->update();
	collision();
	//_bgSpeed += 3;
	cout << _bgSpeed << endl;
}

void SecondScene::render()
{
	//IMAGEMANAGER->loopRender("��� ����", getMemDC(),
	//	&RectMake(0, 0, WINSIZE_X, WINSIZE_Y),
	//	_bgSpeed, 0);

	IMAGEMANAGER->findImage("���ø�")->render(getMemDC());

	SetBkMode(getMemDC(), TRANSPARENT); // dc�� �׸��� �ؽ�Ʈ���۸� �����ϰ� ���ִ� �Լ�.

	//���� �ؽ�Ʈ
	char str[128];
	wsprintf(str, "����");
	TextOut(getMemDC(), 230, 350, str, strlen(str));

	//���ο� ���
	wsprintf(str, "���ο���");
	FONTMANAGER->drawText(getMemDC(), 100, 400, "�ü�", 70, 600, str, strlen(str),RGB(255,0,0));
	_rocket->render();
	_em->render();
}

SecondScene::SecondScene()
{
}


SecondScene::~SecondScene()
{
}





/*
����1. ���Ͽ� flame�̹��� �߰�

- Flame �̹����� ���������� ������ ��Ų��.

�� Flame Ŭ�������� ���Ͽ� ���� ������ ������ �ȵǸ� MainGame ���� Flame�� ���� ������ �� �ʿ䰡 ����.

- ���Ͽ� �÷����� �־�ߵǳ�?

����2. 


*/