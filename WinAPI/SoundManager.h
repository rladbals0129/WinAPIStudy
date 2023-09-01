#pragma once
#include "SingletonBase.h"


#pragma region 사운드 (FMOD + 트릭스터 + 배터리 엔진)
/*
상용엔진을 쓸거면 FOMD, 코코스를 쓸거면 트릭스터 ,네이티브 자체개발 모바일게임(ios)에선 배터리엔진 많이 사용

▶ FMOD (회사명 :파이어라이트 테크놀로지스)

- 사운드 엔진 라이브러리
ㄴ 사운드 관련 엔진이기 때문에 일반적으로 사용되는 대부분의 음원 확장자는 전부 지원한다고 보면 될것이고
추가로 다양한 플랫폼까지 지원을 한다.

º 사용 이유?
ㄴ WinAPI / DirectX같은 경우에도 자체 사운드 라이브러리를 가지고 있지만 가공이 필요한 경우가 많아 불편하다. 
ㄴ 개발기간 단축을 위해 사용
ㄴ 별도 스레드로 분리되면서 이전보다 활용빈도가 더 좋아졌다.


▶ 상용 엔진

- 언리얼 + 유니티 에서는 라이센스 계약으로 기본 내장
ㄴ 그렇기때문에 무료인 경우고 많고 출시를 목표로 할때만 라이센스를 필요로 한다.

- 1. 언리얼 엔진은 기본적으로 너무너무너무너무 무겁기 때문에 라이센스를 통한 내장만 되어 있다.
(기본 플래그쉽만 내장되어있다.) -> 플러그인 추가.
ㄴ EX: .bank

- 2. 유니티 내장 사운드는 기본적으로 FMOD를 사용하지만 대신 모든 기능에 대한것은 아니다.
ㄴ 그렇기 때문에 추가 기능을 사용하기 위해서는 추가 에셋을 설치해야 한다.
ㄴ EX: .bank -> FMOD 비주얼라이저


- 3. 이외의 대부분의 플랫폼에서는 사용하기 위한 선행처리가 필요하다.
ㄴ 헤더,클래스,이름 공간, 라이브러리 링크 -> 파일

※ FMOD를 이용한 대표적인 게임들
ㄴ 던파, 와우, 바이오쇼크, 디제이맥스 리스팩트V 등등 많이 있다.

▷ FMOD 구성
- 크게 3가지로 나뉜다.
ㄴ 라이브러리 + 프로그램

1. FMOD Ex (우리가 현제 쓸것)
ㄴ StudioAPI / Core API
ㄴ 로우레벨 사운드 엔진 (주로 네이티브 언어에서 채용되는 API)
ㄴ API형태로 되어있기 때문에 다른 라이브러리 대비 가볍고 빠르다. (장점)
ㄴ 하지만 코딩을 못하면 전혀 쓸 수가 없다. (단점)
ㄴ 주로 일반적인 음악 포맷을 사용한다면 선택이 되고 또한 디자이너가 없을때도 선택이 되는 경우가 많다.
		(wav,mp3,mid)		
=========================	1번을썼을때 디자이너가 있다면 2번3번이 딸려오는 경우가 많다.

2. FMOD 이벤트 시스템
ㄴ Ex의 상위 레이어 -> 디자이너가 작업한 사운드 컨텐츠를 재생하는 DATA 기반 Driven API
ㄴ 디자이너의 능력에 따른 결과물에 따라 불필요한 코드가 대부분 사라지고 이는 곧 성능 향상으로 이어진다.
ㄴ 특히 디자이너에 의한 사운드 파트에서 튜닝이 가능해 지기 때문에 
프로그래미가 전혀 사운드 관련해서 신경을 쓰지 않아도 된다. -> 개발속도up

3. FMOD 디자이너
ㄴ 사운드 이벤트를 만들어내는 툴
ㄴ 기획 + 설계 + 방향성 단계에서 FMOD가 채택이 되면 사운드 디자이너가 주로 사용할꺼다.
	 ㄴ 너희가 사용할 툴
ㄴ 상용 엔진을 사용하던 아니면 디자이너 툴을 사용하던 기본적으로 트랜지션 설계를 할 예정이기 때문에
   프로그래머로서는 더욱 편리한 면이 있다.

※ 위에 내용들은 디자이너와 협업 / 너희에게 시킬 여지가 다분하니 충분히 숙지를 해야 한다.


========프로그래머의 관점=========

※ FMOD를 포함해서 외부 기능은 대부분 라이브러리를 통해 해당 플랫폼과 언어에 맞게 커스텀 되기 때문에
외부 라이브러리를 사용하기 위해서는 라이브러리에 대한 이해가 필요하다.

정적라이브러리(lib)코드내장 , 동적라이브러리 (.dll)외부
ㄴ컴파일타임                  ㄴ런타임  

정적 - 장점:
	   단점:

동적 - 장점: 필요할때마다 dll파일을 읽어옴. 미리 심어놓지 않기때문에 메모리 다운
	   단점:

	 해당하는 기능에 따라서 연산을 할거냐 안할거냐
	 연산을 할거면은 정적 연산을 안할거면 동적

- 동적사용시 경로 주의





*/
#pragma endregion

// 사운드 갯수
constexpr auto soundBuffer = 10;

// 여분의 채널 갯수 (버퍼)
constexpr auto extraSoundChannel = 5;

// 총 사운드 갯수 
constexpr auto totalSoundChannel = soundBuffer + extraSoundChannel;


using namespace FMOD;

class SoundManager : public SingletonBase<SoundManager>
{
private:
	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundsIter;
	typedef map<string, Channel**> arrChannel;
	typedef map<string, Channel**>::iterator arrChannelIter;

	System* _system;		//fmod 시스템 접근 허용하기때문에 *1개
	Sound** _sound;			// 직접 접근이 안되기때문에 interface를 통해 접근 접근 하기위해 ** (외부 라이브러리기떄문에 막아둠)
	Channel** _channel;		//

	arrSounds _mTotalSounds;
	

public:
	HRESULT init(void);
	void release(void);
	void update(void);

	void addSound(string keyName, string soundName, bool background, bool loop);

	void play(string keyName, float volume);
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);

	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);



	SoundManager();
	~SoundManager() {}
};

