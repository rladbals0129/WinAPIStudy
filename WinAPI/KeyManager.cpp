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
	// ��Ʈ������ AND������ �Ѵ�
	// ���Ѵ� 1�϶��� ����� 1�̰� �ƴ϶�� ����� 0 ���� ����
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
	��GetAsyncKeyState(int key) 
	
	- � Ű�� �ԷµȰ��� üũ/���α׷����� Ű�� �Է¹ް� ������ ����ϴ� API�����Լ�

	- �⺻������ �޼��� ť�� �ִ� Ű ������ Ȯ���Ѵ�

	- Ű�� ���� ������ üũ�ϱ� ���� &(AND) ������ ����� Ȯ���Ѵ�.

	0X0000 Ű�ȴ���
	0X0001 Ű����
	0X8000 Ű�� ���Ⱦ��µ� ������ �ȴ���
	0X8001 Ű�� ���Ⱦ��� ���ݵ� ��������
	
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
