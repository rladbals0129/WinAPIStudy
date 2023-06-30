#pragma once
#include "SingletonBase.h"

// 객체지향 전환 -> 설계방식 / 방법론

#define KEY_MAX 256 //키의 조합max는 256

class KeyManager : public SingletonBase <KeyManager>
{
private :
	//BOOL _keyUp[KEY_MAX];
	//BOOL _keyDown[KEY_MAX];
	bitset<KEY_MAX> _keyUp;
	bitset<KEY_MAX> _keyDown;
public:
	HRESULT init(void); //초기화

	bool isOnceKeyDown(int key); //키가 한번만 눌렸는지
	bool isOnceKeyUp(int key);	// 한번 누르고 뜨었는지
	bool isStayKeyDown(int key);//키가 계속 눌려있는지
	bool isToggleKey(int key); //토글키

	bitset<KEY_MAX> getKeyUp(void){ return _keyUp; }
	bitset<KEY_MAX> getKeyDown(void) { return _keyDown; }

	void setKeyUp(int key, int state) { _keyUp.set(key, state); }
	void setKeyDown(int key, int state) { _keyDown.set(key, state); }
	KeyManager();
	~KeyManager();
};

