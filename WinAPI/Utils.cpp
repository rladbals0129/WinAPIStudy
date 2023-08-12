#include "Utils.h"
#include "stdafx.h"
namespace MY_UTIL
{
	// 두점사이의 거리
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrt(x * x + y * y);
	}

	//스타트 -> 엔드 -> 각을 라디안으로
	float getAngle(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX; //x차이
		float y = endY - startY; //y차이
		float d = sqrt(x * x + y * y);//두점사이의 거리

		float angle = acos(x / d); //시작점끝점 연결하는 벡터와 x축 방향간의 각도 계산
		//

		if (y > 0) angle = PI_2 - angle;

		return angle;
	}


}

//흠......... 어떻게 효율적으로 전달을 해줄 것이냐
//stdafx


