#include "Stdafx.h"
#include "KeyManager.h"




HRESULT KeyManager::init(void)
{
	for (int i = 0; i < KEY_MAX; i++)
	{
		this->setKeyUp(i, false);
		this ->setKeyDown(i, false);
	}
	return S_OK;
}

bool KeyManager::isOnceKeyDown(int key)
{
	// 비트단위로 AND연산을 한다
	// ㄴ둘다 1일때만 결과가 1이고 아니라면 결과가 0 으로 동작
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!this->getKeyDown()[key])
		{
			this->setKeyDown(key, true);
			return true;
		}
	}
	else
	{
		this->setKeyDown(key, false);
	}
	return false;
}

bool KeyManager::isOnceKeyUp(int key)
{
	/*
	▶GetAsyncKeyState(int key) 
	
	- 어떤 키가 입력된건지 체크/프로그램에서 키를 입력받고 싶으때 사용하는 API공용함수

	- 기본적으로 메세지 큐에 있는 키 정보를 확인한다

	- 키가 눌린 시점을 체크하기 위하 &(AND) 연산을 사용해 확인한다.

	0X0000 키안눌림
	0X0001 키눌림
	0X8000 키가 눌렸었는데 지금은 안눌림
	0X8001 키가 눌렸었고 지금도 눌려있음
	
	*/
	if (GetAsyncKeyState(key) & 0x8000)
	{
		this->setKeyUp(key, true);
	}
	else
	{
		if (this->getKeyUp()[key])
		{
			this->setKeyUp(key, false);
			return true;
		}
	}
	return false;
}

bool KeyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		return true;
	}
	return false;
}

bool KeyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001)
	{
		return true;
	}
	return false;
}

KeyManager::KeyManager()
{
}


KeyManager::~KeyManager()
{
}
