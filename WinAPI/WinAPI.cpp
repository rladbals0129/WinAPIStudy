#include "Stdafx.h"
#pragma region WinAPI
/*
▶ API
- 운영체제가 응용 프로그램 개발을 위해 제공하는 함수의 집합

- 명령어의 집합으로 어플리케이션 프로그램에서 오퍼레이팅 시스템의 기본적인 기능을 사용할 필요가 
있을 경우 API에서 명령어 호출이 진행된다.

ex) 하드웨어 -------------- 운영체제 (windows) ---------------- 응용프로그램
( API 함수 ) 

▷ 장점

- 운영체제가 같으면 같은 기능의 집합을 사용하기에 확장성 및 연동성, 그리고 유지보수면에서 아주 유리하다. (규격화된 틀이 있기떄문)
  (윈도우즈 != 리눅스)   ex)합을 맞춘적이없는 두 개발자가 winapi를 이용해 개발을 해도 둘다써봤다면 합이맞는다

- 운영체제에 종속되기 때문에 개발 확장성이 아주 좋다. (게임)


▷ 단점

- 플랫폼에 고착화
	ㄴ c언어 개발

▶ API 구조

- 크게 진입점과 메세지 루프, Window Procedure로 나뉜다.



*/
#pragma endregion

#include <Windows.h>


#include <tchar.h>

//TCHAR* pszString = _T("Windows API");
/*
▶ TCHAR

- TCHAR형은 프로젝트의 문자셋 설정에 따라 자동적으로 char 또는 wchar_t 로 Type_Casting되는 중간 매크로 자료형

- 멀티바이트와 유니코드 환경에서 별도의 수정 작업 없이 프로그램을 구동하기 위해서는 TCHAR 형으로 문자열을 표현할 것을 추천
(근본적인 코딩 언어는 영어, 그렇지만 시대가 지남에 따라 한국 러시아 일본 중국 등등 세계적으로 코딩을 하기때문에
언어에 대한 확장성떄문에 TCHAR를 사용한다)

- 일반적으로 윈도우 응용 프로그램에서 문자열 상수를 쓰기 위해서는 중간 설정에 따라
char* 또는 wchar_t* 로 변환해주는 _T 매크로를 써야된다.




*/
/*
LPSTR		-> Long Pointer  = char*  
LPCSTR		-> Long Pointer Constant = const char*
LPCTSTR		-> Long Pointer Constant t_string = const tchar* (매크로를 의미하는 t)
*/

/*
▶ 인스턴스
- 윈도우 OS가 현재 실행되고 있는 프로그램을 확인하기 위한 값
- 기본적으로 같은 프로그램이면 같은 인스턴스 값을 가진다.
- 클래스가 메모리에 실제로 구현된 실체
ㄴ 실행되고 있는 각각의 프로그램을 인스턴스라고 할 수 있다.
*/
//전역변수
HINSTANCE _hInstance; //인스턴스
HWND _hWnd; //윈도우 핸들
POINT _ptMouse = { 0,0 };
//LPTSTR _lpszClass = TEXT("Windows API"); //윈도우 타이틀

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); //콜백함수
void setWindowSize(int x, int y, int width, int hight); //클라이언스 사이즈 잡기
RECT rc;
RECT _rc1, _rc2;
/*
hInstance: 프로그램 인스턴스 핸들
hPrevInstance: 이전에 실행된 인스턴스 핸들
lpszCmdParam: 명령형으로 입력된 프로그램 인수
nCmdShow: 프로그램이 시작될 형태 (최소화 / 크기 등등)

*/
/*
//문자셋
int APIENTRY _tWinMain(HINSTANCE hInstance,				
	HINSTANCE hPrevInstance,
	TCHAR* lpszCmdParam,			//멀티바이트,유니코드
	int nCmdShow);
	*/

//사각형 중심점 만들기



