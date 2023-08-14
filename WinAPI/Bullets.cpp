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