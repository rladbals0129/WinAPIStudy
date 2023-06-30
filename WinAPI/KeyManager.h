#pragma once
#include "SingletonBase.h"

// ��ü���� ��ȯ -> ������ / �����

#define KEY_MAX 256 //Ű�� ����max�� 256

class KeyManager : public SingletonBase <KeyManager>
{
private :
	//BOOL _keyUp[KEY_MAX];
	//BOOL _keyDown[KEY_MAX];
	bitset<KEY_MAX> _keyUp;
	bitset<KEY_MAX> _keyDown;
public:
	HRESULT init(void); //�ʱ�ȭ

	bool isOnceKeyDown(int key); //Ű�� �ѹ��� ���ȴ���
	bool isOnceKeyUp(int key);	// �ѹ� ������ �߾�����
	bool isStayKeyDown(int key);//Ű�� ��� �����ִ���
	bool isToggleKey(int key); //���Ű

	bitset<KEY_MAX> getKeyUp(void){ return _keyUp; }
	bitset<KEY_MAX> getKeyDown(void) { return _keyDown; }

	void setKeyUp(int key, int state) { _keyUp.set(key, state); }
	void setKeyDown(int key, int state) { _keyDown.set(key, state); }
	KeyManager();
	~KeyManager();
};

