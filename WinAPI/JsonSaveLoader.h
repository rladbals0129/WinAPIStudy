#pragma once
#include "SingletonBase.h"

#pragma region 제이슨 (JSON) 자바 스크립트 오브젝트 노테이션
/*
▶ 제이슨

- 제이슨은 객체의 구조와 속성을 텍스트 형식으로 전달하기 위해 고안된 형식이며 데이터 교환의 표준
	ㄴ 기본적으로 자바 스크립트 기반 표준 표기법이지만 다양한 언어를 지원하기에 확장성이 좋다
	ㄴ 주로 인터넷에서 데이터를 주고받을때 그 자료를 표현하는 방법으로 많이 활용이 된다
	ㄴ 텍스트 형식이기 때문에 사람에게도 아주 좋은 포맷
		ㄴ 문자열 기반이기 때문에 오버헤드가 적다.
		-서버에선 패킷을 주고받을때 사용하므로 필수스킬
		-클라에선 캐릭터 등 정보를 주고받을때 사용
 
 - 제이슨은 자료의 종류에 큰 제한은 없으며 특히 컴퓨터 프로그램의 변수값을 표현하는데 적합

 - 형식 자체가 자바 스크립트의 구문 형식을 따르지만 프로그래밍 언어나 "플랫폼"에 독립적이므로
 C / C++, C# , 자바 , 자바스크립트 , 펄 , 파이썬 ...등등.. 많은 언어에서 이용할 수 있다.

 - CSV, XML, HTML -> JSON "일반적인" 상황에서는 더 빠르다
 ㄴ 데이터의 형식과 성능을 고려하면 제이슨은 기본적으로 XML이라는 마크업 언어와 항상 고민을 하게한다. 
 
 -채용-
 XML: 메모리사용량을 고려해야하고 온라인의 여지가 있을때
 JSON : 속도를 빠르게 해야 할때.
 

 - 제이슨 형식에서 사용하는 기호

 {}: 객체
 키: 값: 객체가 가지는 속성
 "": 문자열 데이터
 []: 배열

 - C++ 에서 제이슨을 사용하려면 JsonCPP / Rapid Json을 사용하는것이 좋다
								속도면에선 Rapid Json이 압도적으로 유리 (터미널창 열려서 명령을주면됨) 

 - 


*/
#pragma endregion
class JsonSaveLoader : public SingletonBase<JsonSaveLoader>
{
private:
	void saveString(char* fileName, string data);
	void saveStringWithFileStream(char* fileName, string data);

	string loadString(char* fileName);
	string loadStringWithFileStream(char* fileName);

public:
	HRESULT init(void);
	void release(void);
	void saveJsonFile(char* fileName, Json::Value root);

	Json::Value loadJsonFile(char* fileName);


	JsonSaveLoader() {}
	~JsonSaveLoader() {}
};

