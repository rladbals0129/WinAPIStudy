#include "stdafx.h"
#include "JsonSaveLoader.h"

// UTF-8 ....

HRESULT JsonSaveLoader::init(void)
{
	//Ȯ���� �Ǹ� ���Ű� ������NULL
	return S_OK;
}

void JsonSaveLoader::release(void)
{
	//Ȯ���� �Ǹ� ���Ű� ������NULL
}



void JsonSaveLoader::saveString(char* fileName, string data)
{
	TCHAR* buf = (TCHAR*)data.c_str();

	//HANDLE : �����쿡�� �ο��� ���� �ĺ���ȣ
	// �� ���������� 32��Ʈ ������
	HANDLE file;
	/*		�����ڵ����
	������Ʈ ���� ǥ��(BOM)

	- ��ǻ�ʹ� �����͸� �޸𸮿� �����ҋ� ����Ʈ ������ ������ �����Ѵ�.

	- ����Ʈ ���� ǥ���� ����Ʈ ������ ǥ���ϴ� ������ ���� �� �տ� ���ڵ� ��Ŀ� ���õ� ���ڸ� �־ 
	���ڵ� ����� ǥ���ϴ� ��

	- �Ϲ����� �����Ϳ����� �� BOM�� Ȯ���� �� ���� ��� �����ͷ� �������� Ȯ���� �� �ִ�.

	- �������� ��� ���ڵ� ����̳� ����� ��Ŀ� ���� ����Ʈ ���� ǥ���� �ʿ��� ��찡 ���� ����.
	
	0xFEFF 

	���� ���� ���ϸ� �����ʺ��� �о���� UTF-8 .... �̰ŋ���


	�� ������ -> UTF-16����� ��� 0xFEFF�� BOM���� ����Ѵ�
		�� �ݴ�� ��Ʋ ����� ��� 0xFFFE�� ǥ���Ѵ�.

    �� UTF-16�� �����ڵ� ����̱� ������ �ѱ��� 2����Ʈ�� ó���Ѵ�.
	�� �޸� �������� ������ ��ų �� �ִ�. -> �ƽ�Ű ȣȯx
	�� ��Ȥ���� ���ڰ� �����ų� �ּ��� ������ ���̸�< ���ڵ����� > (�ڵ�)

	�� ����� (��𼭺���������)

	- ��ǻ�� ��Ű��ó���� ���� �߿��� ����

	- ������� ǥ���� ������ CPU ȸ�縶�� ���� ���Ǹ� �� ����̱� ������  CPU ȸ�縶�� ó���ϴ� 
	����� ����� �ٸ���. ( ����/�ϵ�  -> ��Ʋ�����)

	- ����ȿ� ���� ���ٸ� ó���� ���� �ʾҴٸ� �����ʹ� �����ּҿ��� �����ּҷ� ���ʴ�� �����̵�.


	- �� ����� : �� -> ��
	�� �޸𸮿� ����� ���� �״�� ���� �� ������ ����� �����ϱⰡ ���� ����.
	�� ���� ģ���� �����̱� ������ ���� ������ �����ϴ�.


	- ��Ʋ����� : �� <- ��
	�� ��Ʋ���� ��� ��� ����� ���ڸ� ����ϴ� ���� ��İ��� �ٸ��� �Ųٷ� �о�� �Ѵ�
	�� �޸𸮿� ����� ���� ���� ����Ʈ�� ��� �� �� ������ ������ �ʿ� ���� ��찡 ���� ������ 
	������ ���ų� / ���������� �����ϴ�. (�ο��� �����ͺ��� ã�⶧����)


	�� �̷��� ������ ������ �� �𸣰ڴٸ� �׳� 0xFEFF ���� �����ϸ� ����ģ��
	��? -> �츮�������쾲�����ݾ�
	*/
	WORD BOM = 0xFEFF;  //����Ʈ ���� ��Ŀ BOM  ex) �޸��� // �����쿡�� ä���ϴ� ����� 0xFEFF;
	DWORD dwBytes = 0;  
	DWORD dwRead;

	/*
	CreateFile(): ���� ����� ��ġ�� ����ų� �о���� ����� �� �ִ� �ڵ� ��ȯ
	
	*/
	file = CreateFile
	(
		fileName,						// �����ϰų� �� ������ �̸�
		GENERIC_WRITE,					// ���� ����Ÿ�� (������������ ���������� ���� ���Ⱚ�� �ٲ�����)
		0,								// ������ 0 (������ �����ʰڴ� -> �޸� �ν��Ͻ��� �������� �ٸ� ��ü�鿡��)
		NULL,							// ��� ����
		CREATE_ALWAYS,					// ���ο� ���� ���� -> ������ ���� ���� �� ��-> �����
		FILE_ATTRIBUTE_NORMAL,			// ���Ͽ� ���� �Ӽ������� �Ϲ����� �Ӽ��� �������� �ʰڴ�.
		NULL							// ���¿� ���� ����
	);

	// 0(false) / 1(true) / WinAPI���� -1 �� (fail)���� 
	//INVALID_HANDLE_VALUE : �ַ� �ʱ�ȭ�� ����� �ȴ� -> �Ϲ������� -1�� ���ǵǾ��ִ�.
	if (file == INVALID_HANDLE_VALUE)
	{
		MessageBox(_hWnd, "���� ���� ����", "����", MB_OK);

	}
	else
	{
		// �Ϲ����� ���� 
	//	WriteFile(file, &BOM, 2, &dwBytes, NULL);
	// c/c++����
		WriteFile(file, buf, strlen(buf) * sizeof(TCHAR), &dwRead, NULL);
		CloseHandle(file); // ������ ���� ��Ÿ���� ����
	}

}

