#pragma once
#include "GameNode.h"
#include "Flame.h"
#include "Bullets.h"
#include "ProgressBar.h"

//클래스를 만들면 가장 먼저...
// 설계와의 싸움

#define ROCKET_SPEED 3.0f

#pragma region 스마트포인터
/*

- auto_ptr을 대체하기 위해 나온 문법. (C++11에서는 삭제) (방어적으로 대답하기)
ㄴ 메모리 릭을 방지하고 안정성 확보를 위해 사용한다. -> 스마트포인터

- 포인터처럼 동작하는 클래스 템플릿
ㄴ 사용이 끝난 메모리를 자동으로 해제한다.

- 사용하기 전에는 <memory> 헤더가 필요하고 기본적으로 원시 포인터가 실제 메모리를 가리키게 하고 
기본포인터를 스마트포인터에 대입하는 형식으로 많이 사용한다 (원시포인터를 지정하고 뽑아내는 형식)

ex)
	GImage* objectData;

	std::shared_ptr<Rocket> get_shared_ptr()
	{
		return shared_from_this();
	}

	Rocket() { objectData = new GImage[10]; }

- new..? (동적 할당) -cost높음
ㄴ 들어가긴 들어가야 하지만 효율을 생각해보자 
모아서 처리 spRocket.push_back(std::shared_ptr<Rocket>(new Rocket));
ㄴ 항상 스마트 포인터를 사용할때 짝꿍처럼 등장하니 웬만한 메모리는 묶어서 속도를 챙겨야 한다.

▷ 스마트포인터 종류

1. unique_ptr
ㄴ 유일 객체 (객체에 대한 소유권을 유일하게)

2. shared_ptr
ㄴ 일반적으로 여러 객체에서 하나의 객체를 사용하고 싶을때 적용한다.
ㄴ 참조 횟수를 기반으로 동작하며 이 포인터는 객체간 소유권을 분활할떄 사용하면 좋다.
ㄴ 주의점: 배열처럼 나열되는 형태로 넣어주기때문에 값이 들어갈때 절대 주소값이 들어가면 안됨. 
			ㄴex) 1번 2번 3번 4번 플레이어가 있으면 3번부터 넣어줄수 없다. 

3. weak_ptr
ㄴ 단독 실행 불가
ㄴ shared_ptr이 소유한 객체에 대한 접근을 허용할때 필요하다.
ㄴ 1, 2, 3, 4 플레이어가 서로 참조를 하는 경우 한 플레이어를 해제를해줬을때 문제가 생길 수 있다.
 1,2플레이어가 연결되어있다면(순환참조 되어있다면) 1플레이어가 삭제되면 원래는 프로그램이 터진다. 
 ㄴ 이 키워드를 사용하면 프로그램이 터지지않고 멈춘다. ->그 이후에 알아서 고쳐라 
ㄴ메모리에 들어가지 않도록 막아주겠다 
ㄴ 순환 참조를 제거할때 사용된다.

*/
#pragma endregion

//enable_shared_from_this : 객체의 생성 및 소멸에 의한 참조 문제를 해결한다.
// ㄴ 각각의 객체에게 소유권을 부여한다.

enum EWeapon
{
	MISSILE, BEAM
};

class EnemyManager; //클래스 전방선언
//

class Rocket : public GameNode /*, public std::enable_shared_from_this<Rocket>*/ //소유권을 주장할 놈이 누구인지 작성해줘야함Rocket
{
private:
	GImage* _image; //매니저클래스가 있는데 왜 들어온거지??
	//대상 객채를 바꿔줄수 있다. 확장성을 위해
	
	Flame* _flame;
	EWeapon _setWeapon;

	MissileM1* _missile;
	Beam* _beam;
	bool _beamIrradiation;
	ProgressBar* _hpBar;
	int _maxHp;
	int _currentHp;
	bool _die;
	//GImage* objectData;
	EnemyManager* _em;
	
	RECT _rc;
	float _x, _y;

	//vector<std::shared_ptr<Rocket>> spRocket;
	//포인터와 스마트 포인터 차이점?
	// ㄴ
	// 스마트포인터의 종류?
	// ㄴ

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();
	/*
	std::shared_ptr<Rocket> get_shared_ptr()
	{
		return shared_from_this();
	}*/
	void removeMissile(int arrNum);

	MissileM1* getMissile(void) { return _missile; }
	Beam* getBeam(void) { return _beam; }
	RECT getRect(void) { return _rc; }
	void hitDamage(float x) { _currentHp -= x; }


	virtual void collision(void);
	void setEnemyManagerMemoryAddress(EnemyManager* em) { _em = em; }
	
	POINT getPosition(void) { return PointMake((int)_x, (int)_y); }

	Rocket() { /*objectData = new GImage[10];*/ }
	~Rocket() { /*delete[] objectData;*/ }
};

//얘가 왜 필요한가, 굳이 얘가 있어야 하나 