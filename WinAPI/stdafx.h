#pragma once
//경고 무시
#pragma warning(disable : 4005)
// 4005: DXGI 등 그래픽 인터페이스에서 매크로 관련하여 출력되는 경고

/*
▶ Stdafx

- MS의 비주얼 스튜디올르 이용하여 프로젝트를 만들면 생성되는 클레스이다
	ㄴ 이 친구가 의미하는 바는 표준 어플리케이션 프레임 워크의 툴

- 마소에서 개발자들의 능률 향상을 위해 만들어둔 PCH파일
	ㄴ 자주 쓰이는 여러가지 헤더들은 미리 컴파일해두어 이후 다시 컴파일 하지 않고 사용하게 된다.

- 개발의 초기 구축단계에서는 별 필요성을 못느끼지만 헤더파일의 크기가 커지거나 양이 많아질수록
활용도 및 효율이 급상승한다.


*/

//SDKDDKVER.h 는 프로그램에서 지원할 os에 따라 or 라이브러리에 따라 Windows 헤더에서
//코드에 포험도리 함수/상수 등을 제어하는데 사용 한다.
#include <SDKDDKVER.h>

#include "targetver.h"

//#include <ole2.h>
// GDI+ 를 사용하려면 헤더파일에서 꺼내와야 한다.
#define WIN32_LEAN_AND_MEAN

//콘솔창
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")  //?
//라이브러리 추가
#pragma comment (lib,"msimg32.lib")
#pragma comment (lib,"lib/FMOD/fmodex_vc.lib")

#pragma comment (lib,"JsonCPP/lib_json/json_vc71_libmtd.lib")



#include <windows.h>

//외부 해더
#include "inc/FMOD/fmod.hpp"
#include "JsonCPP/include/json/json.h"


//! C런타임 헤더파일
#include <stdlib.h> // C언어 표준 라이브러리 함수
#include <malloc.h>// C언어에서 메모리 할당할때 사용한다
#include <memory.h> // 메모리 관련 헤더파일 memset,memcpy(windows헤더에 포함됨(개정을통해서))
#include <tchar.h> //
#include <time.h>

/*
▶문자열 셋

- 윈도우에서 사용할 문자열 출력 파일(문자) 셋(TextOut, DrawText, wsprinf 등등)
ㄴ 기본적으로 유니코드기반

MBCS (멀티바이트 캐릭터 셋)

- 기존에 사용하던 멀티바이트 형태의 문자열을 뜻한다
- 멀티바이트 코드는 영어같은 아스키 코드에 포험되는 문자는 1바이트로 표기하고
  포함되지 않는 문자는 2바이트로 철한다

WBCS (와이드 바이트 캐릭터 셋)

- 모든 문자를 2바이트로 처리하며 유니코드 기반이다

▶ 유니코드와 멀티바이트의 사용

- VS에서는 개발시 멀티바이트 / 유니코드 뭘쓸지 기본적으로 지정을 해줘야 한다.

- 유니코드인 경우에는 문자열을 ""로 감싸고 그 앞에 L을 붙혀서 (L"")이라고 표기한다

- 멀티바이트 같은 겅우에는 그냥 ""만 사용하면 된다.

- 유니코드로 개발된 프로그램을 멀티바이트로 이식하려면
이들 문자열의 표현방식을 다시 고쳐줘야 하기때문에 매우 불편하다.
ㄴ 그래서 _T 매크로를 사용해야 한다.

- 문자열을 따옴표로 감싸고 유니코드에서 사용한 "L"대신 "_T"를 사용하면
매크로가 알아서 개발 환경에 맞게 치환해준다.

*/
#include <stdio.h> //표준 입출력 헤더파일


//! C++런타임 헤더 파일
#include <iostream>
/*
chrono
- c++11에서 추가된 시간 관련 라이브러리(STL)
ㄴ 기존 c런타임에서 제공하는 time함수보다 다양한 / 확장된 기능을 지원한다.
ㄴ 장점: 정밀도가 높다.(나노 밀리 초 단위)
	ㄴ time함수는 초단위 값만 측정이 가능하기 떄문에 정말도가 떨어질 수밖에 없다
ㄴ OS와 독립적으로 동작을 한다.
*/
#include <chrono>
#include <random>
#include <vector>
#include <map>
#include <unordered_map> //Hash 자료구조
//ㄴ 일반적 상황에서 MAP보다 검색 속도가 더 빠르다.
// ㄴ 빠른 이유는 중복된 데이터를 허용하지 않기 떄문에
//	ㄴ 단. 유사데이터가 많을시(key) 해시 충돌이 발생할 여지가 생기기 때문에 성능 저하가 발생한다.
#include <cassert> //c++프로그래머의 희망. -> 잘 쓰면
#include <bitset>// 비트연산을 좀 더 쉽게 관리해주는 함수를 지원하는 STL
// ㄴ reset(),set(),flip(),all(),any(),size() 등등..

