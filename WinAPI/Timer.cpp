#include "stdafx.h"
#include "Timer.h"

HRESULT Timer::init(void)
{
    //QueryPerformanceFrequency() : 초당 진동수를 체크하고 고성능 타이머를 지원하면 t 반대라면f
    //ㄴ LARGE_INTEGER : int를 최대값으로 떙겨쓰겠다
    //ㄴ _periodFrequency:초당 파악할 수 있는 시간이 들어간다. (기본은 밀리세컨)
    //사용이 가능한 경우 true
    if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
    {
        _isHardware = true;
        
        //QueryPerformanceCounter() : 특정 지점에서 몇번 진동했는가를 나타내는 함수
        QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);

        //초당 시간을 계산할 수 있는 시간주기
        _timeScale = 1.0f / _periodFrequency;
    }
    else
    {
        _isHardware = false;
        _lastTime = timeGetTime();
        _timeScale = 0.001f;
    }

    _frameRate = 0;
    _FPSFrameCount = 0;
    _FPSTimeElapsed = 0.0f;
    _worldTime = 0.0f;
    return S_OK;
}

//시간계산
void Timer::tick(float lockFPS)
{
    if (_isHardware)
    {
        QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
    }
    else
    {
        _curTime = timeGetTime();
    }

    //마지막 시간과 현제 시간의 경과량 측정
    _timeElapsed = (_curTime - _lastTime) * _timeScale;

    if (lockFPS > 0.0f)
    {
        while (_timeElapsed < (1.0f / lockFPS))
        {
            if (_isHardware)
            {
                QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
                
            }
            else
            {
                _curTime = timeGetTime();
            }
            _timeElapsed = (_curTime - _lastTime) * _timeScale;
        }
    }


    _lastTime = _curTime;
    // 초당 프레임 카운트 증가
    _FPSFrameCount++;

    // 초당 프레임 시간 경과량 측정
    _FPSTimeElapsed += _timeElapsed;

    //전체시간 경과량 측정
    _worldTime += _timeElapsed;

    //프레임 1초마다 초기화
    if (_FPSTimeElapsed > 1.0f)
    {
        _frameRate = _FPSFrameCount;
        _FPSFrameCount = 0;
        _FPSTimeElapsed = 0.0f;
    }
}

unsigned long Timer::getFrameRate(char* str) const
{

    if (str != nullptr)
    {
        wsprintf(str, "FPS : %d", _frameRate);
    }
    return _frameRate;
}
