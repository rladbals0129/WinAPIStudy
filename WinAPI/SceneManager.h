#pragma once
#include "SingletonBase.h"

class GameNode;
class Scene;

class SceneManager : public SingletonBase <SceneManager>
{
	friend class SingletonBase <SceneManager>; // 나에속해있는 싱글톤베ㅐ이스는 제오ㅓㅣ하겠다

private:
	

public:

};

#define SCENEMANAMGER SceneManager::getSingleton()

