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
	�� ����(���)�� ����(ģ��)�� ����
	�� �������� �������� ������ ���� �ʴ´�.
	�� private���� ��� ������ �����ϱ� ������ �� ���� ȿ���� ������ �� �ݴ��� ���ġ Ű���� 

	- 2�� ���
	- Ŭ����+�Լ� (�Լ���������������)
	�� �����̳� / �����̳�
	- friend�� �ܹ��� 

	��������
	- friend �Ӽ��� ����� Y / N?
	A. �ȵ��ϴ�. friendŰ����� �ܹ��� Ű����� ������

	*/
private:
	//void init(int a);

	virtual void init() = 0;
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void exit() = 0;


protected:


public:

	
	Scene();
	virtual ~Scene();

};

