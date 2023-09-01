#pragma once
#include "SingletonBase.h"

#pragma region ���̽� (JSON) �ڹ� ��ũ��Ʈ ������Ʈ �����̼�
/*
�� ���̽�

- ���̽��� ��ü�� ������ �Ӽ��� �ؽ�Ʈ �������� �����ϱ� ���� ��ȵ� �����̸� ������ ��ȯ�� ǥ��
	�� �⺻������ �ڹ� ��ũ��Ʈ ��� ǥ�� ǥ��������� �پ��� �� �����ϱ⿡ Ȯ�强�� ����
	�� �ַ� ���ͳݿ��� �����͸� �ְ������ �� �ڷḦ ǥ���ϴ� ������� ���� Ȱ���� �ȴ�
	�� �ؽ�Ʈ �����̱� ������ ������Ե� ���� ���� ����
		�� ���ڿ� ����̱� ������ ������尡 ����.
		-�������� ��Ŷ�� �ְ������ ����ϹǷ� �ʼ���ų
		-Ŭ�󿡼� ĳ���� �� ������ �ְ������ ���
 
 - ���̽��� �ڷ��� ������ ū ������ ������ Ư�� ��ǻ�� ���α׷��� �������� ǥ���ϴµ� ����

 - ���� ��ü�� �ڹ� ��ũ��Ʈ�� ���� ������ �������� ���α׷��� �� "�÷���"�� �������̹Ƿ�
 C / C++, C# , �ڹ� , �ڹٽ�ũ��Ʈ , �� , ���̽� ...���.. ���� ���� �̿��� �� �ִ�.

 - CSV, XML, HTML -> JSON "�Ϲ�����" ��Ȳ������ �� ������
 �� �������� ���İ� ������ ����ϸ� ���̽��� �⺻������ XML�̶�� ��ũ�� ���� �׻� ����� �ϰ��Ѵ�. 
 
 -ä��-
 XML: �޸𸮻�뷮�� ����ؾ��ϰ� �¶����� ������ ������
 JSON : �ӵ��� ������ �ؾ� �Ҷ�.
 

 - ���̽� ���Ŀ��� ����ϴ� ��ȣ

 {}: ��ü
 Ű: ��: ��ü�� ������ �Ӽ�
 "": ���ڿ� ������
 []: �迭

 - C++ ���� ���̽��� ����Ϸ��� JsonCPP / Rapid Json�� ����ϴ°��� ����
								�ӵ��鿡�� Rapid Json�� �е������� ���� (�͹̳�â ������ ������ָ��) 

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