int APIENTRY WinMain(HINSTANCE hInstance,					//진입점
                      HINSTANCE hPrevInstance,
                      LPSTR lpszCmdParam,
                      int nCmdShow)
{
    //인스턴스를 전역 변수에 담아둔다.
	_hInstance = hInstance;

	/*
	- WinMain의 역활

	1. 윈도우 창을 세팅 후 화면에 띄우기
		ㄴ 화면에 창을 띄우기 위해서는 4가지를 모두 처리해야 한다.
		1-1
		1-2
		1-3
		1-4


	2. 메세지 루프
	
	
	*/  
	// 1-1. 윈도우창 구조체 선언 및 초기화
	// WNDCLASS : 이 구조체는 윈도우즈 운영체제에서 윈도우 생성을 명령하기 위해서
	// 커스텀한 윈도우를 식별할 수 있는 정보 등을 기록하는 역활을 수행한다.
	WNDCLASS wndClass;

	wndClass.cbClsExtra = 0;										//클래스 여분 메모리
	wndClass.cbWndExtra = 0;										//윈도우 여분 메모리
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//백그라운드
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					// 마우스 커서
	wndClass.hIcon = LoadIcon(NULL,IDI_APPLICATION);				// 아이콘
	wndClass.hInstance = hInstance;									// 윈도우를 소요한 프로그램의 식별자 정보
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						// 윈도우 프로시져
	wndClass.lpszClassName = WINNAME;							// 클래스이름(식별자정보)
	wndClass.lpszMenuName = NULL;									// 메뉴 이름
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						// 윈도우 스타일(다시 그리기 정보)
	
	//1-2 윈도우 클래스 등록
	RegisterClass(&wndClass);

	//1-3 화면에 보여줄 윈도우 창 생성
	_hWnd = CreateWindow
	(
		WINNAME,					// 윈도우 클래스 식별자
		WINNAME,					// 윈도우 타이틀 바 이름
		WS_OVERLAPPEDWINDOW,		// 윈도우 스타일
		WINSTART_X,						// 윈도우 화면x좌표
		WINSTART_Y,						// 윈도우 화면y좌표
		WINSIZE_X,						// 윈도우 화면 가로 크기
		WINSIZE_Y,						// 윈도우 화면 세로 크기
		NULL,						// 부모 윈도우 - GetDesktopWindow
		(HMENU)NULL,				// 메뉴 핸들
		hInstance,					// 인스턴스 지정
		NULL						// 윈도우의 자식 윈도우를 생성하면 지정하고 그렇지않다면 NULL을 잡아라
		

	);
	//클라이언트 영역의 사이즈를 정확히 잡아주기 위해
	setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);
	//1-4 화면에 윈도우창 보여주기
	ShowWindow(_hWnd, nCmdShow);

	// 단일 프로잭트 (단기테스트/과제)업데이트 처리 해야 한다
	//UpdateWindow(_hWnd);

	//2. 메세지 루프
	// MSG : 운영체제에서 발생하는 메세지 정보를 저장하기 위한 구조체
	MSG message;
	//ZeroMemory(&message, sizeof(message)); //Update를했다면 반드시 제로메모리도쓸것
	/*while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}*/
   
	/*
	★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
	▶ 메세지 루프 종류
	1. GetMessage				
	ㄴ 메세지를 꺼내올 수 있을 때 까지 멈춰 있는 함수 (대기)
	ㄴ GetMessage는 메세지 큐로부터 하나의 메세지를 가져오는 역활을 수행한다
	ㄴ 단 , 메세지 큐가 비어있을 경우 메세지가(발생한 메세지x) 들어올때까지 대기한다


	2. PeekMessage             - 게임은 기본적으로 이것에 기반한다. (플레이어가 라면먹으면서 잠수타도 게임은돌아간다)
	ㄴ 메세지가 없더라도 반환되는 함수

	*/
    while (GetMessage(&message, 0, 0, 0))   //윈도우랑 소통
    {      
          TranslateMessage(&message);
          DispatchMessage(&message);
    }
	/*
	
	TranslateMessage(&message);
	ㄴ 키보드의 입력 메세지 처리를 담당				->필수. 얘없으면 키보드 쓸 수 없음
	ㄴ 입력된 키가 문자키인지 확인 후 대문자,소문자,한글/영문 인지에 대해 WM_CHAR 메세지를 발생시킨다.

    DispatchMessage(&message);
	ㄴ 윈도우 프로시져에서 전달된 메세지를 실제 윈도우로 전달해준다.
	*/

    return (int) message.wParam;
}

