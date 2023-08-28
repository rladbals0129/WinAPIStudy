#include "stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"
//#include "Scene.h"

//여기있는 이친구들의 영향력은 어떻게 될까? 
// ㄴ> 초기화'만' -> 호출 여부에 관계없이
GameNode* SceneManager::_currentScene = nullptr;
GameNode* SceneManager::_loadingScene = nullptr;
GameNode* SceneManager::_readyScene = nullptr;

DWORD CALLBACK loadingThread(LPVOID prc) 
{
	// 교체될 씬의 함수 실행
	SceneManager::_readyScene->init();

	// 현재씬을 교체될 씬으로 변경
	SceneManager::_currentScene = SceneManager::_readyScene;
	// 로딩씬 해제
	SceneManager::_loadingScene->release();
	SceneManager::_loadingScene = nullptr;
	SceneManager::_readyScene = nullptr;

	return 0;
}


HRESULT SceneManager::init()
{
	_currentScene = nullptr;
	_loadingScene = nullptr;	
	_readyScene = nullptr;
	return S_OK;

}

void SceneManager::release(void)
{
	//보기에 좋고 간결하고 문제도 없어보인다
	// ㄴ c/c++언어에서는 싫어하는형태 ->단 까먹진말자
	//for each(auto scene in _mSceneList)
	//{
	//	SAFE_DELETE(scene.second);
	//}


	//메모리를 조금 더 쓰더라도 안정성을 매우 높힘. 우리가 추구해야하는 코딩 습관
	mapSceneIter miSceneList = _mSceneList.begin();
	for (; miSceneList != _mSceneList.end();)
	{
		if (miSceneList->second != nullptr)
		{
			if (miSceneList->second == _currentScene)
			{
				miSceneList->second->release();
			}
			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}
	_mSceneList.clear();
}

void SceneManager::update(void)
{
	if (_currentScene) _currentScene->update();
}

void SceneManager::render(void)
{
	if (_currentScene) _currentScene->render();
}

GameNode* SceneManager::addScene(string sceneName, GameNode* scene)
{
	if (!scene) return nullptr;

	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

GameNode* SceneManager::addLoadingScene(string loadingSceneName, GameNode* scene)
{
	if (!scene) return nullptr;

	_mSceneList.insert(make_pair(loadingSceneName, scene));

	return scene;
}

HRESULT SceneManager::changeScene(string sceneName)
{
	mapSceneIter find = _mSceneList.find(sceneName);

	//바뀌지 못했다
	if (find == _mSceneList.end()) return E_FAIL;
	//찾앗다
	if (find->second == _currentScene) return S_OK;


	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;

		// 추천 : 클래스/구조체
		// ㄴ 찝어서 제외
		// 키워드 static 
		/*
		씬에서 다시 돌아와도 초기화가 안돼야되면 여길 만들자
		*/

		return S_OK;
	}


	return E_FAIL;
}

bool SceneManager::findScene(string sceneName)
{
	mapSceneIter find = _mSceneList.find(sceneName);
	if (find == _mSceneList.end())return E_FAIL;
	if (find->second == _currentScene) return E_FAIL;

	return S_OK;
}

