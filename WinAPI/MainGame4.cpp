#include "Stdafx.h"
#include "MainGame4.h"




HRESULT MainGame4::init(void)
{
	GameNode::init(true);

	IMAGEMANAGER->addImage("데스 스페이스", "Resources/Images/BackGround/DeadSpace.bmp", WINSIZE_X, WINSIZE_Y);


	_alphaA = 0;
	_isAlphaIncrese = false;

	return S_OK;
}

void MainGame4::release(void)
{
	GameNode::release();

}

void MainGame4::update(void)
{
	GameNode::update();
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (MessageBox(_hWnd, "게임을 종료하시겠습니까?", "종료 확인", MB_OKCANCEL) == IDOK)
		{
			PostQuitMessage(0);
		}
	}
	_alphaA++;

}

void MainGame4::render(void)
{
	
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS); //사각형안에 영역을 브러쉬로 채우는 함수
	//=================================================
	
	IMAGEMANAGER->alphaRender("데스 스페이스", getMemDC(), 0, 0, _alphaA);

	//=================================================
	this->getBackBuffer()->render(getHDC());

}

/*
과제1. 제로 콤보이미지 완성

- 스페이스 바를 누르면 1타부터 마지막공격까지 자동으로 재생
ㄴ 무한으로 반복

과제2 프레임 이미지 처리

-시작씬 + 게임씬

- 게임씬에서는 아래의 이미지를 gui화 시켜서 재생시킨다(버튼)
ㄴ 프레임 랜더

-필수이미지

ㄴ 배경,대기,이동(좌,우), 찌르기(좌,우) ,대각선찌르기,연속찌르기(좌,ㅡ우) , 원 돌리기, 승리포즈(옷던지기),스킬 클라이막스연출
,패배

*/


/*
과제1. 캐릭터 벽잡기

- 이미지 필수 : 배경, 벽, 캐릭터(대기,이동,점프,벽을 잡고있는 모션)

- 기본적으로 벽을 잡을때는 가장 위쪽 모서리를 잡으며 벽 중간을 잡았을경우 천천히 지면으로 내려운다

- 캐릭터가 벽을 잡고 있는 상태에서 위 / 또는 아래방향키를 누르면 올라가거나 내려갈수 있어야한다.

- 또한 캐릭터가 벽 위로 올라선 다음 다시 아래로 점프하면 캐릭터는 지면에 착지할수있어야한다

- 캐릭터 점프 높이의 지형이 있고 캐릭터는 지형 밑에서 점프로 지형위 올라 갈 수있다

- 캐릭터는 지형에 올라선 상태에서 지면으로 다시 내려올 수 있으면 ok

과제2. 미니맵 연동

- 플레이어의 움직임을 미니맵에서 그대로 확인해야 한다
ㄴ 움직임까지 동일하게


*/