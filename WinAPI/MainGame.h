#pragma once
#include "GameNode.h"
#include "Example_Mole.h"
// 객체지향 프로그래밍-> 설계의 기반한 효율적인 방법론과 관리 체계
/*
과제가 두더지잡기 게임이다..

1. 두더지+맵
ㄴ 클래스분할..?
	ㄴ 상속? / 클래스 갯수? / STL이 필요한가?
		ㄴ 프레임워크가있으니 굳이 상속을 해야만 알려줄수있을까?? 아니면 다른 길이 있을까??

2. 체계(열거,클래스,구조체) 반드시 선행되어야함. 그래야 재사용성이 높아진다/ 확장성 유지보수
필요한것을 먼저 세팅을하고 구체화를 하자.

3. 구체화
     ㄴ PCH / 함수 -> 로직구현

*/


//0. 상속을 받은 클래스
//1. 최상위 관리자 클래스
//2. 대리자 (오류맞고 사망하는 클래스)
enum CURRENT_RECT
{
	CURRENTRECT_A, CURRENTRECT_B,
	CURRENTRECT_C, CURRENTRECT_D,
	CURRENTRECT_E, CURRENTRECT_F,
	CURRENTRECT_G, CURRENTRECT_H,
	CURRENTRECT_NULL
};
/*
enum class CURRENT_RECT : UINT8 
{
	CURRENTRECT_A, CURRENTRECT_B,
	CURRENTRECT_C, CURRENTRECT_D,
	CURRENTRECT_E, CURRENTRECT_F,
	CURRENTRECT_G, CURRENTRECT_H,
	CURRENTRECT_NULL
};

*/
class MainGame : public GameNode
{
private:
	Example_Mole* _mole;

	CURRENT_RECT _currentRect;

	RECT _rc[8];
	int _index;		//두더지 인덱스 8개
	int _count;		//타이머용 카운트
	int _time;		//랜덤시간 변수
	int _score;		//점수
	// 하는짓이 다르기때문에 묶어주지않았다. (x,y)같은 좌표변수면 int x,y; 묶어줘도 됨

	bool _bIsSelected;		//선택이 됐는지
	bool _bIsOnceCheck;		//한번만 눌렸는지
public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	//MainGame();
	//~MainGame();
};

