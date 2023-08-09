#pragma once
#include "SingletonBase.h"
#include "GImage.h"
#pragma region stl��
/*
--�̹���-- ����...
 ������
1. ��ü�� ���� new
2. ��������
 �� STL -> Map    ����� �����ϱ⿡�� ���� 
		// �˻��ӵ� ������ �ǹ̾����� unoderdMap (�˻��ӵ����� �ߺ�x)�� �ʿ���ڴ�

stl map
- Ű+ ���� ��������
�� ù��° first->Ű
�� �ι�° second ->��

-�߰��ϴ� ����� insert()�� ����ϰ� Ű�� ������ ���ÿ� �߰��ؾ� �ϴ� pair/make_pair�� ����� �߰��ؾ��Ѵ�

- pair() : �ΰ��� �ڷ����� �ϳ��� �����ִ� ����ü( ���ø��̱⶧���� � �ڷ����� ok)

- make_pair() : pair�� ����� �ִ� �Լ�
�� pair.first = x   pair.second =y;
�� pair = make_pair(x,y)

- �ϳ��� Ű�� �������� ���� �����ϰ� �ʹٸ� ��Ƽ���� ����ϴ� �͵� ���

- pair�� Ȯ����� ������ �ۼ��Ϥ��ų� �ټ��� ��ȯ���� ������ �ʹٸ� tuple�� ����ؾ� �Ѵ�.
*/
#pragma endregion
class ImageManager :public SingletonBase <ImageManager>
{
private:
	//typedef ������ : gdi gdi+�� �߰��ص� �����ְ� �̷����������� �ۼ���
	typedef map<string, GImage*> mapImageList;
	typedef map<string, GImage*>::iterator mapImageIter;
	// Q. �� ���⼱char�� �ƴ϶� string�� ������?? / ����Ʈ �����Ϳ� ����������char*�� ���� ��Եɱ�?
	//		�� char* �� �޸��ּҸ� ��� Ȯ�����ִ� �۾��� ���ܼ� ������
	//		�� ȣȯ�������� ����� �ִ�. ����ܰ�� ������ string������
	/*
	char*�� ����ϴ� ���, ���ڿ��� �޸� �ּҸ� ����ؼ� Ȯ�����־�� �ϹǷ� ������ ���ϵ� �� �ֽ��ϴ�.
	char*�� C ��Ÿ���� ���ڿ� ǥ�� ����̸�, C++������ ���ڿ��� �����ϰ� �ٷ�� ���� std::string�� ����ϴ� ���� �����ϴ�.
	std::string�� ���ڿ��� ���̸� �����ϰ� �޸� ���� ���� �ڵ����� ó���Ͽ� ������ ���ڿ� Ÿ���Դϴ�.
	std::string�� ����ϸ� ȣȯ�� ������ ������ �� ������, C++�� �پ��� ���ڿ� ó�� ��ɰ� ������ Ȱ���� �� �ֽ��ϴ�.
	����Ʈ �����͸� ����Ͽ� char*�� �����ϸ� �޸� ������ �������� ���Ǽ��� Ȯ���� �� �ֽ��ϴ�.
	����Ʈ �����ʹ� �޸� �Ҵ�� ������ �ڵ����� ó�����ֹǷ� �޸� ������ �߸��� �޸� ���� ���� ������ ������ �� �ֽ��ϴ�.
	����, ���� �ܰ迡���� std::string�� ����Ͽ� ���ڿ��� �ٷ�� ���� ����˴ϴ�.
*/
private:
	mapImageList _mImageList;
public:

	HRESULT init(void);
	void release(void);
	//GImage�� ���� ����Ŭ������.
	// �ܵ����� ó���Ҽ������� �׷���� 2���� �������� �����
	// 1. �����ӿ�ũ �ڵ� ����ġ
	// 2. ��ü�� (�̹���) �浹 ���ɼ��� �ִ�.
	GImage* addImage(string strKey,int width, int height);
	GImage* addImage(string strKey, const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	GImage* addImage(string strKey, const char* fileName, float x, float y, int width, int height,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));		
	GImage* addFrameImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	GImage* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height,
		int maxFrameX, int maxFrameY,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	GImage* findImage(string strKey);

	bool deleteImage(string strKey);
	bool deleteAll();
	//����

	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY); //��x�� ��y

	//�̹���Ŭ���� (�߶�׸���)
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHight);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHight, int destWidth, int destHight);

	//���ķ��� BYTE 0~255
	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHight, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int destWidth, int destHight, int sourX, int sourY, int sourWidth, int sourHight, BYTE alpha);

	//===================������ ����=================== 
	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY); 
	void loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	ImageManager() {}
	~ImageManager() {}
};

