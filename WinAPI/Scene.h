#pragma once
//코어(GameNode)가 없을땐 이렇게 하면 됨
class SceneManager;

class Scene
{
	friend SceneManager;
	//ㄴ friend 상속관계를 무시한다.
	/*
	확신이 있는 상태에서 사용해야함.
	
	friend: 말 그대로 친구 -> 다 스킵하고 접근해서 빼오기 가능
	ㄴ 복잡한 상속구조 / 효율적인 구조를 설계할때 많이 등장한다. ->private까지 접근할수있는 권한이 생김 
	
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

