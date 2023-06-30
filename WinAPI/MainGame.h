#pragma once
#include "GameNode.h"
#include "Example_Mole.h"
// ��ü���� ���α׷���-> ������ ����� ȿ������ ����а� ���� ü��
/*
������ �δ������ �����̴�..

1. �δ���+��
�� Ŭ��������..?
	�� ���? / Ŭ���� ����? / STL�� �ʿ��Ѱ�?
		�� �����ӿ�ũ�������� ���� ����� �ؾ߸� �˷��ټ�������?? �ƴϸ� �ٸ� ���� ������??

2. ü��(����,Ŭ����,����ü) �ݵ�� ����Ǿ����. �׷��� ���뼺�� ��������/ Ȯ�强 ��������
�ʿ��Ѱ��� ���� �������ϰ� ��üȭ�� ����.

3. ��üȭ
     �� PCH / �Լ� -> ��������

*/


//0. ����� ���� Ŭ����
//1. �ֻ��� ������ Ŭ����
//2. �븮�� (�����°� ����ϴ� Ŭ����)
enum CURRENT_RECT
{
	CURRENTRECT_A, CURRENTRECT_B,
	CURRENTRECT_C, CURRENTRECT_D,
	CURRENTRECT_E, CURRENTRECT_F,
	CURRENTRECT_G, CURRENTRECT_H,
	CURRENTRECT_NULL
};
/*
enum class CURRENT_RECT : UINT8 
{
	CURRENTRECT_A, CURRENTRECT_B,
	CURRENTRECT_C, CURRENTRECT_D,
	CURRENTRECT_E, CURRENTRECT_F,
	CURRENTRECT_G, CURRENTRECT_H,
	CURRENTRECT_NULL
};

*/
class MainGame : public GameNode
{
private:
	Example_Mole* _mole;

	CURRENT_RECT _currentRect;

	RECT _rc[8];
	int _index;		//�δ��� �ε��� 8��
	int _count;		//Ÿ�̸ӿ� ī��Ʈ
	int _time;		//�����ð� ����
	int _score;		//����
	// �ϴ����� �ٸ��⶧���� ���������ʾҴ�. (x,y)���� ��ǥ������ int x,y; �����൵ ��

	bool _bIsSelected;		//������ �ƴ���
	bool _bIsOnceCheck;		//�ѹ��� ���ȴ���
public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	//MainGame();
	//~MainGame();
};

