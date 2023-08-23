#pragma once
#include "GameNode.h"
#include "Flame.h"
#include "Bullets.h"
#include "ProgressBar.h"

//Ŭ������ ����� ���� ����...
// ������� �ο�

#define ROCKET_SPEED 3.0f

#pragma region ����Ʈ������
/*

- auto_ptr�� ��ü�ϱ� ���� ���� ����. (C++11������ ����) (��������� ����ϱ�)
�� �޸� ���� �����ϰ� ������ Ȯ���� ���� ����Ѵ�. -> ����Ʈ������

- ������ó�� �����ϴ� Ŭ���� ���ø�
�� ����� ���� �޸𸮸� �ڵ����� �����Ѵ�.

- ����ϱ� ������ <memory> ����� �ʿ��ϰ� �⺻������ ���� �����Ͱ� ���� �޸𸮸� ����Ű�� �ϰ� 
�⺻�����͸� ����Ʈ�����Ϳ� �����ϴ� �������� ���� ����Ѵ� (���������͸� �����ϰ� �̾Ƴ��� ����)

ex)
	GImage* objectData;

	std::shared_ptr<Rocket> get_shared_ptr()
	{
		return shared_from_this();
	}

	Rocket() { objectData = new GImage[10]; }

- new..? (���� �Ҵ�) -cost����
�� ���� ���� ������ ȿ���� �����غ��� 
��Ƽ� ó�� spRocket.push_back(std::shared_ptr<Rocket>(new Rocket));
�� �׻� ����Ʈ �����͸� ����Ҷ� ¦��ó�� �����ϴ� ������ �޸𸮴� ��� �ӵ��� ì�ܾ� �Ѵ�.

�� ����Ʈ������ ����

1. unique_ptr
�� ���� ��ü (��ü�� ���� �������� �����ϰ�)

2. shared_ptr
�� �Ϲ������� ���� ��ü���� �ϳ��� ��ü�� ����ϰ� ������ �����Ѵ�.
�� ���� Ƚ���� ������� �����ϸ� �� �����ʹ� ��ü�� �������� ��Ȱ�ҋ� ����ϸ� ����.
�� ������: �迭ó�� �����Ǵ� ���·� �־��ֱ⶧���� ���� ���� ���� �ּҰ��� ���� �ȵ�. 
			��ex) 1�� 2�� 3�� 4�� �÷��̾ ������ 3������ �־��ټ� ����. 

3. weak_ptr
�� �ܵ� ���� �Ұ�
�� shared_ptr�� ������ ��ü�� ���� ������ ����Ҷ� �ʿ��ϴ�.
�� 1, 2, 3, 4 �÷��̾ ���� ������ �ϴ� ��� �� �÷��̾ �������������� ������ ���� �� �ִ�.
 1,2�÷��̾ ����Ǿ��ִٸ�(��ȯ���� �Ǿ��ִٸ�) 1�÷��̾ �����Ǹ� ������ ���α׷��� ������. 
 �� �� Ű���带 ����ϸ� ���α׷��� �������ʰ� �����. ->�� ���Ŀ� �˾Ƽ� ���Ķ� 
���޸𸮿� ���� �ʵ��� �����ְڴ� 
�� ��ȯ ������ �����Ҷ� ���ȴ�.

*/
#pragma endregion

//enable_shared_from_this : ��ü�� ���� �� �Ҹ꿡 ���� ���� ������ �ذ��Ѵ�.
// �� ������ ��ü���� �������� �ο��Ѵ�.

enum EWeapon
{
	MISSILE, BEAM
};

class EnemyManager; //Ŭ���� ���漱��
//

class Rocket : public GameNode /*, public std::enable_shared_from_this<Rocket>*/ //�������� ������ ���� �������� �ۼ��������Rocket
{
private:
	GImage* _image; //�Ŵ���Ŭ������ �ִµ� �� ���°���??
	//��� ��ä�� �ٲ��ټ� �ִ�. Ȯ�强�� ����
	
	Flame* _flame;
	EWeapon _setWeapon;

	MissileM1* _missile;
	Beam* _beam;
	bool _beamIrradiation;
	ProgressBar* _hpBar;
	int _maxHp;
	int _currentHp;
	bool _die;
	//GImage* objectData;
	EnemyManager* _em;
	
	RECT _rc;
	float _x, _y;

	//vector<std::shared_ptr<Rocket>> spRocket;
	//�����Ϳ� ����Ʈ ������ ������?
	// ��
	// ����Ʈ�������� ����?
	// ��

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();
	/*
	std::shared_ptr<Rocket> get_shared_ptr()
	{
		return shared_from_this();
	}*/
	void removeMissile(int arrNum);

	MissileM1* getMissile(void) { return _missile; }
	Beam* getBeam(void) { return _beam; }
	RECT getRect(void) { return _rc; }
	void hitDamage(float x) { _currentHp -= x; }


	virtual void collision(void);
	void setEnemyManagerMemoryAddress(EnemyManager* em) { _em = em; }
	
	POINT getPosition(void) { return PointMake((int)_x, (int)_y); }

	Rocket() { /*objectData = new GImage[10];*/ }
	~Rocket() { /*delete[] objectData;*/ }
};

//�갡 �� �ʿ��Ѱ�, ���� �갡 �־�� �ϳ� 