#include "stdafx.h"
#include "EnemyManager.h"
#include "Minion.h"
#include "Rocket.h"
//해더include와 cpp include ->알아보기
// cpp는 참조를 하고 넘어감 (해당되는 해더 파일로) 해더는 복사함
HRESULT EnemyManager::init(void)
{
	IMAGEMANAGER->addFrameImage("해파리", "Resources/Images/Object/JellyFish.bmp", 0.f, 0.f, 
		1140 , 47 ,
		19 , 1 , true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("적미사일", "Resources/Images/Object/Bullet.bmp",
		14, 14,
		true,
		RGB(255, 0, 255));
	_bullet = new Bullet;
	_bullet->init("적미사일", 30, 1000);

	setMinion();
	return S_OK;
}

void EnemyManager::release(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->release();
		SAFE_DELETE(*_viMinion);
	}
	_bullet->release();
	SAFE_DELETE(_bullet);
}

void EnemyManager::update(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
		
	}
	minionBulletFire();
	_bullet->update();
	collision();
}

void EnemyManager::render()
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}
	_bullet->render();
}

void EnemyManager::setMinion(void)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Enemy* jellyFish;
			jellyFish = new Minion;
			jellyFish->init("해파리", PointMake(100 + j * 100, 100 + i * 100));
			
			_vMinion.push_back(jellyFish);
		}
	}
}

void EnemyManager::removeMinion(int arrNum)
{
	SAFE_DELETE(_vMinion[arrNum]);
	_vMinion.erase(_vMinion.begin() + arrNum);
}

void EnemyManager::minionBulletFire(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		if ((*_viMinion)->bulletCouintFire())
		{
			RECT rc = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right + -rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2 + 30,
				getAngle(rc.left + (rc.right + -rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2,
					_rocket->getPosition().x,
					_rocket->getPosition().y), RND->getFromFloatTo(2.f, 4.f));
		}

	}
}

void EnemyManager::collision(void)
{
	for (int i = 0; i < _bullet->getBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_bullet->getBullet()[i].rc,
			&_rocket->getRect()))
		{
			_bullet->removeBullet(i);
			_rocket->hitDamage(2.f);
		}
	}
}
