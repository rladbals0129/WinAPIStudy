#include "stdafx.h"
#include "Rocket.h"
#include "EnemyManager.h" 
HRESULT Rocket::init(void)
{
	_x = static_cast<float>(WINSIZE_X / 2);
	_y = static_cast<float>(WINSIZE_Y / 2);

	//이렇게쓰면 확장성이 닫힌다
	//IMAGEMANAGER->addImage("로켓", "Resources/Images/Object/Rocket.bmp", 52, 64, true, RGB(255, 0, 255));

	//  ↓하지만 이렇게 바뀌면?
	_image = IMAGEMANAGER->addImage("로켓", "Resources/Images/Object/Rocket.bmp", 52, 64, true, RGB(255, 0, 255));
	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
	//그냥 보면 모르겠지만 확장성이 늘어남.
	//api 특성상 rect를 쓰겠다.
	//객체에 맞게끔 세팅을 해준다면 
	/*
			↑  이렇게 안하고 그냥 52 64 상수때려박으면 확장성이 막힌다. 다른곳에 안쓰고 그냥 이거만쓰겠단소리.

			_x,_y 얘를 연결해줄 방법을 생각하자.
	*/

	_flame = new Flame;
	_flame->init("Flame.bmp", &_x, &_y);

	_missile = new MissileM1;
	_missile->init(5, 600.f);

	_beam = new Beam;
	_beam->init(1,0.5f);
	_beamIrradiation = false;
//	spRocket.push_back(std::shared_ptr<Rocket>(new Rocket));
	_currentHp = 10;
	_maxHp = 10;
	_hpBar = new ProgressBar;

	_hpBar->init(_x, _y , 54, 4);
	

	

	return S_OK;
}

void Rocket::release(void)
{
	_flame->release();
	SAFE_DELETE(_flame);

	_missile->release();
	SAFE_DELETE(_missile);

	_beam->release();
	SAFE_DELETE(_beam);
}

void Rocket::update(void)
{

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _rc.right < WINSIZE_X && _beamIrradiation == false)
	{
		_x += ROCKET_SPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _rc.left > 0 && _beamIrradiation == false)
	{
		_x -= ROCKET_SPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _rc.bottom < WINSIZE_Y)
	{
		_y += ROCKET_SPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && _rc.top > 0)
	{
		_y -= ROCKET_SPEED;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_setWeapon = MISSILE;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		_setWeapon = BEAM;
	}

	switch (_setWeapon)
	{
	case MISSILE:
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_missile->fire((_rc.left + _rc.right) / 2, _y - 60);
		}
		break;

	case BEAM:
		if (KEYMANAGER->isStayKeyDown(VK_SPACE))
		{
			_beamIrradiation = true;
			_beam->fire(_x, _y - 430);
		}
		else
		{
			_beamIrradiation = false;
		}
		break;
	default:
		break;
	}
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (_currentHp > 0)
		{
			_currentHp--;
		}
		else if (_currentHp == 0)
		{
			_die = true;
		}
		
	}	
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		if (_currentHp < 10)
		{
			_currentHp++;
		}
		
	}
	collision();
	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
	_hpBar->setX(_x - (_rc.right - _rc.left) / 2);
	_hpBar->setY(_y - (_rc.bottom - _rc.top) / 2);
	_hpBar->update();
	_hpBar->setGauge(_currentHp, _maxHp);
	_hpBar->update();
	//_hpBar->setGauge();

	_flame->update();
	_missile->update();
	_beam->update();
}

void Rocket::render() 
{
	_image->render(getMemDC(), _rc.left, _rc.top);
	_flame->render();
	_missile->render();
	_beam->render();

	_hpBar->render();
}

void Rocket::removeMissile(int arrNum)
{
	_missile->removeBullet(arrNum);

}

void Rocket::collision(void)
{
	for (int i = 0; i < _missile->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getMinions().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_missile->getBullet()[i].rc,
				&CollisionAreaResizing(_em->getMinions()[j]->getRect(), 40, 30)))
			{

				_missile->removeBullet(i);
				_em->removeMinion(j);
				break;
			}
		}

	}

	for (int i = 0; i < _beam->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getMinions().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_beam->getBullet()[i].rc,
				&CollisionAreaResizing(_em->getMinions()[j]->getRect(), 40, 30)))
			{


				_em->removeMinion(j);
				break;
			}
		}

	}

}
