#include "Stdafx.h"
#include "MainGame4.h"




HRESULT MainGame4::init(void)
{
	GameNode::init(true);

	IMAGEMANAGER->addImage("���� �����̽�", "Resources/Images/BackGround/DeadSpace.bmp", WINSIZE_X, WINSIZE_Y);


	_alphaA = 0;
	_isAlphaIncrese = false;

	return S_OK;
}

void MainGame4::release(void)
{
	GameNode::release();

}

void MainGame4::update(void)
{
	GameNode::update();
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (MessageBox(_hWnd, "������ �����Ͻðڽ��ϱ�?", "���� Ȯ��", MB_OKCANCEL) == IDOK)
		{
			PostQuitMessage(0);
		}
	}
	_alphaA++;

}

void MainGame4::render(void)
{
	
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS); //�簢���ȿ� ������ �귯���� ä��� �Լ�
	//=================================================
	
	IMAGEMANAGER->alphaRender("���� �����̽�", getMemDC(), 0, 0, _alphaA);

	//=================================================
	this->getBackBuffer()->render(getHDC());

}

/*
����1. ���� �޺��̹��� �ϼ�

- �����̽� �ٸ� ������ 1Ÿ���� ���������ݱ��� �ڵ����� ���
�� �������� �ݺ�

����2 ������ �̹��� ó��

-���۾� + ���Ӿ�

- ���Ӿ������� �Ʒ��� �̹����� guiȭ ���Ѽ� �����Ų��(��ư)
�� ������ ����

-�ʼ��̹���

�� ���,���,�̵�(��,��), ���(��,��) ,�밢�����,�������(��,�ѿ�) , �� ������, �¸�����(�ʴ�����),��ų Ŭ���̸�������
,�й�

*/


/*
����1. ĳ���� �����

- �̹��� �ʼ� : ���, ��, ĳ����(���,�̵�,����,���� ����ִ� ���)

- �⺻������ ���� �������� ���� ���� �𼭸��� ������ �� �߰��� �������� õõ�� �������� �������

- ĳ���Ͱ� ���� ��� �ִ� ���¿��� �� / �Ǵ� �Ʒ�����Ű�� ������ �ö󰡰ų� �������� �־���Ѵ�.

- ���� ĳ���Ͱ� �� ���� �ö� ���� �ٽ� �Ʒ��� �����ϸ� ĳ���ʹ� ���鿡 �����Ҽ��־���Ѵ�

- ĳ���� ���� ������ ������ �ְ� ĳ���ʹ� ���� �ؿ��� ������ ������ �ö� �� ���ִ�

- ĳ���ʹ� ������ �ö� ���¿��� �������� �ٽ� ������ �� ������ ok

����2. �̴ϸ� ����

- �÷��̾��� �������� �̴ϸʿ��� �״�� Ȯ���ؾ� �Ѵ�
�� �����ӱ��� �����ϰ�


*/