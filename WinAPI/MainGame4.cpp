#include "Stdafx.h"
#include "MainGame4.h"
#include "ShootingScene.h"
#include "StartScene.h"
#include "INIDataScene.h"
#include "JsonDataScene.h"

HRESULT MainGame4::init(void)
{
	GameNode::init(true);
	SCENEMANAGER->addScene("슈팅", new ShootingScene);
	SCENEMANAGER->addScene("시작", new StartScene);
	//================================
	SCENEMANAGER->addScene("제이슨", new JsonDataScene);


	SCENEMANAGER->changeScene("제이슨");
	//asdasd
	//_re.init(); //이미지 관리. 정적으로해준다 
	

	//_start = new StartScene();
	//_start->init();	
	
	//_second = new SecondScene();
	//_second->init();

	// _currentScene -> 시동이 안되면 그냥 실행 자체가 안된다 ->굳이 돌려볼필요도 없다.
	//_currentScene = _start;
	// 생성자 winMain동적할당부분에서 세팅이되고 init함수가 실행될때 _currentScene을 _start로 세팅해주고

	//그럴일은 없겠지만 만약 _currentScene에 _start가 제대로 세팅이 안되었다면 터져라
	//assert(_currentScene != nullptr, "MainGame 초기화 부분에서 노드 파트 오류 발생"); 	// <->
	//커런트씬이 null일때만 돌아라

	//assert는 c. 
	//static_assert() 는 c++
	 




	/*

	▶assert (죽여라)
	ㄴ 안정성을 통해서 assert를 통해서 관리했다. 자막

	- 디버깅 모드에서 동작하는 오류 검출용 함수
	ㄴ 릴리즈 모드에서는 동작하지 않는다.

	사용한곳에 <-> 로 주석처리 해주자 (찾기 쉬움)

	-assert 함수에 걸리게 되면 버그 발생위치/ 콜 스택등 여러 정보를 알수있다.
	    ㄴ Expression -> false -> assert error

	- if문같은건 true일때 동작하지만 assert일땐 보통 false일때 동작할수있게끔 작업을 해줘야 함
      (대부분의 문법)
				ㄴ 그렇기때문에 일어나면 안되는 조건이 아니라 꼭 일어나는 조건을 명시해야 한다.
			assert(_currentScene != nullptr);
				ㄴ _currentScene 이 null이 아니면 true가 나오게 되므로 패스
				ㄴ _currentScene 이 null이면 false가 나오므로 작동되어 터짐

	assert() : "c" -> 컴파일 타임을 지나 프로그램을 실행시키고 문제를 파악하겠다
	static_assert(): "C++" -> 컴파일 중에 문제를 파악
										ㄴ 상수값을 안에 넣어줘야겠군 (tip.컴파일 나오면 상수생각해보기)

	*/
	
	//Json::Value;

	return S_OK;
}

void MainGame4::release(void)
{
	GameNode::release();
	//SAFE_DELETE(_start);
	//SAFE_DELETE(_second);

}

void MainGame4::update(void)
{
	GameNode::update();

	SCENEMANAGER->update();

	/*_currentScene->update();

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) { _currentScene = _second; }
	

	if (KEYMANAGER->isOnceKeyDown(VK_BACK)) { _currentScene = _start; }*/
	
	
}

void MainGame4::render(void)
{
	
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS); //사각형안에 영역을 브러쉬로 채우는 함수
	//=================================================
	
	//IMAGEMANAGER->alphaRender("데스 스페이스", getMemDC(), 0, 0, _alphaA);
	
	//_currentScene->render();
	SCENEMANAGER->render();
	

	TIMEMANAGER->render(getMemDC());

	//=================================================
	this->getBackBuffer()->render(getHDC());

}

/*
과제1. 제로 콤보이미지 완성

- 스페이스 바를 누르면 1타부터 마지막공격까지 자동으로 재생
ㄴ 무한으로 반복

과제2 프레임 이미지 처리

-시작씬 + 게임씬

- 게임씬에서는 아래의 이미지를 gui화 시켜서 재생시킨다(버튼)
ㄴ 프레임 랜더

-필수이미지

ㄴ 배경,대기,이동(좌,우), 찌르기(좌,우) ,대각선찌르기,연속찌르기(좌,ㅡ우) , 원 돌리기, 승리포즈(옷던지기),스킬 클라이막스연출
,패배

*/


/*
과제1. 캐릭터 벽잡기

- 이미지 필수 : 배경, 벽, 캐릭터(대기,이동,점프,벽을 잡고있는 모션)

- 기본적으로 벽을 잡을때는 가장 위쪽 모서리를 잡으며 벽 중간을 잡았을경우 천천히 지면으로 내려운다

- 캐릭터가 벽을 잡고 있는 상태에서 위 / 또는 아래방향키를 누르면 올라가거나 내려갈수 있어야한다.

- 또한 캐릭터가 벽 위로 올라선 다음 다시 아래로 점프하면 캐릭터는 지면에 착지할수있어야한다

- 캐릭터 점프 높이의 지형이 있고 캐릭터는 지형 밑에서 점프로 지형위 올라 갈 수있다

- 캐릭터는 지형에 올라선 상태에서 지면으로 다시 내려올 수 있으면 ok

과제2. 미니맵 연동

- 플레이어의 움직임을 미니맵에서 그대로 확인해야 한다
ㄴ 움직임까지 동일하게


*/

/*
과제1 .  2d레이싱게임

- 이미지 필수 : 배경+자동차(플레이어,적) + 계기판

- 계기판은 차 속력에 따라 변환을 해야하고 최저속도와 최대속도를 예외처리한다.

- 중요한건 스피드감

- 점수시스템 구현

- 스킬3개 구현
ㄴ 1 보호막
ㄴ 2 @
ㄴ 3 홍해 가르기

※ 전자 계기판 사망




*/

/*
과제1 포트폴리오 ppt작성

-발표일은 아직 미정

-디테일 + 깔끔

과제2. 블랙홀

- 화면 외각에서 무작위로 생성되는 오브젝트 객체

- 그리고 주변 오브젝트를 빨아들일수 있는 블랙홀을 만든다

- 오브젝트가 생성되는 위치를 알기위해 표시를 한다.
ex) 색 이미지 크기

필수 : STL -> vertor / list

최소오브젝트는 1000개

역삼각함수를 사용할것




*/

/*
과제1. 캐릭터 공격 및 방어

-필수 : 이미지 -> 배경/체력바/플레이어(대기,공격,방어) , 적(대기 공격 피격)

- 기본 형식은 대전게임처럼 좌/우로 배치
ㄴ +체력바 

- 플레이어는 공격 및 방어를 할 수 있고 적은 공격 및 피격모션이 존재한다
ㄴ 적: 허수아비

- 플레이어는 상시 조종 < - > 적은 공격 on/off기능만 (이동x)

-공격, 방어 , 피격등이 발생하면 상황에 맞는 결과를 화면에 랜더링한다
ㄴ 막기 빗나감 치명타 등

- 데미지도 표기한다.
ㄴ 컨버팅 할 수 있으면 해본다.


*/