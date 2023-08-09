#pragma once
#include "GameNode.h"
#define _USE_MATH_DEFINES
#include <math.h>
#define PI 3.141592653f //���ȭ 

#define DEGREE_RADIAN(_deg)		(M_PI * (_deg)/ 180.0f)
#pragma region �ﰢ�Լ�
/*
�� �ﰢ�Լ�

- ���п����� �ﰢ�Լ��� ���� �ﰢ���� ���� ���� �ﰢ�� ������ ���� ��� ��Ÿ���� �Լ��̴�
 �������ﰢ���϶��� ������ �ȴ�

- �ַ� ������ �̿��Ҷ� �ﰢ�Լ��� �ʿ�����
	��ex: �߻�ü�� ����/ ĳ������ �밢�� �̵� / ��ų�� �������� ��(��ä��)
	�� �� ���ư��� �ĵ���Ģ�� ���� ������ ��ƾ�� ����ų� ��,�������굵 �����ϴ� / �����Ѽ�����

�� �ﰢ�Լ� �ϸ� ����� 3����

- ����:l   -> �뺯(����) :h       -> �غ�: b

1. ����(sin)
- ������ ������ ������ ������ �����ִ� �Լ�
sin�� = �뺯 / ���� -> h/l

2. �ڻ���(cos)
- ������ �غ��� ������ ����� �ִ� �Լ�
�� cos�� = �غ� / ���� = b / l

3. ź��Ʈ(tan)
- ���� �ﰢ�������� ��� ������ �־����� �뺯�� �뺯�� ������ �����ش�
�� tan(45��) = 1
�� tan�� = �뺯 / �غ� = h / b



�� ���α׷��ֿ����� �ﰢ�Լ�
 
 - api�� ������ ��ǥ�踦 ����Ѵ�

 - ������ ��ǥ��� ��ī���� ��ǥ��ʹ� �޸� y ���� �Ʒ��� ���������� ������ �Ǳ� ������
  �� y��ǥ�� ���ҋ� ���ٸ� ó���� ���� �ʾҴٸ� sin�տ� - ��ȣ�� ������ �Ѵ�

  �� ����ؾ��� ����

  - PI
  �� ����(���� �ѷ�) �� ����(���� �߽��� �����ؼ� ���� ���� ������ �ݴ��� ������ ���������� ��)�� ���̸� ��� ��Ÿ����

  - ȣ����
  �� ������ ��Ÿ���� ǥ�� ����߿� �ϳ� -> ȣ�� ���̷� ������ ǥ���ϴ� ǥ���
  �� PI�� ����� ������ ǥ���ϴ°�
  �� �̸� ȣ�����̶�� �Ѵ�
  �� ȣ������ ����ؾ� �ϴ� ������ ��ǻ�ʹ� ������ �ν��Ҷ� ���� ����� �� ����.
  �� �������� ���̿� ���� ȣ�� ���� �߽ɰ��� 1ȣ�� (����) �̶�� �Ѵ�.

  - ����
  �� ȣ������ ǥ���Ҷ� ����ϴ� ����
  �� �������� ȣ�� ���̰� ���� ���� 1���� �̶�� �����Ѵ�.
  �� 1 ���� = 57.3��


  - ��
	�� �Ϲ������� ����ϴ� ���� ���� (����)
	�� ������/ ����ǥ���� �Ҹ���
	�� �ѹ����� 360���� �����Ѵ�

  - 60�й�
  �� ���� �ѷ��� 360����Ͽ� ���� ũ�⸦ ��Ÿ���� ���
  �� PI (������):3.14

  �� ���� �ѷ�: 2 * PI * ������
  �� ���� ����: ������ * ������ * PI

  - ��Ÿ�ӿ��� ���𰡸� ã���� ����ϴ� ��찡 ����

  �� ���� ���� ���޵� ���� �ƴϸ� �����ϸ� ����� �����ϴ� ���� ����
  why? �ڽ�Ʈ�� �ſ� ��

  �� PI�� ���Ȱ��� 180��

  -�׷��⋚���� ������ ������ �� �ִ�

  - ��� (Degree)
  �� 180�� = pi ����
  �� 1�� = pi / 180 ����
  �� x�� =  x * PI / 180 ����

  - ����
  �� PI ���� = 180��
  �� 1���� = 180 / PI��
  �� X ���� = X * 180 / PI ��

 �� ��ä�� ��翡���� ������,ȣ,�߽ɰ��߿� 2������ �� �� ������ �ٸ� 1������ ���� �� �ִ�.

 �� �⺻ ����

 1. �� �� ������ �Ÿ��� ���ϴ� ����
 �� �� ���� �ȴ�(start/end) -> ������ �Ÿ��� �ȴ� -> ��ǥ �������� ���� ������ �A��
	�� END - START = �� �� ������ �Ÿ� -> �A ��ŭ�� ��

�� ���� �������� �� ��(x,y) ������ ��Ÿ���� ���Ѵ�
	��DeltaX, DeltaY
2. �밢�� (����)�� �Ÿ�
�� Dinstance(����) = sqrt(DeltaX * DeltaX + DeltaY * DeltaY)       
						�� �� sqrt() ������ ���ϴ� �Լ�

3. ���� ���Ѵ� (�̰͵� �⺻������ ������ Ȱ������)

-float angle = acos (DeltaX / Dinstance);
	�� �ﰢ �Լ�: ������ �־ ���� ���
	�� ���ﰢ�Լ� : �ﰢ�Լ��� ����������� ������ ����Ѵ�.
		�� �Ϲ������� �ﰢ�Լ� �տ� arc Ȥ�� a�� ǥ��
		�Ϲ�������(�÷��̾�� �ﰢ�Լ� ���� ���ﰢ�Լ��� ���� ��찡 ����)

- ������ ���� ���̷��� ���Ѵ�
	�� float DeltaX = cos(����) * Distance(�̵���);
	�� float DeltaY = -sin(����) * Distance(�̵���);

4. x�� ��ǥ ���ϱ�
�� x = cos(���� * PI / 180) * �ӵ�;

5. y�� ��ǥ ���ϱ�
�� y = -sin(���� * PI/ 180) * �ӵ�;

*/
#pragma endregion

/*
��������
�� IntersectRect() : �������� ���ϴ� �Լ�
- ù��° ���ڴ� �� �簢�� A,B�� �浹������ ����� �簢��. 
- �� �κп� ũ�Ⱑ �����Ѵٸ� �浹�� �Ȱ��̰� �ȵȴٸ� �浹�� �ȵȰ�
- 2�� ������ ��Ʈ�� 3�� ������ ��Ʈ�� ��ġ�� ������ ����� 1����Ʈ�� ������ �Ѵ�.
- �浹�� �����ϸ� �浹�� ������ ������ ����
�� �浹�� ������ 0
�� �浹�� �߻��� ��Ȳ�̶�� NON ZERO��ȯ
*/
struct STAR //Ȯ�强�� ����
{
	int x;
	int y;
};


class MainGame2 : public GameNode
{
private:
	GImage* _bgImage;
	GImage* _plImage;
	RECT _rc;

	float _radian;
	float _degree;

	SYSTEMTIME _st; //�ð����� ����ü (os�� �������ִ� �ð��� �츮 ������Ʈ�� �������� ���� ����ü)
	HPEN _currentStarPen;
	STAR _star[5]; 

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);



	MainGame2();
	~MainGame2();
};
