#pragma once
//코어(GameNode)가 없을땐 이렇게 하면 됨
class SceneManager;

class Scene
{
	friend SceneManager;
	//ㄴ friend 상속관계를 무시한다.
	/*
	확신이 있는 상태에서 사용해야함.
	
	friend: 말 그대로 친구 -> 다 스킵하고 접근해서 빼오기 가능
	ㄴ 복잡한 상속구조 / 효율적인 구조를 설계할때 많이 등장한다. ->private까지 접근할수있는 권한이 생김 
	ㄴ 수직(상속)과 수평(친구)의 관계
	ㄴ 접근제어 지시자의 영향을 받지 않는다.
	ㄴ private까지 모두 접근이 가능하기 떄문에 잘 쓰면 효율이 좋지만 그 반대라면 양아치 키워드 

	- 2개 기억
	- 클래스+함수 (함수에도찍을수있음)
	ㄴ 전부이냐 / 단일이냐
	- friend는 단방향 

	면접문제
	- friend 속성은 상속이 Y / N?
	A. 안들어갑니다. friend키워드는 단방향 키워드기 때문에

	*/
private:
	//void init(int a);

	virtual void init() = 0;
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void exit() = 0;


protected:


public:

	
	Scene();
	virtual ~Scene();

};

