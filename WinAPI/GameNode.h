#pragma once
#include "GImage.h"

#pragma region 객체지향 프로그래밍
/*

▶객체지향 프로그래밍 (oop)

- 코드의 재사용성이 높고 코드의 관리가 용이하다

- 기준점이 있기 때문에 신뢰성이 높은 프로그래밍을 가능하게 한다.


▶ 4대 특징
캡슐화 / 상속 / 다형성 / 추상
(프로그래밍을 할때 몇개정도만 넣어볼까?) -> 다 들어가면좋다
 가장어려운건 추상
추상객체만들고 미래에 들어올것을 예상하여 코드를 설계해야함

1. 캡슐화
- 객체의 속성을 보호하기 위한 키워드
	ㄴ 객체가 플레이어에게 오염되면 안돼

2. 상속

- 객체지향에서의 상속은 하위로 내려갈수록 구체화 되는것을 의미한다

- 재사용성 향상 + 확장성 향상 + 유지보수성 향상 + 프로그램 구조에 대한 이해도를 높힐 수 있다.
(ex) 휴머노이드 객체 ->오크,엘프,사람

3. 다형성

- 하나의 객체가 여러 형태로 변환하는 것을 의미.
	ㄴ오버라이딩

4. 추상화 - 원본에 기반한 활용하는부분이 있다라는것이 전제

- 공통적인 부분과 특징 특성을 분리 및 추출하여 재조합 및 재구성하는것을 의미한다.
(윈도우os에선 얕은추상)
▶ 객체지향 5대 설계원칙 [SOLID]

1. SRP (단일 책임 원칙)	
	ㄴ 결합도는 낮추고 응집도를 높혀라		(결합도가 높으면 유지보수가 힘들다)
	ㄴ 상속 / 오버라이딩을 하면 응집도가 높아진다.

2. OCP (개방 폐쇄의 원칙)
	ㄴ 자신의 확장에는 열려 있고/ 주변의 변화에 대해서는 닫혀있어야 한다.

3. LSP (리스코브 치환의 원칙)
	ㄴ 하위 타입은 언제나 자신의 기반인 상위 타입으로 교체가 가능해야 한다.
	ex)제네시스는 차다. 라면은 음식이다.

4. ISP (인터페이스 분리 법칙)
	ㄴ 클라이언트는 자신이 사용하지 않는 함수 / 메서드에 의존 관계를 맺으면 안된다.
	쉽게 말해 니 할거만해라. (플레이어는 플레이어 할일만, 오크는 오크할일만)
	문제. 상점아저씨는 플레이어의 소지금을 알아야할까?

5. DIP (의존관계 역전의 원칙)
	ㄴ 자신보다 변하기 쉬운것에 의존하면 안된다



*/
#pragma endregion
//백버퍼를 정적이미지로 받음
static GImage* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZE_X, WINSIZE_Y);
//씬을 바꿀수있다
class GameNode
{
private:
	//GImage* _DoubleBuffer;	//버퍼이미지
	//void setDoubleBuffer(void);//함수지만 private; 이유는 node는 최상위객체라public으로 하면
	//							//node를 상속받는 모든 class들이 이 함수를 받게된다
	//							//따라서 public으로 안하고 private로 한다
	////
	HDC _hdc;
	bool _managerInit;
public:
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);		//갱신
	virtual void render(void);

	//빽버퍼+더블버퍼 이미지 얻기

	GImage* getBackBuffer(void) { return _backBuffer; }

	HDC getMemDC() { return _backBuffer->getMemDC(); } //dc를 고유로 빼주었다. dc를 사용하고싶으면
													//랜더를 사용하거나 hdc를 불러왔어야했는데 그걸 해결해줬다.
	HDC getHDC() { return _hdc; }

	//virtual void IFunction() PURE; //순수가상함수 / 여기서 쓰면 결합도가 높아짐

	// LRESULT : 콜백의 반환형으로 많이 사용된다
	// ㄴ 메세지 처리를 마친 후에 OS에게 신호를 주기 위한 값
	// ㄴ 스위치문에서 각 메세지에 대한 처리값을 -1, 0, 1로 운영체제에 어떤 영향을 주는지 알려주는 역할을 한다.
	// ㄴ 기본적으로 0이 리턴되면 모든메세지가 처리되었다는 것을 의미한다
	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);


	//GameNode();
	virtual ~GameNode();
	//ㄴ 가상소멸자를 쓰는이유??: 자식객체에서 재정의가 발생했다면 자식객체에서 소멸자를 호출하기 위해 가상소멸자를 사용한다.
};

