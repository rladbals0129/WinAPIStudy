#include "stdafx.h"
#include "SecondScene.h"


HRESULT SecondScene::init(void)
{
	IMAGEMANAGER->addImage("배경 루프", "Resources/Images/BackGround/bg.bmp",
		1570, WINSIZE_Y);

	_offsetX = _offsetY = 0;
	_bgSpeed = 0;

	_temp = new TempSoundScene;
	return S_OK;
}

void SecondScene::release(void)
{
	SAFE_DELETE(_temp);
}

void SecondScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (MessageBox(_hWnd, "게임을 종료하시겠습니까?", "종료 확인", MB_OKCANCEL) == IDOK)
		{
			PostQuitMessage(0);
		}
	}

	_temp->update();
	_bgSpeed += 3;
	cout << _bgSpeed << endl;
}

void SecondScene::render()
{
	IMAGEMANAGER->loopRender("배경 루프", getMemDC(),
		&RectMake(0, 0, WINSIZE_X, WINSIZE_Y),
		_bgSpeed, 0);

	SetBkMode(getMemDC(), TRANSPARENT); // dc를 그릴때 텍스트버퍼를 투명하게 해주는 함수.

	//기존 텍스트
	char str[128];
	wsprintf(str, "기존");
	TextOut(getMemDC(), 230, 350, str, strlen(str));

	//새로운 방식
	wsprintf(str, "새로운방식");
	FONTMANAGER->drawText(getMemDC(), 100, 400, "궁서", 70, 600, str, strlen(str),RGB(255,0,0));
	
}

SecondScene::SecondScene()
{
}


SecondScene::~SecondScene()
{
}



//HFONT font;
//HFONT oldFont; //기존폰트와 올드폰트로 메모리에 그려두고 스왑하는 과정
//
//
/*
//font = CreateFopnt
//(
//	v문자크기, 문자폭, 기울기(전체), 문자 방향, v문자 굵기,
//	기울기( t / f ), 밑줄( t / f ), 취소선,
//	v문자세팅, 출력 정확도, 클리핑 정확도, 출력의 질, 자간, v폰트
//);
//*/
//
//
//
//font = CreateFont
//(
//	70, 0, 0, 0, 600,
//	0, 0, 1,
//	HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("궁서")
//); // ㄴ 한글은2바이트라 해줘야댐
//
//oldFont = (HFONT)SelectObject(getMemDC(), font);
//
//wsprintf(str, "새로운 폰트");
//TextOut(getMemDC(), 100, 400, str, strlen(str));
//
//SelectObject(getMemDC(), oldFont);
//DeleteObject(font);// 올드폰트에 넣어주고 더이상쓸모없으니 딜리트해준다