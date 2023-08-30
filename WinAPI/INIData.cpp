#include "stdafx.h"
#include "INIData.h"

HRESULT INIData::init(void)
{
	return S_OK;
}

void INIData::release(void)
{
	// ! Do Nothing
}

void INIData::addData(char* section, char* key, char* value)
{
	tagIniData iniData;
	iniData.section = section;
	iniData.key = key;
	iniData.value = value;

	arrIniData vIniData;
	vIniData.push_back(iniData);

	_vIniData.push_back(vIniData);

}

void INIData::iniSave(char* fileName)
{
	char str[256];
	char dir[256];

	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));

	sprintf_s(dir, "\\INIData/%s.ini", fileName);

	GetCurrentDirectory(256, str);

	//���ڿ� ����
	// �������� ���ϸ� ��������.
	strcat_s(str, dir);
	
	for (int i = 0; i < _vIniData.size(); i++)
	{
		arrIniData vData = _vIniData[i];

		//�б���. �� � ���� ����? -> INI
		//WritePrivateProfileString() : ���Ͽ� ����(���ڿ�)�� ���� ���࿡ �ش� ���ǰ� Ű���� ������
		//													�ڵ����� ������ ��Ų��
		WritePrivateProfileString
		(
			vData[0].section,
			vData[0].key,
			vData[0].value,
			str
		);
			vData.clear();
	
	}

	_vIniData.clear();

}

char* INIData::loadDataString(char* fileName, char* section, char* key)
{
	char str[256];
	char dir[256];

	ZeroMemory(str, strlen(str));
	ZeroMemory(dir, strlen(dir));

	sprintf_s(dir, "\\INIData/%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strcat_s(str, dir);

	char data[64] = { NULL, };
	//���� �б�
	GetPrivateProfileString
	(
		section,			// �о�� ������ �ִ� ������ �̸�
		key,				// �о�� ������ �̸�
		"", //�����尪. ��	// �����̸��̳� Ű �̸��� ã�� ���ϸ� ����� ���ڿ�
		data,				// Ű������ ����Ű�� ���� ������ ����
		64,					// Ű���� ������ ���� ������
		str					// 
	);

	return data;
}

int INIData::loadDataInteger(char* fileName, char* section, char* key)
{
	char str[256];
	char dir[256];

	ZeroMemory(str, strlen(str));
	ZeroMemory(dir, strlen(dir));

	sprintf_s(dir, "\\INIData/%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strcat_s(str, dir);

	return GetPrivateProfileInt(section,key,0,str);
}
