#pragma once


#pragma region 디자인패턴 (싱글톤)
/*
▶ 디자인 패턴

- 객체 지향 프로그래밍 설계 단계에서 자주 발생하는 또는 알려진 문제들을 피하기 위해 사용하는 일반적인 패턴을 의미

▷장점 

- 의사소통 간결화로 인한 효율 증가 (작업속도 up)

- 평준화되고 안정적인 코드 동작성을 보장한다.
ㄴ 많은 프로그래머가 이미 동일한 증상을 많이 겪어봤기때문에 시간이 지남에 따라 해결 방안도 이미 대부분 나온 상태

- 프로그래밍을 작성하기 앞서 디자인 타임에서의 다양한 상항에 대한 가이드 및 방향성 제시가 가능하다.


▷단점 

- 디자인 패턴은 코드를 설계하고 작성하는 하나의 방법일뿐 "패턴병" 조심
														
- 대부분의 디자인 패턴은 원본 부분가 활용 부분이 있기 때문에 코드간결화를 추구한다면
가능한 사용을 자제해야 한다.

▶ 싱글톤

- 프로젝트 전체에서 1개만 존재해야 하는 객체나 클래스, 또는 프로젝트 전체에서 공유하는
 클래스에 적용할 수 있는 패턴이다.

 ▷ 장점

 - 한번의 키워드를 통해 (new) 객체를 생성하며 만약 프로젝트 어느곳에도 사용하지 않으면
 인스턴스를 생성하지 않기 때문에 메모리 낭비를 방지할 수 있다. 
 (프로젝트 전체에서 1개만 존재해야 하는 객체나 클래스, 또는 프로젝트 전체에서 공유하는
 클래스에 적용할 수 있는 패턴이다.)
 

 ▷ 단점

 - 싱글톤은 대부분 전역변수로 처리하기 때문에 코드에대해 알아내기 어렵고
  싱글톤 인스턴스에게 너무 많은 데이터가 공유된다면 유지보수가 매우 어려워진다.
		ㄴ (사용했을떄 이걸 어떻게 해결할지를 생각해봐야함)


*/
#pragma endregion

template <class T>
class SingletonBase
{
protected:
	//싱글톤 인스턴스
	static T* singleton;

	SingletonBase() {};
	~SingletonBase() {};

public:
	static T* getSingleton(void);	//싱글톤 가져오기
	void releaseSingleton(void);	//싱글톤 메모리에서 해제
};

//싱글톤 초기화
template <typename T>
T* SingletonBase<T>::singleton = 0;

//싱글톤 가져오기
template <typename T>
T* SingletonBase<T>::getSingleton(void)
{
	if (!singleton) singleton = new T;

	return singleton;
}

//싱글톤 메모리에서 해제
template <typename T>
void SingletonBase<T>::releaseSingleton(void)
{
	if (singleton)
	{
		delete(singleton);
		singleton = 0;
	}
}
