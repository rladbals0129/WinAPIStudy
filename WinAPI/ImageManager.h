#pragma once
#include "SingletonBase.h"
#include "GImage.h"
#pragma region stl맵
/*
--이미지-- 설계...
 문제점
1. 객체에 따른 new
2. 관리문제
 ㄴ STL -> Map    사람이 관리하기에도 좋고 
		// 검색속도 빠른건 의미없으니 unoderdMap (검색속도빠름 중복x)은 필요없겠다

stl map
- 키+ 값을 잊지말자
ㄴ 첫번째 first->키
ㄴ 두번째 second ->값

-추가하는 방법은 insert()를 사용하고 키와 벨류를 동시에 추가해야 하니 pair/make_pair를 사용해 추가해야한다

- pair() : 두가지 자료형을 하나로 묶어주는 구조체( 템플릿이기때문에 어떤 자료형도 ok)

- make_pair() : pair를 만들어 주는 함수
ㄴ pair.first = x   pair.second =y;
ㄴ pair = make_pair(x,y)

- 하나의 키에 여러개의 값을 저장하고 싶다면 멀티맵을 사용하는 것도 고려

- pair를 확장시켜 구조를 작성하ㅏ거나 다수의 반환값을 가지고 싶다면 tuple도 고려해야 한다.
*/
#pragma endregion
class ImageManager :public SingletonBase <ImageManager>
{
private:
	//typedef 재정의 : gdi gdi+를 추가해도 쓸수있게 미래지향적으로 작성함
	typedef map<string, GImage*> mapImageList;
	typedef map<string, GImage*>::iterator mapImageIter;
	// Q. 왜 여기선char가 아니라 string이 들어갔을까?? / 스마트 포인터에 원시포인터char*이 들어가면 어떻게될까?
	//		ㄴ char* 의 메모리주소를 계속 확인해주는 작업이 생겨서 느리다
	//		ㄴ 호환성문제가 생길수 있다. 설계단계기 때문에 string을쓰자
	/*
	char*을 사용하는 경우, 문자열의 메모리 주소를 계속해서 확인해주어야 하므로 성능이 저하될 수 있습니다.
	char*은 C 스타일의 문자열 표현 방식이며, C++에서는 문자열을 안전하게 다루기 위해 std::string을 사용하는 것이 좋습니다.
	std::string은 문자열의 길이를 추적하고 메모리 관리 등을 자동으로 처리하여 안전한 문자열 타입입니다.
	std::string을 사용하면 호환성 문제를 예방할 수 있으며, C++의 다양한 문자열 처리 기능과 연산을 활용할 수 있습니다.
	스마트 포인터를 사용하여 char*을 관리하면 메모리 관리의 안전성과 편의성을 확보할 수 있습니다.
	스마트 포인터는 메모리 할당과 해제를 자동으로 처리해주므로 메모리 누수나 잘못된 메모리 참조 등의 문제를 방지할 수 있습니다.
	따라서, 설계 단계에서는 std::string을 사용하여 문자열을 다루는 것이 권장됩니다.
*/
private:
	mapImageList _mImageList;
public:

	HRESULT init(void);
	void release(void);
	//GImage에 대한 랩핑클래스다.
	// 단독으로 처리할수있지만 그럴경우 2가지 문제점이 생긴다
	// 1. 프레임워크 코드 불일치
	// 2. 객체간 (이미지) 충돌 가능성이 있다.
	GImage* addImage(string strKey,int width, int height);
	GImage* addImage(string strKey, const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	GImage* addImage(string strKey, const char* fileName, float x, float y, int width, int height,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));		
	GImage* addFrameImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	GImage* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height,
		int maxFrameX, int maxFrameY,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	GImage* findImage(string strKey);

	bool deleteImage(string strKey);
	bool deleteAll();
	//랜더

	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY); //끝x와 끝y

	//이미지클리핑 (잘라그리기)
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHight);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHight, int destWidth, int destHight);

	//알파랜더 BYTE 0~255
	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHight, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int destWidth, int destHight, int sourX, int sourY, int sourWidth, int sourHight, BYTE alpha);

	//===================프레임 랜더=================== 
	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY); 
	void loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	ImageManager() {}
	~ImageManager() {}
};

