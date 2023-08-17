#include "stdafx.h"
#include "TimeManager.h"

HRESULT TimeManager::init()
{
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

#else

#endif //!_DEBUG
}
