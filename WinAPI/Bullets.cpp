#include "stdafx.h"
#include "Bullets.h"

HRESULT Missile::init(int bulletMax, float range)
{
	_range = range;

	for (int i = 0; i < bulletMax; i++)
	{
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(tagBullet)); //ZeroMemory : 0���� ä��� (memset)������ -> 1. 0�����ʱ�ȭ 2. 0�̾ƴ� ������ �ʱ�ȭ ����
		/*
			MoveMemory
			CopyMemory
			FillMemory
			ZeroMemory
		*/
		bullet.img = new GImage;
		bullet.img->init("Resources/Images/Object/Missile.bmp",
			0.0f, 0.0f,
			416, 64,
			13, 1,
			true,
			RGB(255, 0, 255));
		bullet.fire = false;
		bullet.frameTick = 7.0f;
		bullet.speed = 5.0f;
		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void Missile::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}
	_vBullet.clear();
	
	
}

void Missile::update(void)
{
	move();
}

void Missile::render()
{
	draw();
}

void Missile::fire(float x, float y)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;

		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		break;
	}
}

void Missile::draw(void)
{

	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;
		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->img->getFrameX(), _viBullet->img->getFrameY());

		_viBullet->count++;

		if (_viBullet->count % 5 == 0)
		{
			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);

			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
			{
				_viBullet->img->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}
}


void Missile::move(void)
{
	
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			_viBullet->fire = false;
		}
	}
}


//===========================================





HRESULT MissileM1::init(int bulletMax, float range)
{
	_range = range;
	_bulletMax = bulletMax;


	

	return S_OK;
}

void MissileM1::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}
	_vBullet.clear();
}

void MissileM1::update(void)
{
	move();

}

void MissileM1::render()
{
	draw();
}

void MissileM1::fire(float x, float y)
{
	if (_bulletMax <= _vBullet.size()) return;
	
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.img = new GImage;
		bullet.img->init("Resources/Images/Object/Missile.bmp",
			0.0f, 0.0f,
			416, 64,
			13, 1,
			true,
			RGB(255, 0, 255));
		bullet.speed = 5.0f;

		bullet.x = bullet.fireX = x;
		bullet.y = bullet.fireY = y;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y,
			bullet.img->getFrameWidth(), bullet.img->getFrameHeight());

		//	_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
		_vBullet.push_back(bullet);
	


	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;

		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		break;
	}
}

void MissileM1::draw(void)
{

	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->img->getFrameX(), _viBullet->img->getFrameY());

		_viBullet->count++;

		if (_viBullet->count % 5 == 0)
		{
			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);

			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
			{
				_viBullet->img->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}
}

void MissileM1::move(void)
{

	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
		
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			SAFE_DELETE(_viBullet->img);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
}

void MissileM1::removeBullet(int arrNum)
{
	SAFE_DELETE(_vBullet[arrNum].img);
	_vBullet.erase(_vBullet.begin() + arrNum);
}

/*
����1. ���� �̻��� �߻�
- draw�� move �Լ��� �ϼ��ϰ� ������ �̻����� �߻��Ѵ�.

- �翬�� �̻��� �̹����� ���������� ���

����2. �� ��Ʈ�������� ���� ���� ���� �ӹ�

- ���� �ĺ��� 3�� (2��)

����3. Ÿ�ϸ� �����

- ����ڰ� �Է��� ���ڷ� Ÿ�ϸ��� �׸���. (�ִ� ������:100)
�� ex: 20�� �Է��ϸ� 20x20 �������� Ÿ���� ȭ�鿡 �׷�����.

- Ÿ�ϸ� �ȿ��� ������ ��ġ�� �̹��� 2���� ����.

-�̹����� �Ź� Ÿ�ϸ��� ���� �׷��ٶ����� ��ġ�� �ٲ��� �ϰ�
�׷��� �̹����� ���콺�� Ŭ���� �� ������ ��ġ���� ���� �� �� �־�� �Ѵ�.

�ʼ� : STL ����

��Ʈ :
	  MoveMemory
	  CopyMemory
	  FillMemory
	  ZeroMemory �� ����ϸ� ����




*/

HRESULT Beam::init(int bulletMax, float range)
{
	_range = range;
	_bulletMax = bulletMax;

	return S_OK;
}

