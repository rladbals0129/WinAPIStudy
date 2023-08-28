#pragma once
#include "SingletonBase.h"

class GameNode;
//class Scene;

class SceneManager : public SingletonBase <SceneManager>
{
	//friend class SingletonBase <SceneManager>; // ���������ִ� �̱��溣�̽��� �����ϰڴ�
public: 
	typedef map<string, GameNode*>mapSceneList;
	typedef map<string, GameNode*>::iterator mapSceneIter;
	// �� �����尡 �������� ���ΰ����ϱ� ���ؼ�

private:
	static GameNode* _currentScene;  
	static GameNode* _loadingScene;	 //static�� ������ �޸� ����(��ġ)�� Ư������
	static GameNode* _readyScene;	//�Ⱦ��� Ŭ�������ִ� �����̱⶧���� ��ġ�� �˱� �ָ���

	 mapSceneList _mSceneList;
	 mapSceneList _mLodingSceneList; //�����尡 �ȵ��� �ʿ����

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
	//�ݹ��� �������ν� �����带 ������� �ʰڴ� LPVOID DWORD -window

	SceneManager() {}
	~SceneManager() {}

};

//#define SCENEMANAMGER SceneManager::getSingleton()



//������ : �ɹ� �̴ϼȶ������ �ʱ�ȭ�� �Լ��ȿ��� �ʱ�ȭ�� ����?
// ��>
//���⼭ ������������ ���κ��� MainGame�� �����ڷ� �Ӹ�ް� �ʱ�ȭ�� ���ְ��ֱ⶧���� ���ʱ�ȭ�� �߻��� ������ �ֱ⶧��.