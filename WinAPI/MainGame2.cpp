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
		_star[i].x = cosf((i * 72 - 90)*PI / 180.0f) * 200 + WINSIZE_X / 2; //첫 좌표를 12시방향으로 잡으려고.
		_star[i].y = sinf((i * 72 - 90)*PI / 180.0f) * 200 + WINSIZE_Y / 2;
	}
	/*
	오망성을 그리기 위한 포인트 5개
	ㄴ 72 <- 360 / 5

	-90?? -> 초기 각도

	pi / 180 디그리->라디안

	200 -> 중심의 거리

	WINSIZE_X,Y 중점
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
		if (MessageBox(_hWnd, "게임을 종료하시겠습니까?", "종료 확인", MB_OKCANCEL) == IDOK)
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
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS); //사각형안에 영역을 브러쉬로 채우는 함수

	//=====================================================지우지마
	
	_bgImage->render(memDC, 0, 0);
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(memDC, _rc.left, _rc.top, _rc.right, _rc.bottom);

	}
	_plImage->render(memDC, _rc.left, _rc.top);


	//char strRadian[180];
	//char strDegree[180];
	//char strSecond[128];

	//sprintf_s(strSecond, "%d 초", _st.wSecond);
	//TextOut(memDC, WINSIZE_X/2 , 100, strSecond, strlen(strSecond));

	//sprintf_s(strRadian, "%.2f 라디안 값은 %.2f 디그리 값과 같다", _radian, _radian*(180.0f / M_PI));
	//TextOut(memDC, WINSIZE_X / 2 - 100, WINSIZE_Y / 2 - 100, strRadian, strlen(strRadian));

	////디글에서 라디안으로
	//sprintf_s(strDegree, "%.2f 디글 값은 %.2f 라디안 값과 같다", _degree, _degree * (PI / 180.0f));
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


	//라디안에서 디그리로

	//1라디안 = 180 / pi degress

}

MainGame2::MainGame2()
{
}


MainGame2::~MainGame2()
{
}
/*
이미지 추가 과제1. 두더지게임

- 상황에 맞는 이미지를 필수적으로 적용한다

- 두더지가 없을때, /나왔을때 / 때렸을때 / 망치 (대기,때렸을떄)

※ 마우스커서는 ShowCursor()를 이용한다

과제1. 틀린그림찾기

- 이미지는 포토샵 편집 / 검색으로 처리한다

- 스테이지는 총 2개의 스테이지

- 틀린곳은 5개이상

- 게임이 시작되면 타임게이지가 점점 줄어들며 잘못클릭하면 게이지가 감소된다

- 틀린곳을 맞추면 타임게이지가 증가

- 타임게이지가 모두 소진되면 타임오버 메세지를 화면에 띄우며 게임 종료를 시킨다.

과제2. 포신 각도에 따른 총알발사

- 예외처리 : 포신 앵글을 막아준다 -> 화면밖으로 나가지않는다

필수 : 수동/자동버전 -> 총 2가지로

과제3. 발사된 총알끼리 충돌이된다.

-핵심요소 : 총알끼리 충돌이되면 자연스럽게 튕겨나가야한다 (역삼각함수를 사용해보자)

과제4. 발사한 총알에 중력을 적용

- 총알이 중력을 받아 떨어진다. -> 힘이 다하면

※ 발사된 총알 예외처리
ㄴ 4번과제를 제외하고
ㄴ발사된 총알은 화면밖으로 나갈 수 없다.
ㄴ 주의사항: 발사된 총알이 화면 끝점에 닿아 튕겨나갈때 각도에 신경쓴다.

도전과제 1번. 도형회전

- 사각형을 회전시킨다

- hdc를 통해 그려온다
ㄴ winAPI를 활용해 구현

- 화면축이 바뀐 상태면 상대 좌표로 이동하게 구현을 한다.

과제3. 포토샵설치

-CS6



*/


/*
과제 1번 아날로그 시계

- 초침 / 분침 / 시침
- 오늘 사용한 SYSTEMTIME을 이용해서 만든다
- 필수: 시간표시


*/
