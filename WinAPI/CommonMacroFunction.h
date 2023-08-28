#pragma once
//일반적으로 사용하는 함수를 매크로화 시키겠다.

template <typename InterFaceType>
inline void SafeRelease(InterFaceType** currentScene)
{
	if (*currentScene != nullptr)
	{
		(*currentScene)->Release();
		*currentScene = nullptr;
	}
}

template <typename InterFaceType>
inline InterFaceType* safeAcquire(InterFaceType* newObject)
{
	if (newObject != nullptr)
	{
		//너희가 붙히고 싶은 함수
		newObject->AddRef();
	}
	return newObject;
}

// 새로운 객체를 붙일떄 이전 객체를 해제
template <typename InterFaceType>
inline void SafeSet(InterFaceType** currentObject, InterFaceType* newObject)
{
	safeAcquire(newObject);
	SafeRelease(&currentObject);
	currentObject = newObject;
}

inline HRESULT ExceptionToHResult()
{
	// if else 사용불가


	
	try //try : 예외 발생에 대한 검사 범위
	{
		throw;//이전 예외를 다시 던진다
	}

	catch (std::bad_alloc&) // chtch: try블록에서 발생한 예외를 처리한다.
	{			//bad_alloc : 배열 오버플로우나 동적할당not alloc
		return E_OUTOFMEMORY; //  일단 값은 모르겠고 널 찍어서 프로그램 살리고 보자
	}

	catch (...)
	{
		return E_FAIL;
	}


}

inline POINT PointMake(int x, int y)  //2d 방향벡터
{
	POINT pt = { x,y };
	return pt;
}

inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x,y,x + width,y + height };
	return rc;
}

inline void DrawRectMake(HDC hdc, RECT rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2 , y - height / 2 ,x + width / 2, y + height / 2 };

	return rc;
	
}

inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

inline void EllipaseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

inline void EllipaseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}


//충돌 영역 리사이징
inline RECT CollisionAreaResizing(RECT& rcDest, int width, int height)
{
	RECT rc =
	{
		rcDest.left + width / 2,
		rcDest.top + height / 2,
		rcDest.right + width / 2,
		rcDest.bottom + height / 2
	};
	return rc;
}