/*
hWnd: 어느 윈도우에서 발생한 메세지인지 구분
iMessage: 메세지 구분 번호
wParam: unsigned int -> 마우스 처리 담당, 키보드 조합키의 상태를 전달 (매개변수)
lParam: unsigned long -> 마우스 클릭 좌표를 전달

*/
//윈도우 메세지를 처리하는 역할
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	/*
	▶ Window Procedure
	ㄴ 메세지를 운영체제에 전달 -> 강제로 운영체제가 호출되게 해준다.
	ㄴ WinMain()이 아닌 운영체제에 의해 호출이되는 콜백(Callback) 함수
	ㄴ 윈도우를 생성할때 반드시 지정을 해줘야한다.

	- 기억해야 할건 윈도우 프로시저 내부에서는 윈도우에서 발생한 모든 메세지를 처리하는 것이 아니라
	특정 메세지만을 처리하고 나머지 메세지는 DefWindowProc라는 함수가 처리하도록 로직을 설계하는게 일반적이다.

	※ 위 내용은 반드시 기억할것.
	*/

	HDC hdc;				// 핸들DC
	PAINTSTRUCT ps;			// 페인트 구조체

	static POINT pt = { 0,0 };
	char strPT[128];

	char str[] = "그래";
	//RECT rc = { 100,100,200,200 };
	/*
	▶ RECT: 사각형의 좌표를 저장하기 위한 구조체
		ㄴLPRECT,PRECT도 기억

	
	
	*/




	/*
	char[]: 수정이 가능하다 -> 배열이기때문에 하나 하나 다 접근 가능
	char* : 수정이 불가능 -> 첫번째 메모리 주소값만 불러오는 참조char
	
	*/

    switch (iMessage)	//당분간 코딩은 여기서 하자
    {
	case WM_CREATE:		//생성자 (초기화)
		_rc1 = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 100, 100);
		_rc2 = RectMakeCenter(WINSIZE_X / 2 + 200, 400, 100, 100);
		break;


		/*
		▶WM_PAINT
		
		-윈도우를 다시 그려야 할때 사용하는 메세지

		1. 윈도우가 처음 만들어졌을때
		2. 윈도우 크기를 조절하고 싶을때
		3. 윈도우가 다른 윈도우에 가려졌다가 다시 보일때
		4. 특정 함수가 호출이 될때 -> InvalidateRect,Invalidate,UpdataAllViews등등...
				ㄴ 기본적으로 랜더링 관련된 함수가 나오면 PAINT를 떠올려야 한다.
		*/
	case WM_PAINT:			//출력에 관한 모든것을 담당한다.(문자,그림,도형 등등 화면에 보이는 모든것들)
		hdc = BeginPaint(hWnd, &ps);
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
		wsprintf(strPT, "x: %d    y: %d", pt.x, pt.y);
		TextOut(hdc, 10, 10, strPT, strlen(strPT));

		Rectangle(hdc, _rc1.left, _rc1.top, _rc1.right, _rc1.bottom);
		DrawRectMake(hdc, _rc2);

		//EllipaseMakeCenter(hdc, WINSIZE_X / 2, WINSIZE_Y / 2, 100, 100);
		//Ellipse(hdc, 300, 100, 200, 200);	//원을 그리는 함수


		

		

		//Rectangle(hdc, 100, 100, 200, 200);	//사각형을 그리는 함수 상수보단 아래처럼
	//	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

		//데크르트 좌표 != 윈도우 좌표
		// 윈도우좌표계는 y축이 반대다.

		//TextOut(hdc, 300, 300, "과제가 너무 재밌다^^", strlen("과제가 너무 재밌다^^"));
		// ㄴ TextOut(어떤dc, 좌표x ,좌표y, 출력할 텍스트 ,출력이될 문자열 버퍼)  문자출력
		//  ㄴ strle은 할당받은 메모리에 바인딩 된 문자열에서 NULL값을 제외한 문자열 길이
		/*
		strcpy(x,y): y를 x에 복사
		strcat(x,y): x문자열 + y문자열
		strlen(x,y): 문자열 길이
		strcmp(x,y): 두 문자열이 같은지 확인
		ㄴ 같을시 0 리턴 y가 크면 -1리턴 x가크면 1리턴

		strcpy  -> wcscpy	->	_tcscpy
		strcat  -> wcscat	->	_tcscat
		strlen  -> wcslen	->	_tcslen
		strcmp  -> wcscmp	->	_tcscmp							->기능은 똑같다.
		strtok	-> wcstok	->  _tcstok		문자열 자르기
		strchr	-> wcschr	->  _tcschr		문자 찾기
		strstr	-> wcsstr	->  _tcsstr		문자열 찾기
		*/
		//문자열 글자 색 변경
		//SetTextColor(hdc, RGB(255, 0, 0));
		//TextOut(hdc, 300, 400, "과제 좀 더 내주세요.", strlen("과제 좀 더 내주세요."));

		/*MoveToEx(hdc, 400, 400, NULL);
		LineTo(hdc, 200, 400);

		MoveToEx(hdc, 400, 400, NULL);
		LineTo(hdc, 200, 200);
		
		
		MoveToEx(hdc, 400, 400, NULL);
		LineTo(hdc, 200, 400);*/
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);

		InvalidateRect(hWnd, NULL, true);

		break;
	case WM_LBUTTONDOWN:			//마우스 왼쪽 버튼이 눌렀을때 메세지가 발생한다
	
		//InvalidateRect(hWnd,NULL,t/f);
		 

	    break;
	case WM_RBUTTONDOWN:

		break;
	case WM_KEYDOWN:		//키보드 입력

		switch (wParam)
		{
		case VK_LEFT:
			break;
		case VK_RIGHT:
			break;
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}

		break;
    case WM_DESTROY:	//소멸자
        PostQuitMessage(0);//이 함수는 메세지 큐에 Quit 메세지를 보내는 역활을 한다.
		// 즉, Quit 메세지를 수신하는 순간 GetMessage함수가 FALSE를 반환하므로 루프가 종료된다.
        return 0;
		//윈도우 프로시져에서 처리되지 않은 나머지 메세지를 처리해 준다.

	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