void Beam::release(void)
{


	////1.���� (c++ǥ������ ����ϴ� ����)
	//for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	//{
	//	SAFE_DELETE(_viBullet->img);
	//}
	////2. ���̰�ʹ�. (������ ���ؼ� ������� ������ �ı��� ���̰�ʹ�)
	//_viBullet = _vBullet.begin();
	//for (; _viBullet != _vBullet.end(); ++_viBullet)
	//{
	//	SAFE_DELETE(_viBullet->img);
	//}
	////3. ������ ȿ�����ΰ�? -> ���������� �ݺ��ڰ� �پ���
	//iterBullet iterBullet = _vBullet.begin();

	////�������� �����ؾ���
	//auto iterBullet = _vBullet.begin();
	//for (; iterBullet != _vBullet.begin(); ++iterBullet)
	//{
	//	SAFE_DELETE(_viBullet->img);
	//}

	//// 4. range base
	//for (auto it : _vBullet)
	//{
	//	SAFE_DELETE(it.img);
	//}


	////5. for each -> (High)�������� ���, �˰��� �Լ��� ���ſ�
	////�����̳� ������� �ݺ����� �����µ� ������ ���� ������ ������ ����ص� ��
	//for each (auto iter in _vBullet)
	//{
	//	SAFE_DELETE(iter.img);
	//}

	////6. for_each-> �Լ��� �ݺ� ��Ű�ڴ�.
	//// �Լ��� Ư�� ��쿡�� ������ ���ְ������ ��� 
	//// �� �ݺ����� ���۰� ��, �׸��� �Լ��� �Ķ���ͷ� �޴´�.
	//// �� ������ �κ��� �Ķ���ͱ� ������ ���ٽ����� ǥ���� ����
	//for_each(_vBullet.begin(), _vBullet.end(), update); 

	//int value = 0;
	//for_each(_vBullet.begin(), _vBullet.end(), [&value](auto& number)
	//	{
	//		Value += number;
	//	});

	///*
	//���ٽ�
	//- [] () {} ()
	//�� [ĸó] (�Ű� ����) {(��ȯ)�Լ�����} (ȣ������(��������))
	//ex) - (int numA,int numB) {cout << numA + numB <<endl;} (10,20);
	//	- (int numA,int numB) {return numA + numB } (10,20);
	//*/

	//int numberA = 10;
	//int numberB = 20;
	//auto resultA = [](int numA, int numB) {return numA + numB; }(10, 10);	//�Ʒ��ΰ����� ȿ��UP
	//auto resultB = [&]()->int { return numberA + numberB; }();
	//auto resultC = [=,&numberA]()->int {return numberA + numberB; }();

	///*
	//[]: ���� ������ �ִ� ��� ������ ������ �ȵȴ�. 
	//[&]: ���� ������ �ִ� ��� ������ ������ ȣ��
	//[=]: ���� ������ �ִ� ��� ������ �� o
	//[&, ����A]: ���� ������ �ִ� ��� ������ ������ ĸ��. ��. ����A�� ������ ĸó�ϰڴ�
	//[=, ����A]: ���� ������ �ִ� ��� ������ ������ ĸ��. ��. ����A�� ������ ĸó�ϰڴ�
	//[&����A]: ���������� ����a�� ������ ĸ���ϰڴ�.
	//*/

	////7. transform
	//// �� �ݺ��ڸ� �̿��� �ݺ����̶� �Ҽ��ִ� ( ����� �ٸ� �����̳ʿ� ���� )
	////�� ���� �����̳ʵ� ���� + ����
	//vector<int> _vBulletReload;
	//transform(_vBullet.begin(), _vBullet.end(), _vBulletReload.begin(), update);

	//transform(_vBullet.begin(), _vBullet.end(), _vBulletReload.begin(),
	//	[](__int64 numA)-> auto{return numA; });


	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}
	_vBullet.clear();
}

void Beam::update(void)
{
	move();
}

void Beam::render()
{
	draw();
}

void Beam::fire(float x, float y)
{
	if (_bulletMax <= _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.img = new GImage;
	bullet.img->init("Resources/Images/Object/Beam.bmp",
		0.0f, 0.0f,
		426, 801,
		4, 1,
		true,
		RGB(255, 0, 255));
	bullet.speed = 0.1f;

	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.img->getFrameWidth(), bullet.img->getFrameHeight());

	//	_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
	_vBullet.push_back(bullet);



	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;

		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		break;
	}
}

void Beam::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->img->getFrameX(), _viBullet->img->getFrameY());

		_viBullet->count++;

		if (_viBullet->count % 5 == 0)
		{
			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);

			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
			{
				_viBullet->img->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}
}

void Beam::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			SAFE_DELETE(_viBullet->img);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
}



/*
����1 .
�̻��� �浹ó��

-���� �߻��� �̻��Ϸ� ���� �����Ѵ�.
�� ������ ������ ���� ȿ������(��ü��������)�������

����2.
ü�¹� ����

-���ϰ� ���� ü�¹ٸ� �����Ѵ�.

2������������ 

1. ü�¹ٸ� ������ ��ü ���� ����ִ� ���

2. �� ��ü �������� ü�¹ٸ� �����ϴ� ���


*/