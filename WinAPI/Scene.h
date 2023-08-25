#pragma once
//�ھ�(GameNode)�� ������ �̷��� �ϸ� ��
class SceneManager;

class Scene
{
	friend SceneManager;
	//�� friend ��Ӱ��踦 �����Ѵ�.
	/*
	Ȯ���� �ִ� ���¿��� ����ؾ���.
	
	friend: �� �״�� ģ�� -> �� ��ŵ�ϰ� �����ؼ� ������ ����
	�� ������ ��ӱ��� / ȿ������ ������ �����Ҷ� ���� �����Ѵ�. ->private���� �����Ҽ��ִ� ������ ���� 
	
	*/
private:
	void init(int a);

	virtual void init() = 0;
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void exit() = 0;


protected:


public:

	
	Scene();
	virtual ~Scene();

};

