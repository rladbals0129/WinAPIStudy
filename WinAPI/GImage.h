#pragma once
//include 는 복사다 c++에서
// 전처리기 단계가 길어지면서 메모리사용량+ 컴파일시간 증가
//#include "Animation.h"

class Animation; //애니메이션 클래스라는게 있대. 걔가뭔데? 몰라
//ㄴ 있다는거만 알고있어라.

// -선행- ㄴ 전방선언이 들어오면 문법적으로 cpp에 include가 들어와 줘야 한다.

/*
- 클래스 전방선언

전방선언 + 전처리기문 ->#include 

is a 관계: 제네시스는 차다. (include)

has a 관계: 제네시스는 바퀴를 가지고 있다. (클래스 전방선언)


-이를 해결하기 위해 전방선언으로 풀어줄 수 있다.
ㄴ 1. 클래스의 포인터 / 참조 형식으로 이름만 참조할 경우
ㄴ 2. 매개 변수나 리턴타입을 위한 이름만 참조할 경우

*/

class GImage
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE =0, LOAD_FILE,	//리소스,파일
		LOAD_EMPTY,LOAD_END				// 빈 비트맵, 로드Done
	};

	typedef struct tagImage
	{
		DWORD	 resID;
		HDC		 hMemDC;
		HBITMAP  hBit;
		HBITMAP  hObit;
		float	 x;						//이미지 x좌표
		float	 y;						//이미지 y좌표
		int		 width;					//이미지 가로크기
		int		 height;				//
		int		 currentFrameX;			//현재 프레임 x		//
		int		 currentFrameY;			//
		int		 maxFrameX;				//최대 프레임 x 갯수
		int		 maxFrameY;				//
		int		 frameWidth;			//1프레임 가로크기
		int		 frameHeight;			//1프레임 세로크기
		BYTE	 loadType;				//

		//- 애니메이션 - 
		// 스프라이트 이미지에 맞게 x y좌표를 탐색해 애니메이션 조건에 따라 출력
		// 모션에따라 가로크기 세로크기가 다를텐데 누구에 맞춰야 할까??
		//	 ㄴ 가장 큰 모션 이미지 크기에 맞춰야한다.

		/*
		
		
		
		*/


		tagImage()
		{
			resID = 0;
			hMemDC = nullptr;		//단독으로 따로 사용되고있으니 별도로찍어서 별도로 날려줘야댐
			hBit = nullptr;		//단독으로 따로 사용되고있으니 별도로찍어서 별도로 날려줘야댐
			hObit = nullptr;		//단독으로 따로 사용되고있으니 별도로찍어서 별도로 날려줘야댐
			x = y = 0;

			width = 0;
			height = 0;

			currentFrameX   = 0;
			currentFrameY   = 0;
			maxFrameX	    = 0;
			maxFrameY	    = 0;
			frameWidth	    = 0;
			frameHeight	    = 0;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO; //재정의

private:
	LPIMAGE_INFO _imageInfo; //이미지 정보에 대한 구조체
	char*		 _fileName; // 로드파일(파일을 찾기 위한 변수)
	bool		 _isTrans;  // (이미지의 빈 값을 처리) 배경을 뺼꺼면 어떤 색으로 뺼것이냐. //없앨건지?
	// - 마젠타 색상으로 뺀다(분홍비슷) 이유: 게임에서 거의 안쓰는 색상이라서.
	COLORREF	 _transColor; //없앨 RGB값 (255,0,255)

	/*
	COLORREF - 면접문제
	-윈도우즈에서 색상값을 표현학 위한 부호없는 32비트 정수형
	ㄴ R,G,B 각각 1바이트(8비트) 이며 0~255까지의 값을 표현하는데 최적화 되어있다.	
	*/

	BLENDFUNCTION _blendFunc;	//알파블랜드에 대한 기능 (투명)
	LPIMAGE_INFO _blendImage;   // 알파블랜드 이미지  (투명)
	//별도의 초기식 함수가 필요하다.
	
public:
	// ★★★★★★★★★★★★init 을 하나로 합치지 않고 이렇게 많이 오버로딩 해본 이유가 무엇일까?
	//★★★★★★★★★★★★ 프리징 현상을 방지하기 위해서 cost를 낮추려고 나눠놓았다.
	//이미지 너비높이로 초기화
	HRESULT init(int width, int height);

	//이미지 리소스로 초기화									BOOL -> c언어 정수계열로 bool을 인위적으로 재정의
	HRESULT init(const DWORD resID, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	//이미지 파일로 초기화
	HRESULT init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
																//BOOL 로 하면 안되는이유 -> BOOL유형은 정수계열의 
	//																확장이기 때문에 컴퓨터가 정수로 인식


	//====================프레임 애니메이션 초기화 ========================
	HRESULT init(const char* fileName, float x, float y, int width, int height,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));		//한번 쓰고 값을 안바꾸는애들
	// ㄴ ex) 배경 단, 요즘게임들은 배경도 나뉘어져있다

	HRESULT init(const char* fileName,  int width, int height, int maxFrameX, int maxFrameY,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	HRESULT init(const char* fileName,float x, float y, int width, int height, 
		int maxFrameX, int maxFrameY,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	// 플레이어 객체에 쓰이겠다. 위치값 너비높이 맥스프레임 다 받고있으므로 콕 찝어서 그릴수있겠다.
	//=====================================================

	HRESULT initForAlphaBlend(void);
	//투명 컬러키 세팅
	void setTransColor(bool isTrans, COLORREF transColor);
	//해제
	void release(void);

	//랜더
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY); //끝x와 끝y

	//이미지클리핑 (잘라그리기)
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHight); 
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHight, int destWidth, int destHight);

	//알파랜더 BYTE 0~255
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc,int destX ,int destY ,BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHight, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int destWidth, int destHight, int sourX, int sourY, int sourWidth, int sourHight, BYTE alpha);

	//===================프레임 랜더=================== 그려지는방식이 까다로워질테니 인라인함수를추가해보자
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX,int currentFrameY);

	//==================루프랜더====================
	// ㄴ 반복 / 이미지를 밀고 당기는 방식 
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY); //ex) 슈팅게임 배경, 러닝게임 배경 (활용하면 카메라구현가능)
									//그려지는 영역
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY,BYTE alpha);

	void aniRender(HDC hdc, int destX, int destY, Animation* ani);


	//렉트를 선행적으로 그려놓고


	// ↓클레스를 다 뒤지지 않기 위해 인라인으로 x y 좌표 등등을 받아온다.

	// ==인라인함수==
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	inline float getX(void) { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }

	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }

	//이미지 센터좌표
	inline void setCenter(float x, float y)
	{ 
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}
	//이미지 가로세로크기
	inline int getWidth(void){return _imageInfo->width;}
	inline int getHeight(void){return _imageInfo->height;}
	
	//바운딩박스(충돌용렉트) 엔진에서 쓰이는 충돌체를 따라하기위해 (유니티 box collider)
	inline RECT boundimgBox(void)
	{
		RECT rc =
		{
			(int)_imageInfo->x,
			(int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->width,
			(int)_imageInfo->y + _imageInfo->height
		};

		return rc;
	}


	//바운딩박스(충돌용렉트)
	inline RECT boundimgBoxWithFrame(void)
	{
		RECT rc =
		{
			(int)_imageInfo->x,
			(int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->frameWidth,
			(int)_imageInfo->y + _imageInfo->frameHeight
		};

		return rc;
	}


	//===프레임에 대한 인라인
	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX) 
	{ 
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	
	}
	//프레임 x y가 max를 넘어가면 max로 정해준다
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}

	}

	//이미지 1프레임에 대한 가로세로크기
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }

	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	//최대 프레임 xy 갯수
	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }

	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

	GImage(); // 생성자는 쓰고 소멸자를 안쓰는 이유? -> 추상객체기때문에 
	~GImage() {}
};

