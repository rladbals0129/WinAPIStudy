#include "stdafx.h"
#include "FontManager.h"

//char*
void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontweight, char* printString, int length, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT); 
	/*
font = CreateFopnt
(
	v����ũ��, ������, ����(��ü), ���� ����, v���� ����,
	����( t / f ), ����( t / f ), ��Ҽ�,
	v���ڼ���, ��� ��Ȯ��, Ŭ���� ��Ȯ��, ����� ��, �ڰ�, v��Ʈ
);
*/
	HFONT font = CreateFont
	(
		fontSize,
		0,
		0,
		0,
		fontweight,
		0,
		0, 
		0,
		HANGEUL_CHARSET,
		0,
		0,
		0,
		0,
		TEXT(fontName)
	);

	//auto font = (HFONT)SelectObject(hdc, font);
	auto oldFont = (HFONT)SelectObject(hdc, font);;

	SetTextColor(hdc, color);

	const int stringLength = strlen(printString);
	wchar_t charBuffer[256];
	//ZeroMemory(charBuffer, stringLength);

	TextOut(hdc,destX,destY,printString,stringLength);
	//TextOutW(hdc,);
	

	SelectObject(hdc, oldFont);
	DeleteObject(font);// �õ���Ʈ�� �־��ְ� ���̻󾵸������ ����Ʈ���ش�
}

//Ȯ�强������  LPCWSTR
void FontManager::drawText(HDC hdc, int destX, int destY, char * fontName, int fontSize, int fontweight, LPCWSTR printString, int length, COLORREF color)
{

}

//�迭�� ���
void FontManager::drawText(HDC hdc, int destX, int destY, char * fontName, int fontSize, int fontweight,  LPCWSTR* printStringArr, int length, COLORREF color)
{
	//�� ����
	//int arraySize = sizeof(printStringArr) / sizeof(*printStringArr);
	//
	//int lineCount = 0;
	//for (int i = 0; i < arraySize; i++)
	//{
	//	if (i==0)
	//	{
	//		if () {}

	//		else
	//		{
	//			break;
	//		}
	//		
	//	}
	//	else
	//	{

 //}
	//}

}