void JsonSaveLoader::saveStringWithFileStream(char* fileName, string data)
{
	ofstream outFile(fileName);

	outFile << data << endl;

	outFile.close();
}

string JsonSaveLoader::loadString(char* fileName)
{
	// 8192 : Ŭ�󿡼� ����ϴ� �ֻ��� ��Ʈ -> ���� -> ��Ĺ ���۶�� �θ���.
	// ����� -> byte(1 ~ 8) / word (2 ~ 16 ) / dword  (4 ~ 32)/ qword (8~64)
	// �� 1��Ʈ(������) -> 8��Ʈ (1����Ʈ) -> 2����Ʈ -> 1 word


	TCHAR buf[8192]; //������Ҷ� ���̳��� 
	ZeroMemory(buf, sizeof(buf));

	
	HANDLE file;
	DWORD dwBytes;

	file = CreateFile
	(
		fileName,						
		GENERIC_READ,					//�Ϲ����� ���·� �о���̰ڴ�
		0,								
		NULL,							
		OPEN_EXISTING,					// ������ �����Ҷ��� ����.
		FILE_ATTRIBUTE_NORMAL,			
		NULL							
	);

	if (file == INVALID_HANDLE_VALUE)
	{
		MessageBox(_hWnd, "���� ���� ����", "����", MB_OK);
		
		return "";
	}
	else
	{
		ReadFile(file, buf, 8192, &dwBytes, NULL);
		CloseHandle(file); 
	}
	// ������ ����� �����Ѵ�.
	return string(buf);
}

//�ٽ�
string JsonSaveLoader::loadStringWithFileStream(char* fileName)
{
	ifstream fileIn;
	// �ھ� ������ -> cpu ��ĳ�ٸ�          ª�� �����ְ� ������ �ݾ������
	fileIn.open(fileName, ios::in); //���� ������ cpu�ھ ��� �װ� ó���ؼ� ������ó���ϰ� ������
	// �� �޸� ������ ���� cpu�� �ҷ����� (c++����)			����ִ�cpu�� �� ���
	/*
	ios::in -> ������ �����ϰڴ�. (�б⸸ ������ ���·�)
	ios::out -> ���ϰ���(���⸸ ����)
	
	ios:ate -> �����ǳ����� ���� �����͸� �̵� ��Ų��. (������ �����Ҷ�)
	ios:app -> ������ �߰�(������ ���ʺ���)
	ios::binary -> ���̳ʸ� ���� ���� (���� ������Ҷ� ���)

	*/


	//cpu��ĳ�ٸ� ��Ӱ���? �˻�
	
	char data;
	string jsonStr;

	while (fileIn.get(data))
	{
		jsonStr += data;
	}
	fileIn.close();


	return jsonStr;
}


void JsonSaveLoader::saveJsonFile(char* fileName, Json::Value root)
{
	Json::StyledWriter writer;
	string outputConfig = writer.write(root);

	saveStringWithFileStream(fileName, outputConfig);
}

Json::Value JsonSaveLoader::loadJsonFile(char* fileName)
{
	string jsonStr = loadStringWithFileStream(fileName);

	if (jsonStr == "")
	{
		MessageBox(_hWnd, "�����Ͱ� ����", "���", MB_OK);
		return NULL;
	}

	Json::Reader reader;
	Json::Value root;

	// parsing (�Ľ�): Ư�� ������ �о�鿩�� �̸� �ٸ� ���α׷��̳� ���� ��ƾ�� ����� �� �ִ�
	// ���� ǥ�� ������� ��ȯ ���ִ°�
	bool parsingRet = reader.parse(jsonStr, root);
	//							�� parse: �Ľ��� �ϴ� ���μ���

	if (!parsingRet)
	{

		string errorMsg = reader.getFormatedErrorMessages();
		MessageBox(_hWnd, errorMsg.c_str(), "����", MB_OK);
		PostQuitMessage(0); 
		//�ش������� �޼����ڽ��� ���� ����?? ->�ٸ������� �ƴ�json������. ��°� �˸�������
		//�ܺ� ���̺귯���⋚���� �츮 �����Ϸ��� ������ ������������ ��
	}


	return root;

	//�Ľ�?
}

