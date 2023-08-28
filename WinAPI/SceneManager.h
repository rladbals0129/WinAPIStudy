#pragma once
#include "SingletonBase.h"

class GameNode;
//class Scene;

class SceneManager : public SingletonBase <SceneManager>
{
	//friend class SingletonBase <SceneManager>; // 나에속해있는 싱글톤베이스는 제외하겠다
public: 
	typedef map<string, GameNode*>mapSceneList;
	typedef map<string, GameNode*>::iterator mapSceneIter;
	// ㄴ 쓰레드가 들어왔을떄 따로관리하기 위해서

private:
	static GameNode* _currentScene;  
	static GameNode* _loadingScene;	 //static을 씀으로 메모리 영역(위치)를 특정해줌
	static GameNode* _readyScene;	//안쓰면 클래스에있는 전역이기때문에 위치를 알기 애매함

	 mapSceneList _mSceneList;
	 mapSceneList _mLodingSceneList; //쓰레드가 안들어가면 필요없음

public:
	HRESULT init();
	void release(void);
	void update(void);
	void render(void);

	GameNode* addScene(string sceneName, GameNode* scene);
	GameNode* addLoadingScene(string loadingSceneName, GameNode* scene);
	
	HRESULT changeScene(string sceneName);
	
	bool findScene(string sceneName);

	friend DWORD CALLBACK loadingThread(LPVOID prc);
	//콜백을 잡음으로써 쓰레드를 사용하지 않겠다 LPVOID DWORD -window

	SceneManager() {}
	~SceneManager() {}

};

//#define SCENEMANAMGER SceneManager::getSingleton()



//생성자 : 맴버 이니셜라이즈로 초기화랑 함수안에서 초기화의 차이?
// ㄴ>
//여기서 안해준이유는 노드로부터 MainGame이 관리자로 임명받고 초기화를 해주고있기때문에 재초기화가 발생할 여지가 있기때문.