#include <algorithm> //람다
//함수 포인터 변수처럼 주고받을수있다
//bind : 특정 인자에 대해서만 함수를 실행시키고싶을떄/특정인자와 특정 함수를 묶어버릴때
// ㄴ 함수포인터->이벤트->트리거->델리게이트->액션트리거->관찰자패턴
//우리도 쓰고있었다. 윈도우프로시저(콜백함수)
#include <functional>
#include <fstream>
#include <queue>
#include <deque>

using namespace std;
/*
//D2D/D3D 헤더 파일
#include <D2D1.h>
#include <d2d1helper.h>
#include <d3dx0.h>
#include <D3DX11.h>
#include <d3d11shader.h>
#include <dinput.h>

#pragma comment (lib,"d2d1.lib")
#pragma comment (lib,"d3d9.lib")
#pragma comment (lib,"d3dx9.lib")
#pragma comment (lib,"d3d11.lib")
#pragma comment (lib,"d3dx11.lib")
#pragma comment (lib,"dinput8.lib")
#pragma comment (lib,"dxguid.lib")

ID2D1Factory* _ID2DFactory = nullptr;
ID2D1HwndRenderTarget* _ID2DRenderTarget = nullptr;
 */

// ※ 사용자 정의 해더파일명
#include "CommonMacroFunction.h"
#include "RandomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "TempSoundManager.h"
#include "Utils.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "INIData.h"
#include "SoundManager.h"
using namespace MY_UTIL;

// # 싱글톤 #
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define FONTMANAGER FontManager::getSingleton()
#define TEMPSOUNDMANAGER TempSoundManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()
#define INIDATA INIData::getSingleton()
#define SOUNDMANAGER SoundManager::getSingleton()

//타이틀
#define WINNAME		(LPTSTR)(TEXT("WindowsAPI"))

// !전체화면
//#define FULLSCREEN

#ifdef FULLSCREEN

#define WINSTART_X	0
#define WINSTART_Y	0
#define WINSIZE_X	GetSystemMetrics(SM_CXSCREEN) //GetSystemMetrics()인자로 전달되는 시스템 설정 정보를 반환
#define WINSIZE_Y	GetSystemMetrics(SM_CYSCREEN) //SM_CXSCREEN ,SM_CYSCREEN 현제 화면 해상도 반환(x,y축) 
#define WINSTYLE	WS_POPUPWINDOW | WS_MAXIMIZE

#else

#define WINSTART_X	0
#define WINSTART_Y	0
#define WINSIZE_X	600
#define WINSIZE_Y	800
#define WINSTYLE	WS_CAPTION | WS_SYSMENU
#endif

// #매크로# (윈도우 창 초기화)
//#define WINNAME		(LPTSTR)(TEXT("WindowsAPI"))
//#define WINSTART_X	0
//#define WINSTART_Y	0
//#define WINSIZE_X	1280
//#define WINSIZE_Y	800
////WS_CAPTION : 타이틀바를 가지기 위한 옵션
////WS_SYSMENU : 제목 표시줄에 컨트롤 메뉴 상자 창
//#define WINSTYLE	WS_CAPTION | WS_SYSMENU

//# 매크로 함수 #   -> 매크로함수는 한줄만인식 이어가고싶으면 아래처럼 \ 를 사용하자
// (클래스에서 동적할당된 부분 해제)
#define SAFE_DELETE(p) {if(p) { delete (p); (p) = nullptr; }}
#define SAFE_DELETE_ARRAY(p) {if(p) { delete[] (p); (p) = nullptr; }}
#define SAFE_RELEASE(p)	{if(p) {(p)->release(); (p) = nullptr; }}
#define SAFE_RELEASE_SCNEN(p) {if(p) {(p)->Release(); (p) = nullptr; }}

// 레일슈터 / 플래포머 / 슈팅					  /   리듬    / RPG / 점프  -> 포폴 장르 추천
//  ㄴ 마리오          ㄴ삼각함수가 숙련되어야함 
//

// # 전역 변수 # (데이터 영역, 프로잭트 전체에서 접근가능해서 주의해야함)
//		ㄴ(ex - 플레이어 인벤토리 추천)
//static vs extern   ?? 
// static 은 더이상 전역이 아니게 바꿔줄수 있다.
// extern 은 프로젝트가 끝날떄까지 계속 전역
// ㄴextern키워드는 다른헤더 /cpp 에서 변수를 공유해서 쓰기 위해 사용한다
// ㄴ객체
// 기본적으로 전역변수는 extern키워드를 생략해도 기본적으로 extern화 되는 경우가 많다. (명시를 해줬을뿐)
// ID2D1HwndRenderTarget* _ID2DRenderTarget = nullptr; <- 이거는 안된다. nullptr이 아니라 정확히 명시를 해줘야함
//	ㄴ 클래스를 참조하고있는 포인터변수

//전역변수
extern HINSTANCE _hInstance;
extern HWND      _hWnd;

extern POINT	 _ptMouse;
// └ x좌표와 y좌표를 평면의 좌표에 정의할떄 사용을 한다. (ex ->마우스 커서 why? 상점을가든 옵션을 켜든 마우스는 계속 있으니까.)
//			ㄴ전역으로 쓰기 좋다.


