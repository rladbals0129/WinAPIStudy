#pragma once

/*
API 공용 함수
ㄴ 문제가 있다..
ㄴ 최초 설계단계에서 게임을 고려하고 만든 타이머들이 아니기때문에 정밀도가 떨어진다

timeGetTime (윈도우가 시작되고 1분이 지나면 60000 리턴)
GetTickCount (부팅 시간 체크 -> 부팅된 이후 1초에 1000씩 틱이 증가한다)
ㄴ 이 함수는 한계가있는데 반환시간이 최대 DWRD(32비트)다,              ->약 50일 이후로 오류
날짜로 따지면 49.7일인데 49.7일동안 윈도우를 종료하지 않으면 초기화됨
GetTickCount64


-타이머 
ㄴ 시간을 측정하는 함수들은 기본적으로 윈도우가 시작된 이후 지난 시간을 Milli Second단위로 반환한다 (1000분의 1초)
ㄴ 밀리세컨은 기본적으로 정밀도가 떨어진다 -> 게임에서
ㄴ 그렇기떄문에 보다 높은 정밀도를 원한다면 고 해상도 타이머를 추가해서 사용해야 한다.
(고해상도 타이머는 중첩을 안했을시 1/500초 중첩하면 1/900초)

- 타이머를 구현할때는 보통 해상도와 클럭을 알고 있어야 한다.

※ 해상도란?
- 다양한 시간 함수들은 시간을 측정하기 위한 각각의 틱 계산 로직이 있다.
	ㄴ 이 기준은 1분을 중점으로 삼았을때 얼마나 많은 프레임으로 나눌 수 있는지 계산

- 1분동안 얼마나 많은 틱으로 나눠서 시간의 정확도를 높이느냐가 고해상도와 저해상도의 차이를 발생 시킨다

※ 클럭 (진동수)

- 타이머에서 얘기하는 클럭은 CPU클럭

- 클럭 자체는 디지털 회로의 전기적 진동 수이며 헤르츠 단위로 표기하는게 일반적(Hz)
ㄴ ex: 1초에 1Hz며 이진수의 신호를 한번 준다는 얘기 (0또는1)
	ㄴ 1 비트를 옮길 수 있다는 얘기
	ㄴ 1Ghz 는 10의 9제곱 -> 10억번
		ㄴ 2.4Ghz는 약 24억번 (1초에 24억비트를옮길수있다)

단위
ㄴ Milli Second
ㄴ 10 Milli Second 세티
ㄴ 100 Milli Second 대시
*/
class Timer //너무무거워서 노드의 무결점을 위해 노드상속x MainGame에 묶어버릴 예정
{
private:
	float _timeScale;		//경과시간
	float _timeElapsed;		//마지막시간과 현제시간의 경과값 (1프레임과 2프레임사이. 즉 프레임을 구할수있다)
	bool _isHardware;		//하드웨어 지연여부

	__int64 _curTime;		//현제시간
	__int64 _lastTime;		//이전시간
	__int64 _periodFrequency; //시간주기

	unsigned long _frameRate; //long : 32비트에선 4바이트 64비트에선 4바이트
	//int는 byte가 올라갈 여지가있지만 long은 고정값이다
	/*
	int 와 long의 관계
	NULL과 nullptr의 관계 까먹지말기
	*/
	unsigned long _FPSFrameCount;
	float _FPSTimeElapsed;
	float _worldTime;

public:
	HRESULT init(void);
	
	void tick(float lockFPS = 0.0f); // (수직동기화같은 함수임) 이거 풀어주면 5정도 프레임 올라감

	unsigned long getFrameRate(char* str = nullptr)const;
	inline float getElapsedTime(void) const { return _timeElapsed; } //const를 붙힘으로 맴버함수의 상수화 (맴버함수의 변경을 허용하지않겠다)
	inline float getWorldTime(void) const { return _worldTime; }
};