void setWindowSize(int x, int y, int width, int hight)
{
	RECT rc = { 0,0,width,hight };

	AdjustWindowRect(&rc, WINSTYLE, false);
	//AdjustWindowRect(): RECT구조체,윈도우스타일,메뉴여부
	
	//얻어온 렉트의 정보로 윈도우 사이즈를 세팅하겠다.
	SetWindowPos(_hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);
	//		ㄴ 2d z축 렌더링기법 (ZORDER) 
}


/*
2023/06.08
-------------------------------------------------------------------------------
과제1. 구구단

	- 예외처리 필수: 구구단의 본질(1단이하x /9단이상x)

	- 마우스 왼쪽 클릭을 했을 시 1단씩 생기고, 우클릭을하면 한단씩 지워진다.
	ㄴ 3단씩 개행한다.
---------------------------------------------------------------------------------
과제2. WinAPI 출력

- MoveToEx() + LineTo()를 이용한다.

★ 도형 관련 함수 사용 금지.

- 1. 자기 이름 출력 (한글)

- 2. Unreal Engine (영문)

마우스 왼쪽을 누르면 한글자씩 출력이 되며 우클릭을 하면 한글자씩 지워진다.
'ㅇ' 을 어떻게 처리해야 할까?? 반복문??? 곡선처리 고민해보자.
ㄴ 원의 법칙을떠올리자(수학) 베지에 곡선

- 현재 창 크기 기준 절반 이상의 사이즈로 해온다.
-------------------------------------------------------------------------

2023.06,09

과제1. 오망성 출력

- 오망성을 마법진처럼 만들어 온다.

- 양식은 자유지만 본인이 생각했을때 가장 효율적인 방법으로
	ㄴ 특히 배열은 무조건 사용한다. (짝대기)

과제2.애플 로고 출력 

- 사이즈는 화면의 절반사이즈 

- SetPixel을 이용해서 찍는다 (효율적인 반복문)

힌트 : 원을쓰면 생각보다 외형 따기 쉽다. Ellipse

과제3. 사각형 이동

- 방향키를 통해 사각형을 움직인다.

- 예외처리: 사각형은 화면 밖으로 나갈 수 없다. (800 조금넘어가는건 감안)

과제4. 사각형 2개 움직이기

- 총 사각형 갯수: 2개

- 하나는 움직일 수 있는 사각형 / 다른하나는 움직일수 없는 사각형.

- 움직일 수 없는 사각형을 움직일 수 있는 사각형이 밀어낼 수 있으면 된다.

- 예외처리: 2개의 사각형은 화면 밖으로 나갈 수 없다

- 2개의 사각형을 초기 위치로 돌리는 기능도 추가한다.

※ 별다른 언급을 하기 전까지는 충돌함수 사용 금지. (조건식)



한줄조사.

----------------------------------------------------------------

2023.06.12

과제1. 사각형 영혼 밀어넣기

-시작은 큰 사각형2개와 작은사각형 1개

-내가 움직일 수 있는 사각형 안에는 작은 사각형이 들어있다.

-큰 사각형을 움직이면 작은 사각형 역시 움직이는 버전1개/움직이지 않는 버전 1개
ㄴ 총 2가지버전
ㄴ 예외처리: 작은 사각형은 큰 사각형을 벗어날 수 없다.

-큰 사각형끼리 충돌이되면 작은사각형은 충돌이 된 반대편 사각형으로 이동한다.

※ 움직일 수 있는 주도권은 작은 사각형을 가지고 있는 "큰 사각형"
예외처리: 큰 사각형 끼리의 모서리에 대한 정밀도를 처리한다.

----------------------------------------------------------------------
2023.06.13

과제1. 사각형 드래그 이동

- 마우스로 사각형을 자유롭게 움직일 수 있으면 된다.

※ T / F (클릭여부) (화면 밖으로 마우스가 넘어갔을때도 t/f가 바뀌는거 신경쓰기 ->바뀌어야 함)

과제2. 마우스로 사각형의 크기를 자유롭게 조절 할 수 있으면 된다.

- 바탕화면에서 드래그 해보면서 똑같이 만들면 ok

과제3. 사각형 4단 밀기  (1)

- 사각형의 갯수는 총 4개

- 마우스로 화면에 그려진 4개의 사각형중 아무거나 선택해 자유롭게 움직인다. 

- 마우스로 움직이고 있는 사각형이 다른 사각형과 충돌되면 충돌된 사각형은 자연스럽게 밀려난다

※ 관성 / 그럴싸해보이게 (힘)
ㄴ 에어하키

한줄조사. 디자인패턴 조사하기
- 싱글톤 + @ 4개
*/


