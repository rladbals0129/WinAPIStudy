#include "Stdafx.h"
#include "MainGame4.h"
HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void setWindowSize(int x, int y, int width, int hight);

MainGame4* _mg;
//_currentScene 이 세팅nullptr

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hProvInstance, LPSTR lpszCmdstr, int nCmdShow)
{
	_mg = new MainGame4(); //나를 힙 영역에 할당해라.
	
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

	//굳이 assert를 쓰자면 여기서 쓸 수 있겠다.
	//HRESULT hr; 
	//hr = RegisterClass(&wndClass);
	//assert(SUCCEEDED(hr));
	RegisterClass(&wndClass);

#ifdef FULLSCREEN
	//디바이스 모드 구조체(화면 디스플레이 관련 구조체)
	DEVMODE dm;
	ZeroMemory(&dm, sizeof(DEVMODE));

	dm.dmSize = sizeof(DEVMODE);
	dm.dmBitsPerPel = 32; //32비트 트루컬러
	dm.dmPanningWidth = 1920;		//가로
	dm.dmPelsHeight = 1080;			//세로
	dm.dmDisplayFrequency = 60; // 주사율(60hz)


	//필드설정
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

	if (FAILED(_mg->init())) //FAILED : mg의 초기화가 실패할경우 트루반환 후 종료
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
	UnregisterClass(WINNAME, hInstance); //지워주기

	return (int)message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg->MainProc(hWnd, iMessage, wParam, lParam); 
	// init함수 실행
}



void setWindowSize(int x, int y, int width, int hight)
{
	RECT rc = { 0,0,width,hight };

	AdjustWindowRect(&rc, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);

}

/*
과제1. 마우스로 무작위 도형 출력

- 마우스로 클릭한 좌표에 무작위 도형을 출력한다.

- 도형의 크기 + 도형의 모양 + 도형의 종류까지 모두 무작위 처리한다

- 도형의 종류 : 사각형,원,삼각형 및 다각형

※ 삼각형 + 다각형 - > Polygon() + 배열을 이용한다.


(2일주는과제)
과제2. 도형을 활용한 내 얼굴 그려오기 ㅋㅋ

- 도형을 활용한다.
ㄴ 특징을 잘 살리자


과제3. 공튕기기

- 큰 사각형 안에 작은 공이 있다

- 작은 공은 큰 사각형 안에서 사용자의 별 다른 입력이 없어도 사각형 면에 튕기면서
 지속적으로 움직인다.

 - 큰 사각형은 키보드 방향키 입력을 받으며 크기를 늘리거나 줄일수 있다.

 - 크기가 늘어나거나 줄어들면 당연히 안쪽에있는 작은 공 도 영향을 받는다.

 - 마우스 왼클릭시 : 작은 공 속도 증가

 - 마우스 우클릭시 : 작은 공 속도 감소


 ※ 한줄조사

 -GetAsyncKeyState 조사
 (상태값까지 조사)


*/

/*
과제1. 카드 짝맞추기

- 사이즈 : 5 x 4

- 카드짝을 맞추면 맞춘 카드는 계속 오픈되어야 한다.

- 치트 필수
ㄴ 1. 전부 오픈후 일정시간 후 다시 감추기
ㄴ 2. 한 쌍을 제외하고 나머지는 전부 오픈되고 유저가 1쌍을 맞추면서 종료

※ HBRUSH 를쓰면 색상을 넣을 수 있다.

*/

/*
과제1. 두더지게임

- 두더지 수는 최소8마리ㅣ

- 화면에 현제 점수를 표기한다

- 예외 처리 : 두더지를 1번 클릭하면 점수증가
				ㄴ 이후두더지가 사라질떄까지 재클릭을 해도 점수가 오르면 안된다.

과제2. 클레이사격

- 좌 / 우에서 무작위로 출현하는 타겟을 마우스로 제거한다.

- 타겟을 제거하면 점수획득, 제거된 타겟은 그자리에서 바로 떨어진다

-등장하는 타겟의 종류는 무작위 도형처리
(사각형 50점 원-100점 다각형100점)

- 게임시간은 60초로 한정하고 시간이 다 되거나 내 점수가 5000점이 되면 게임 종료

타임어택. API 프레임 워크

- 가상화를 통해 메인게임 클레스가 만들어지고 키 매니저를 통해 렉트를 움직이는 파트까지.
*/