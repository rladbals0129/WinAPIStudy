#pragma once

// 얘를 어떻게 다른애들한테 던져주지?
//namespace 로 묶어줘야겠다. 유틸스..


//간소화 시키고 싶은 로직 -> 수학적 기능을 정의하면 좋다.

//디그리 1도의 라디안
#define DEG_TO_RAD 0.017453f

#define PI		3.141592653f
#define PI_2    6.283185308f

/*
- 반올림 오차 (Rounding Erroe)
2d에선 그정도 정밀함을 요구하지 않아 쓸일이 없지만 3D에선 매우필요. 
FLOAT_EPSILON 

- 부동소수는 기본적으로 실수를 정확하게 표현하는게 불가능
ㄴ 이유는 수학적으로 실수는 무한한 반면 이 실수를 유한한 비트로 표현을 해야하기 때문에
ㄴ 그렇기 때문에 컴퓨터는 어쩔수없이 근사값으로 처리를 한다.

- 이게 부동소수점 반올림 오차
ㄴ 컴퓨터는 실수를 이진수의 형태로 저장
ㄴ 이러한 특징때문에 오차범위가 발생하고 정확한 계산을 위해서는 상수값이 반드시 필요하다.

- 2D좌표계에서는 체감을 상대적으로 못할 수 있으나 3D에서는 체감이 확 되는 부분.

*/
#define FLOAT_EPSILON 0.001f

//실수 -> 정수
#define FLOAT_TO_INT(f1) static_cast<int>(f1 + FLOAT_EPSILON)
								//캐스팅연산자 입니다.
						
								//cast연산자 종류 4가지

/*
- C++ 캐스팅 연산자는 4종류

1. reinterpret_cast 
ㄴ 절대 번지를 바꿔주는 연산자
-예시로 포인터와 정수형과의 연산이 가능해진다.
ㄴ 절대번지(주소값)으로 연산된다. 위험함
ㄴ 간단히 얘기하면 데이터가 메모리상에 배열되는 순서가 역순으로 들어올수 있다. 
ㄴ 이는 프로그래머가 의도한 상황을 연출하는 경우가 아니기 때문에 버그로 이어짐.
ㄴ ex) 플레이어가 로드되지 않았지만 input은 받아 건물을 통과해 들어간다



*/

//두 실수가 같은지 비교
// ㄴ 여기서 사용된 절대값은 소수점 차의 절대값 반환
#define FLOAT_EQUAL(f1,f2)		(fabs(f1-f2) <= FLOAT_EPSILON)



namespace MY_UTIL
{
	// 두점사이의 거리
	float getDistance(float startX, float startY, float endX, float endY);

	//스타트 -> 엔드 -> 각을 라디안으로
	float getAngle(float startX, float startY, float endX, float endY);


}


