#pragma once
#include "SingletonBase.h"

class GameNode;
class Scene;

class SceneManager : public SingletonBase <SceneManager>
{
	friend class SingletonBase <SceneManager>; // ���������ִ� �̱��溣���̽��� �����ä��ϰڴ�

private:
	

public:

};

#define SCENEMANAMGER SceneManager::getSingleton()

