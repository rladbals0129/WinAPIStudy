#include "stdafx.h"
#include "Bullets.h"

HRESULT Missile::init(int bulletMax, float range)
{
	_range = range;

	for (int i = 0; i < bulletMax; i++)
	{
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(tagBullet)); //ZeroMemory : 0으로 채운다 (memset)차이점 -> 1. 0으로초기화 2. 0이아닌 값으로 초기화 가능
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
과제1. 로켓 미사일 발사
- draw와 move 함수를 완성하고 로켓이 미사일을 발사한다.

- 당연히 미사일 이미지는 프레임으로 출력

과제2. 팀 포트폴리오로 만들 게임 선정 임박

- 최종 후보군 3개 (2개)

과제3. 타일맵 만들기

- 사용자가 입력한 숫자로 타일맵을 그린다. (최대 사이즈:100)
ㄴ ex: 20을 입력하면 20x20 사이즈의 타일이 화면에 그려진다.

- 타일맵 안에는 랜덤한 위치에 이미지 2장이 들어간다.

-이미지는 매번 타일맵을 새로 그려줄때마다 위치가 바뀌어야 하고
그려진 이미지는 마우스로 클릭할 수 있으며 위치또한 변경 할 수 있어야 한다.

필수 : STL 벡터

힌트 :
	  MoveMemory
	  CopyMemory
	  FillMemory
	  ZeroMemory 를 사용하면 쉽다




*/

HRESULT Beam::init(int bulletMax, float range)
{
	_range = range;
	_bulletMax = bulletMax;

	return S_OK;
}

void Beam::release(void)
{


	////1.정석 (c++표본에서 얘기하는 문법)
	//for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	//{
	//	SAFE_DELETE(_viBullet->img);
	//}
	////2. 줄이고싶다. (변수에 의해서 길어지는 가독성 파괴를 줄이고싶다)
	//_viBullet = _vBullet.begin();
	//for (; _viBullet != _vBullet.end(); ++_viBullet)
	//{
	//	SAFE_DELETE(_viBullet->img);
	//}
	////3. 협업식 효율적인건? -> 종류에따른 반복자가 줄어든다
	//iterBullet iterBullet = _vBullet.begin();

	////협업에서 지양해야함
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


	////5. for each -> (High)레벨에서 사용, 알고리즘 함수라 무거움
	////컨테이너 기반으로 반복문을 돌리는데 별도의 연산 로직이 없을땐 사용해도 됨
	//for each (auto iter in _vBullet)
	//{
	//	SAFE_DELETE(iter.img);
	//}

	////6. for_each-> 함수를 반복 시키겠다.
	//// 함수를 특정 경우에만 돌리고 뺴주고싶을때 사용 
	//// ㄴ 반복자의 시작과 끝, 그리고 함수를 파라미터로 받는다.
	//// ㄴ 마지막 부분이 파라미터기 때문에 람다식으로 표현이 가능
	//for_each(_vBullet.begin(), _vBullet.end(), update); 

	//int value = 0;
	//for_each(_vBullet.begin(), _vBullet.end(), [&value](auto& number)
	//	{
	//		Value += number;
	//	});

	///*
	//람다식
	//- [] () {} ()
	//ㄴ [캡처] (매개 변수) {(반환)함수동작} (호출인자(생략가능))
	//ex) - (int numA,int numB) {cout << numA + numB <<endl;} (10,20);
	//	- (int numA,int numB) {return numA + numB } (10,20);
	//*/

	//int numberA = 10;
	//int numberB = 20;
	//auto resultA = [](int numA, int numB) {return numA + numB; }(10, 10);	//아래로갈수록 효율UP
	//auto resultB = [&]()->int { return numberA + numberB; }();
	//auto resultC = [=,&numberA]()->int {return numberA + numberB; }();

	///*
	//[]: 같은 영역에 있는 모든 변수에 접근이 안된다. 
	//[&]: 같은 영역에 있는 모든 변수를 참조로 호출
	//[=]: 같은 영역에 있는 모든 변수를 값 o
	//[&, 변수A]: 같은 영역에 있는 모든 변수를 참조로 캡쳐. 단. 변수A는 값으로 캡처하겠다
	//[=, 변수A]: 같은 영역에 있는 모든 변수를 값으로 캡쳐. 단. 변수A는 값으로 캡처하겠다
	//[&변수A]: 같은영역의 변수a를 참조로 캡쳐하겠다.
	//*/

	////7. transform
	//// ㄴ 반복자를 이용한 반복문이라 할수있다 ( 결과를 다른 컨테이너에 저장 )
	////ㄴ 원본 컨테이너도 가능 + 람다
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
과제1 .
미사일 충돌처리

-내가 발사한 미사일로 적을 제거한다.
ㄴ 본인이 생각한 가장 효율적인(객체지향적인)방법으로

과제2.
체력바 구현

-로켓과 적의 체력바를 구현한다.

2가지버전으로 

1. 체력바를 각각의 객체 위에 띄워주는 방법

2. 적 객체 한정으로 체력바를 공유하는 방법


*/