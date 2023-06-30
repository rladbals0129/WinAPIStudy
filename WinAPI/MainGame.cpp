#include "Stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void)
{
	GameNode::init();

	_currentRect = CURRENTRECT_NULL; //1.�ʱⰪ ����

	for (int i = 0; i < 2; i++)	//�δ����� ������ ���� ������ ������ �ȵǴ� �δ����� ��ġ�� �ʱ�ȭ�ߴ�. �״����� ����ؾߵɱ�?
	{							//�������� ó���ϸ�ǰڴ�.
		for (int j = 0; j < 4; j++)
		{
			_rc[i * 4 + j] = RectMakeCenter(100 + j * 200, 200 + i * 200, 100, 100); //�δ��� ��ġ ����
		}
	}

	_index = 0;
	_count = 0;
	_score = 0;
	_time = RND->getFromIntTo(30, 60);

	_bIsSelected = false;
	_bIsOnceCheck = false;

	_mole = new Example_Mole;
	_mole->init();
	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
	_mole->release();
	SAFE_DELETE(_mole);
}
//POINT _ptMouse;
void MainGame::update(void) //3.
{
	GameNode::update();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) //Ŭ���Ǹ� ���ھ �ø��� ����üũ�� Ʈ���
	{
		/*if (_rc[0].right > _ptMouse.x &&
			_rc[0].left < _ptMouse.x&&
			_rc[0].left < _ptMouse.x && _bIsOnceCheck)
		{

		}*/

		//PtInRect(): ��Ʈ �ȿ� POINT(X,Y)�� �ִ��� �˻���Ͽ� ����Ʈ�� �簢���ȿ� ������ true�� ��ȯ�ϴ� �Լ�
		//�����δ� �̰��� ����.
		if (PtInRect(&_rc[_index], _ptMouse) && !_bIsOnceCheck)
		{
			_score += 100;
			_bIsOnceCheck = true;
		}
	}

	if (!_bIsSelected)
	{
		_count++;
		if (_count % _time == 0)
		{
			_count = 0;
			_index = RND->getInt(8);
			_currentRect = (CURRENT_RECT)_index;
			_bIsSelected = true;
		}
	}
	else
	{
		_count++;
		if (_count % _time == 0)
		{
			_bIsOnceCheck = false;
			_bIsSelected = false;
			_currentRect = CURRENTRECT_NULL;
			_time = RND->getFromIntTo(30, 60);
			_index = 100;
		}
	}

	_mole->update();

	//if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	//{
	//	rc.top += 3;
	//	rc.bottom += 3;
	//}
	//if (KEYMANAGER->isStayKeyDown(VK_UP))
	//{
	//	rc.top -= 3;
	//	rc.bottom -= 3;

	//}
	//if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	//{
	//	rc.left -= 3;
	//	rc.right -= 3;
	//}
	//if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	//{
	//	rc.left += 3;
	//	rc.right += 3;
	//}

}

void MainGame::render(HDC hdc) //2. �ʱ�ȭ�ϰ� �������� ó�������. 
{

	for (int i = 0; i < 8; i++) //�δ�������
	{
		Rectangle(hdc, _rc[i].left, _rc[i].top, _rc[i].right, _rc[i].bottom);
	}

	char strScore[128];

	wsprintf(strScore, "Score : %d", _score);
	TextOut(hdc, 50, 100, strScore, strlen(strScore));

	if (_bIsSelected) //�δ����� ���õǸ� ���� ������Ʈ
	{
		int r = RND->getInt(256);
		int g = RND->getInt(256);
		int b = RND->getInt(256);
		HBRUSH brush = CreateSolidBrush(RGB(r, g, b));
		FillRect(hdc, &_rc[_index], brush);
		// �̷������� DC�� ���� �ǵ��̴� �Լ��� ������ �����.
		// ���� delete�� �� ���������.
		DeleteObject(brush);
	}
	//_mole->render(hdc);

	/*if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	}*/

}

/*

- �ָ� ���� ����

�� �𸮾� 1��_�� �׸���_������
�� ���Ͽ���9��
 �� ���ð��� ����

����1. �����ϱ�

- ���� ��ư�� �����鼭 ���� ����

- ������ ���۵ǰ� �÷��̾ ���������� ��ƾ �ð��� ȭ�鿡 ����Ѵ�.

�ʼ� : ����� + �ٽ��ϱ�

- �÷��̾�� ���������� �¿� ����� �ٸ��� ����

����2. �Ѿ� �߻�

- �ϴܿ��� �¿�� ������ �� �ִ� �÷��̾ ����

- �����̽��ٸ� ������ �÷��̾ �Ѿ��� �߻��Ѵ�.

����3. �Ǿ��̻� ����

- �Ǿ��̻��� �ּ�8�� �̻�

- �Ǿ��̻��� ���ȴ��� �ȹ��ȴ����� ���� Ȯ���� �����ؾ��Ѵ�.

- �ʼ� : �Ǿ��̻��� ������ �ִϸ��̼� ����

*/