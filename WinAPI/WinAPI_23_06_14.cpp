#include "Stdafx.h"
#include "MainGame4.h"
HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void setWindowSize(int x, int y, int width, int hight);

MainGame4* _mg;
//_currentScene �� ����nullptr

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hProvInstance, LPSTR lpszCmdstr, int nCmdShow)
{
	_mg = new MainGame4(); //���� �� ������ �Ҵ��ض�.
	
	_hInstance = hInstance;

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = WINNAME;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	//���� assert�� ���ڸ� ���⼭ �� �� �ְڴ�.
	//HRESULT hr; 
	//hr = RegisterClass(&wndClass);
	//assert(SUCCEEDED(hr));
	RegisterClass(&wndClass);

#ifdef FULLSCREEN
	//����̽� ��� ����ü(ȭ�� ���÷��� ���� ����ü)
	DEVMODE dm;
	ZeroMemory(&dm, sizeof(DEVMODE));

	dm.dmSize = sizeof(DEVMODE);
	dm.dmBitsPerPel = 32; //32��Ʈ Ʈ���÷�
	dm.dmPanningWidth = 1920;		//����
	dm.dmPelsHeight = 1080;			//����
	dm.dmDisplayFrequency = 60; // �ֻ���(60hz)


	//�ʵ弳��
	dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

	if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		ChangeDisplaySettings(&dm, 0);
	}

	_hWnd = CreateWindow(
		WINNAME,
		WINNAME,
		WS_OVERLAPPEDWINDOW,
		WINSTART_X,
		WINSTART_Y,
		WINSIZE_X,
		WINSIZE_Y,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);
#else
	_hWnd = CreateWindow(
		WINNAME,
		WINNAME,
		WS_OVERLAPPEDWINDOW,
		WINSTART_X,
		WINSTART_Y,
		WINSIZE_X,
		WINSIZE_Y,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);
#endif
	setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);
	ShowWindow(_hWnd, nCmdShow);

	if (FAILED(_mg->init())) //FAILED : mg�� �ʱ�ȭ�� �����Ұ�� Ʈ���ȯ �� ����
	{
		return 0;
	}

	MSG message;
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	_mg->release();
	UnregisterClass(WINNAME, hInstance); //�����ֱ�

	return (int)message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg->MainProc(hWnd, iMessage, wParam, lParam); 
	// init�Լ� ����
}



void setWindowSize(int x, int y, int width, int hight)
{
	RECT rc = { 0,0,width,hight };

	AdjustWindowRect(&rc, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);

}

/*
����1. ���콺�� ������ ���� ���

- ���콺�� Ŭ���� ��ǥ�� ������ ������ ����Ѵ�.

- ������ ũ�� + ������ ��� + ������ �������� ��� ������ ó���Ѵ�

- ������ ���� : �簢��,��,�ﰢ�� �� �ٰ���

�� �ﰢ�� + �ٰ��� - > Polygon() + �迭�� �̿��Ѵ�.


(2���ִ°���)
����2. ������ Ȱ���� �� �� �׷����� ����

- ������ Ȱ���Ѵ�.
�� Ư¡�� �� �츮��


����3. ��ƨ���

- ū �簢�� �ȿ� ���� ���� �ִ�

- ���� ���� ū �簢�� �ȿ��� ������� �� �ٸ� �Է��� ��� �簢�� �鿡 ƨ��鼭
 ���������� �����δ�.

 - ū �簢���� Ű���� ����Ű �Է��� ������ ũ�⸦ �ø��ų� ���ϼ� �ִ�.

 - ũ�Ⱑ �þ�ų� �پ��� �翬�� ���ʿ��ִ� ���� �� �� ������ �޴´�.

 - ���콺 ��Ŭ���� : ���� �� �ӵ� ����

 - ���콺 ��Ŭ���� : ���� �� �ӵ� ����


 �� ��������

 -GetAsyncKeyState ����
 (���°����� ����)


*/

/*
����1. ī�� ¦���߱�

- ������ : 5 x 4

- ī��¦�� ���߸� ���� ī��� ��� ���µǾ�� �Ѵ�.

- ġƮ �ʼ�
�� 1. ���� ������ �����ð� �� �ٽ� ���߱�
�� 2. �� ���� �����ϰ� �������� ���� ���µǰ� ������ 1���� ���߸鼭 ����

�� HBRUSH ������ ������ ���� �� �ִ�.

*/

/*
����1. �δ�������

- �δ��� ���� �ּ�8������

- ȭ�鿡 ���� ������ ǥ���Ѵ�

- ���� ó�� : �δ����� 1�� Ŭ���ϸ� ��������
				�� ���ĵδ����� ����������� ��Ŭ���� �ص� ������ ������ �ȵȴ�.

����2. Ŭ���̻��

- �� / �쿡�� �������� �����ϴ� Ÿ���� ���콺�� �����Ѵ�.

- Ÿ���� �����ϸ� ����ȹ��, ���ŵ� Ÿ���� ���ڸ����� �ٷ� ��������

-�����ϴ� Ÿ���� ������ ������ ����ó��
(�簢�� 50�� ��-100�� �ٰ���100��)

- ���ӽð��� 60�ʷ� �����ϰ� �ð��� �� �ǰų� �� ������ 5000���� �Ǹ� ���� ����

Ÿ�Ӿ���. API ������ ��ũ

- ����ȭ�� ���� ���ΰ��� Ŭ������ ��������� Ű �Ŵ����� ���� ��Ʈ�� �����̴� ��Ʈ����.
*/