#pragma once
//�Ϲ������� ����ϴ� �Լ��� ��ũ��ȭ ��Ű�ڴ�.

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
		//���� ������ ���� �Լ�
		newObject->AddRef();
	}
	return newObject;
}

// ���ο� ��ü�� ���ϋ� ���� ��ü�� ����
template <typename InterFaceType>
inline void SafeSet(InterFaceType** currentObject, InterFaceType* newObject)
{
	safeAcquire(newObject);
	SafeRelease(&currentObject);
	currentObject = newObject;
}

inline HRESULT ExceptionToHResult()
{
	// if else ���Ұ�


	
	try //try : ���� �߻��� ���� �˻� ����
	{
		throw;//���� ���ܸ� �ٽ� ������
	}

	catch (std::bad_alloc&) // chtch: try��Ͽ��� �߻��� ���ܸ� ó���Ѵ�.
	{			//bad_alloc : �迭 �����÷ο쳪 �����Ҵ�not alloc
		return E_OUTOFMEMORY; //  �ϴ� ���� �𸣰ڰ� �� �� ���α׷� �츮�� ����
	}

	catch (...)
	{
		return E_FAIL;
	}


}

inline POINT PointMake(int x, int y)  //2d ���⺤��
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


//�浹 ���� ������¡
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

