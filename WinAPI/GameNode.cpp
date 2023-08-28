#include "Stdafx.h"
#include "GameNode.h"


HRESULT GameNode::init(void)
{
	return S_OK; //함수가 성공적으로 실행되었음을 알리는 S_OK
}

HRESULT GameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;


	if (managerInit)
	{
		// 로케일 설정
		//ㄴ 프로그램의 명령어가 여러가지 언어로 주어져 있는 경우 이중에 어떤 언어의 것을 
		// 출력할것인지에 대한 설정
		// ***** 파일불러올때 한글명있어도 읽어들일수있다.
		setlocale(LC_ALL, "korean");

		SetTimer(_hWnd, 1, 10, NULL); //타이머 초기화

		RND->init();
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TEMPSOUNDMANAGER->init();
		TIMEMANAGER->init();
		SCENEMANAGER->init();
	}
	
	return S_OK;
}

void GameNode::release(void)
{
	//동적할당과 같이 삭제하지 않고 종료하면 메모리줄줄줄 샌다.
	
	if(_managerInit)
	{ 
		KillTimer(_hWnd, 1);

		RND->releaseSingleton();
		KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		TEMPSOUNDMANAGER->releaseSingleton();
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
	}
	ReleaseDC(_hWnd, _hdc);

}

void GameNode::update(void)
{
	//InvalidateRect(_hWnd, NULL, false);
}

void GameNode::render(void)
{
	// ?.? 설계단계에서 건들면 안됨
	// 그려지는 영역은 자식객체의 고유이기때문에 여기서 그려주면 안됨
	// 사용할수있게끔 추생객체로만 만들어두고 자식에게 넘긴다.
}
//메인 프로시저
LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_TIMER:
	this->update();
	break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		this->render();

		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
	case WM_LBUTTONDOWN:

		break;
	case WM_KEYDOWN:
		switch (wParam)
		{

		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);

	
}

GameNode::~GameNode()
{
	//!NO
}
