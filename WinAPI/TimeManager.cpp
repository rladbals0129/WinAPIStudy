#include "stdafx.h"
#include "TimeManager.h"

HRESULT TimeManager::init()
{
    _timer = new Timer;
    _timer->init();
    return S_OK;
}

void TimeManager::release()
{
    if (_timer != nullptr)
    {
        SAFE_DELETE(_timer);
        _timer = nullptr;
    }
}

void TimeManager::update(float lock)
{
    if (_timer != nullptr)
    {
        _timer->tick(lock);
    }
}

void TimeManager::render(HDC hdc)
{
    char str[256];
    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, RGB(255, 255, 255));

#ifdef _DEBUG
    /*
    릴리즈가 아닌 디버그모드일때 실행이 된다.
    ㄴ 테스트 용도가 강하다(개발)

    - 그렇기때문에 일반적으로 유저가 접하면 안되는 정보를 확인하면서 개발할때 유효
    ㄴ 좀더 확실한 예외가 필요하다면 assert를 이용해서 예외처리 한다.
    */
    if (_timer != nullptr)
    {
        sprintf_s(str, "FPS : %d", _timer->getFrameRate());
        TextOut(hdc, 0, 0, str, strlen(str));
        sprintf_s(str, "WorldTime : %f", _timer->getWorldTime());
        TextOut(hdc, 0, 20, str, strlen(str));
        sprintf_s(str, "ElapsedTime : %f", _timer->getElapsedTime());
        TextOut(hdc, 0, 40, str, strlen(str));
    }
#else
    if (_timer != nullptr)
    {
        sprintf_s(str, "FPS : %d", _timer->getFrameRate());
        TextOut(hdc, 0, 0, str, strlen(str));
    }

#endif //!_DEBUG

}
