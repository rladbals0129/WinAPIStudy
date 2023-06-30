#include "Stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void)
{
	GameNode::init();

	_currentRect = CURRENTRECT_NULL; //1.초기값 지정

	for (int i = 0; i < 2; i++)	//두더지가 없으면 뭐든 게임이 성립이 안되니 두더지의 위치붵 초기화했다. 그다음은 어디를해야될까?
	{							//랜더링을 처리하면되겠다.
		for (int j = 0; j < 4; j++)
		{
			_rc[i * 4 + j] = RectMakeCenter(100 + j * 200, 200 + i * 200, 100, 100); //두더지 위치 지정
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

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) //클릭되면 스코어를 올리고 원스체크를 트루로
	{
		/*if (_rc[0].right > _ptMouse.x &&
			_rc[0].left < _ptMouse.x&&
			_rc[0].left < _ptMouse.x && _bIsOnceCheck)
		{

		}*/

		//PtInRect(): 렉트 안에 POINT(X,Y)가 있는지 검사사하여 포인트가 사각형안에 있으면 true를 반환하는 함수
		//앞으로는 이것을 쓰자.
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

void MainGame::render(HDC hdc) //2. 초기화하고 랜더링을 처리해줬다. 
{

	for (int i = 0; i < 8; i++) //두더지랜더
	{
		Rectangle(hdc, _rc[i].left, _rc[i].top, _rc[i].right, _rc[i].bottom);
	}

	char strScore[128];

	wsprintf(strScore, "Score : %d", _score);
	TextOut(hdc, 50, 100, strScore, strlen(strScore));

	if (_bIsSelected) //두더지가 선택되면 색상 업데이트
	{
		int r = RND->getInt(256);
		int g = RND->getInt(256);
		int b = RND->getInt(256);
		HBRUSH brush = CreateSolidBrush(RGB(r, g, b));
		FillRect(hdc, &_rc[_index], brush);
		// 이런식으로 DC를 직접 건들이는 함수는 누수가 생긴다.
		// 따라서 delete로 찝어서 날려줘야함.
		DeleteObject(brush);
	}
	//_mole->render(hdc);

	/*if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	}*/

}

/*

- 주말 과제 제출

ㄴ 언리얼 1기_얼굴 그리기_김유민
ㄴ 내일오전9시
 ㄴ 오늘과제 포함

과제1. 똥피하기

- 시작 버튼을 누르면서 게임 시작

- 게임이 시작되고 플레이어가 죽을때까지 버틴 시간을 화면에 출력한다.

필수 : 재시작 + 다시하기

- 플레이어는 사람모양으로 좌우 모양이 다르게 구현

과제2. 총알 발사

- 하단에서 좌우로 움직일 수 있는 플레이어가 존재

- 스페이스바를 누르면 플레이어가 총알을 발사한다.

과제3. 악어이빨 게임

- 악어이빨은 최소8개 이상

- 악어이빨에 물렸는지 안물렸는지에 대해 확인이 가능해야한다.

- 필수 : 악어이빨이 닫히는 애니메이션 구현

*/