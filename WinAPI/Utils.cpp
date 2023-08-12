#include "Utils.h"
#include "stdafx.h"
namespace MY_UTIL
{
	// ���������� �Ÿ�
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrt(x * x + y * y);
	}

	//��ŸƮ -> ���� -> ���� ��������
	float getAngle(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX; //x����
		float y = endY - startY; //y����
		float d = sqrt(x * x + y * y);//���������� �Ÿ�

		float angle = acos(x / d); //���������� �����ϴ� ���Ϳ� x�� ���Ⱓ�� ���� ���
		//

		if (y > 0) angle = PI_2 - angle;

		return angle;
	}


}

//��......... ��� ȿ�������� ������ ���� ���̳�
//stdafx


