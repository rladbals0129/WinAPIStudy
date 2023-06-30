#include "Stdafx.h"
#include "MainGame2.h"

HRESULT MainGame2::init(void)
{
	GameNode::init();
	
	_bgImage = new GImage;
	_bgImage->init("Resources/Images/BackGround/DeadSpace.bmp", WINSIZE_X, WINSIZE_Y);
	_plImage = new GImage;
	_plImage->init("Resources/Images/Object/Airplane.bmp", 173 , 291 , true, RGB(255, 0, 255));
	_rc = RectMakeCenter(WINSIZE_X / 2 - 500, WINSIZE_Y / 2 + 200,173 , 291);

	_radian = 3.141592f;
	_degree = 180;

	for (int i = 0; i < 5; ++i)
	{
		_star[i].x = cosf((i * 72 - 90)*PI / 180.0f) * 200 + WINSIZE_X / 2; //ù ��ǥ�� 12�ù������� ��������.
		_star[i].y = sinf((i * 72 - 90)*PI / 180.0f) * 200 + WINSIZE_Y / 2;
	}
	/*
	�������� �׸��� ���� ����Ʈ 5��
	�� 72 <- 360 / 5

	-90?? -> �ʱ� ����

	pi / 180 ��׸�->����

	200 -> �߽��� �Ÿ�

	WINSIZE_X,Y ����
	*/
	return S_OK;
}

void MainGame2::release(void)
{
	GameNode::release();
	SAFE_DELETE(_bgImage);
	SAFE_DELETE(_plImage);
}

void MainGame2::update(void)
{
	GameNode::update();
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (MessageBox(_hWnd, "������ �����Ͻðڽ��ϱ�?", "���� Ȯ��", MB_OKCANCEL) == IDOK)
		{
			PostQuitMessage(0);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && WINSIZE_X > _rc.right)
	{
		_rc.left += 5.0f;
		_rc.right += 5.0f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && 0 < _rc.left)
	{
		_rc.left -= 5.0f;
		_rc.right -= 5.0f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && 0 < _rc.top)
	{
		_rc.top -= 5.0f;
		_rc.bottom -= 5.0f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && WINSIZE_Y > _rc.bottom)
	{
		_rc.top += 5.0f;
		_rc.bottom += 5.0f;
	}

	GetLocalTime(&_st);
	_st.wSecond;
}

void MainGame2::render(HDC hdc)
{
	GameNode::render(hdc);
	HDC memDC = this->getDoubleBuffer()->getMemDC();
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS); //�簢���ȿ� ������ �귯���� ä��� �Լ�

	//=====================================================��������
	
	_bgImage->render(memDC, 0, 0);
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(memDC, _rc.left, _rc.top, _rc.right, _rc.bottom);

	}
	_plImage->render(memDC, _rc.left, _rc.top);


	//char strRadian[180];
	//char strDegree[180];
	//char strSecond[128];

	//sprintf_s(strSecond, "%d ��", _st.wSecond);
	//TextOut(memDC, WINSIZE_X/2 , 100, strSecond, strlen(strSecond));

	//sprintf_s(strRadian, "%.2f ���� ���� %.2f ��׸� ���� ����", _radian, _radian*(180.0f / M_PI));
	//TextOut(memDC, WINSIZE_X / 2 - 100, WINSIZE_Y / 2 - 100, strRadian, strlen(strRadian));

	////��ۿ��� ��������
	//sprintf_s(strDegree, "%.2f ��� ���� %.2f ���� ���� ����", _degree, _degree * (PI / 180.0f));
	//TextOut(memDC, WINSIZE_X / 2 - 100, WINSIZE_Y / 2, strDegree, strlen(strDegree));

	//HPEN pen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	//HPEN currentPen;

	//currentPen = (HPEN)SelectObject(memDC, pen);

	//LineMake(memDC, WINSIZE_X / 2 - 100, WINSIZE_Y / 2 + 100, WINSIZE_X + 200, WINSIZE_Y + 100);
	//DeleteObject(pen);



	//SetPixel(memDC, _star[0].x, _star[0].y, RGB(255, 0, 0));

	//EllipaseMakeCenter(memDC, _star[0].x, _star[0].y, 10, 10);

	//for (int i = 0; i < 5; i++)
	//{
	//	EllipaseMakeCenter(memDC, _star[i].x, _star[i].y, 10, 10);
	//}
	//=======================================================
	this->getDoubleBuffer()->render(hdc, 0, 0);


	//���ȿ��� ��׸���

	//1���� = 180 / pi degress

}

MainGame2::MainGame2()
{
}


MainGame2::~MainGame2()
{
}
/*
�̹��� �߰� ����1. �δ�������

- ��Ȳ�� �´� �̹����� �ʼ������� �����Ѵ�

- �δ����� ������, /�������� / �������� / ��ġ (���,��������)

�� ���콺Ŀ���� ShowCursor()�� �̿��Ѵ�

����1. Ʋ���׸�ã��

- �̹����� ���伥 ���� / �˻����� ó���Ѵ�

- ���������� �� 2���� ��������

- Ʋ������ 5���̻�

- ������ ���۵Ǹ� Ÿ�Ӱ������� ���� �پ��� �߸�Ŭ���ϸ� �������� ���ҵȴ�

- Ʋ������ ���߸� Ÿ�Ӱ������� ����

- Ÿ�Ӱ������� ��� �����Ǹ� Ÿ�ӿ��� �޼����� ȭ�鿡 ���� ���� ���Ḧ ��Ų��.

����2. ���� ������ ���� �Ѿ˹߻�

- ����ó�� : ���� �ޱ��� �����ش� -> ȭ������� �������ʴ´�

�ʼ� : ����/�ڵ����� -> �� 2������

����3. �߻�� �Ѿ˳��� �浹�̵ȴ�.

-�ٽɿ�� : �Ѿ˳��� �浹�̵Ǹ� �ڿ������� ƨ�ܳ������Ѵ� (���ﰢ�Լ��� ����غ���)

����4. �߻��� �Ѿ˿� �߷��� ����

- �Ѿ��� �߷��� �޾� ��������. -> ���� ���ϸ�

�� �߻�� �Ѿ� ����ó��
�� 4�������� �����ϰ�
���߻�� �Ѿ��� ȭ������� ���� �� ����.
�� ���ǻ���: �߻�� �Ѿ��� ȭ�� ������ ��� ƨ�ܳ����� ������ �Ű澴��.

�������� 1��. ����ȸ��

- �簢���� ȸ����Ų��

- hdc�� ���� �׷��´�
�� winAPI�� Ȱ���� ����

- ȭ������ �ٲ� ���¸� ��� ��ǥ�� �̵��ϰ� ������ �Ѵ�.

����3. ���伥��ġ

-CS6



*/


/*
���� 1�� �Ƴ��α� �ð�

- ��ħ / ��ħ / ��ħ
- ���� ����� SYSTEMTIME�� �̿��ؼ� �����
- �ʼ�: �ð�ǥ��


*/
