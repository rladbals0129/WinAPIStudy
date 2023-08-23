#include "stdafx.h"
#include "SecondScene.h"


HRESULT SecondScene::init(void)
{
	IMAGEMANAGER->addImage("����", "Resources/Images/BackGround/bgIce.bmp",
		WINSIZE_X, WINSIZE_Y);

	_offsetX = _offsetY = 0;
	_bgSpeed = 0;

	_temp = new TempSoundScene;

	_rocket = new Rocket;
	_rocket->init();
	_em = new EnemyManager;
	_em->init();

	_em->setRocketMemoryAddress(_rocket);
	_rocket->setEnemyManagerMemoryAddress(_em);

	_as = new AniScene;
	_as->init();

	_x = _y = 0.f;
	//std::shared_ptr<Rocket> PlayerA = std::make_shared<Rocket>();
	//std::shared_ptr<Rocket> PlayerB = PlayerA->get_shared_ptr();

	//PlayerA.use_count();

	return S_OK;
}

void SecondScene::release(void)
{
	SAFE_DELETE(_temp);

	_rocket->release();
	_em->release();
	_as->release();
	SAFE_DELETE(_rocket);
	SAFE_DELETE(_em);
	SAFE_DELETE(_as);
	
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
	//collision();
	_y -= 2;
	_as->update();
	//_bgSpeed += 3;
	cout << _bgSpeed << endl;
}

void SecondScene::render()
{
	//IMAGEMANAGER->loopRender("��� ����", getMemDC(),
	//	&RectMake(0, 0, WINSIZE_X, WINSIZE_Y),
	//	_bgSpeed, 0);

	RECT rc = { 0,0, WINSIZE_X,WINSIZE_Y };
	IMAGEMANAGER->findImage("����")->loopRender(getMemDC(),&rc,_x,_y);


	SetBkMode(getMemDC(), TRANSPARENT); // dc�� �׸��� �ؽ�Ʈ���۸� �����ϰ� ���ִ� �Լ�.


	_rocket->render();
	_em->render();


	_as->render();
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

/*
27���� ����

1. ������ ppt ��ǥ �غ�
�� ��ǥ�� : ����
�� ��ǥ�� : 

2. ������Ʈ������ (�帣 : ����)
�� 27(��)���� ->������ ����

�� ���� �Ұ� : ���ο� �̹��� �ʼ� (1945,���� �ø���)
1. ��ŸƮ�� ���Ӿ� + �÷��̾� ���� ��
2. ���� ���̸� ������ ȹ���ϴ� �ý���
3. �÷��̾� -> ü�� / ������
4. ���� ��� ���̸� ��������(���� ������ ���ؼ��� �ڿ�������)
	������ �ּ�2 + @ +�߰�����
5. ������ ���̸� ���� ������ �ٽ� �������� ������
6. ������
*/