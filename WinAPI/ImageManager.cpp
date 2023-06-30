#include "Stdafx.h"
#include "ImageManager.h"




HRESULT ImageManager::init(void)
{
	//gdi���� ��� ���� // 
	return E_NOTIMPL;
}

void ImageManager::release(void)
{
	this->deleteAll();
}

GImage* ImageManager::addImage(string strKey, int width, int height)
{
	GImage* img = findImage(strKey); //�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ���ϰڴ�

	//�����͸� ����Ҷ� �׻� ����ó���� ������
	if (img) return img;//�ּҰ��� �̹� ���ִ� = �̹����� �̹� �ִ�-> �׷� ��������� �������� �׳� ����
	
	//�̹����� ����..
	img = new GImage;
	//�� �����ϱ� ���� �����


	if (FAILED(img->init(width, height))) //���� �̹��� ����µ� �����ߴٰ�??
	{
		SAFE_DELETE(img);	//������ �Ѽ������ʰڴ�
		return NULL;
	}
	//�� ���� ������ �ȵȴ� ��������

	//��Ȯ�ϰ� ������ִ°� ����.
	//_mImageList.insert(pair<string, GImage*>(strKey, img));
	//make_pair�� �����鼭 ���� �Լ��ΰŰ���.
	_mImageList.insert(make_pair(strKey, img));
	
	return img;
}

GImage* ImageManager::addImage(string strKey, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	GImage* img = findImage(strKey); 

	if (img) return img;

	img = new GImage;
	//���?
	if (FAILED(img->init(fileName,width, height,isTrans,transColor))) 
	{
		SAFE_DELETE(img);	
		/*
	
					nullptr?? NULL??
		//c/c++ -> ���Ǵ� ������ �����غ��� -> {}
			�� FAILED�ȿ��� ���ǰ��ִ� FAILED��winAPI���� ���ǵǾ��ִ°Ű� winAPI�� c����
				�� FAILED�ȿ� ���ǵǾ��ִ°��̴� c���ִ� NULL�� ����ߴ�.
				�� nullptr�� ����ص� ��������δ� ������ ���� 
				�� �ٵ�FAILED�� nullptr�� �𸥴� �ٵ��� ������������?
				�� FAILED�� nullptr�������� ���� �� �𸣴°Ŵ� GImage�� ����
					���̰Թ���?? ������ ã�°����� ���ľ��Ѵ�.
				�� NULL�� ������ �ƴ°��̴� �ٷκ�����.
				�� ������ �ӵ����� �ϳ������� �׳� �ƹ��ų����

		//1 .Ŭ����?
		//2. ������?? �����켱???
		int* 
		GImage* -> return ??  a. nullptr
		�� Ŭ�������� �� �������ִ� //GImage�ȿ� �� �����Ͱ� �������� �ְ�..


		//���� �ǰ� ���� �ȵɱ�?
		//1.
		return nullptr;
		//2.
		return NULL;
		*/
		return NULL;
	}
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

GImage* ImageManager::addImage(string strKey, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	GImage* img = findImage(strKey); 
	if (img) return img;	
	img = new GImage;	
	if (FAILED(img->init(fileName,x,y, width, height,isTrans,transColor))) 
	{
		SAFE_DELETE(img);
		return NULL;
	}
	_mImageList.insert(make_pair(strKey, img));
	return img;
}

GImage* ImageManager::addFrameImage(string strKey, const char * fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	GImage* img = findImage(strKey);
	if (img) return img;
	img = new GImage;
	if (FAILED(img->init(fileName,width, height, maxFrameX, maxFrameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}
	_mImageList.insert(make_pair(strKey, img));
	return img;
}

GImage * ImageManager::addFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	GImage* img = findImage(strKey);
	if (img) return img;
	img = new GImage;
	if (FAILED(img->init(fileName, x, y, width, height, maxFrameX, maxFrameY,isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}
	_mImageList.insert(make_pair(strKey, img));
	return img;
}

GImage* ImageManager::findImage(string strKey)
{
	auto key = _mImageList.find(strKey);	//�˻�Ű

	if (key != _mImageList.end())	 //find. Key�� �̿��Ͽ� iterator�� �����ɴϴ�. ã�� �� ���ٸ� map.end()�� ��ȯ�մϴ�.
	{
		return key->second;		//�� Ž���� ����
	}
	return nullptr;
}

bool ImageManager::deleteImage(string strKey)
{
	auto key = _mImageList.find(strKey);
	if (key != _mImageList.end())
	{
		key->second->release();
		SAFE_DELETE(key->second);
		_mImageList.erase(key);

		return true;
	}
	return false;
}

bool ImageManager::deleteAll()
{
	auto iter = _mImageList.begin();
	for (; iter != _mImageList.end();)
	{
		if (iter->second != NULL) //�̹����� �ִٸ�
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter); //���ͷ����ͷ� ��Ʈ�����̴� _mImageList.erase(iter);�� ����ȵǰ� iter=�� �������
		}
		else
		{ 
			++iter;
		}
	}
	_mImageList.clear();
	return true;
}

void ImageManager::render(string strKey, HDC hdc)
{
	GImage* img = findImage(strKey);
	if (img) img->render(hdc);


}

void ImageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	GImage* img = findImage(strKey);
	if (img) img->render(hdc,destX,destY);

}

void ImageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHight)
{
	GImage* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY,sourX,sourY,sourWidth, sourHight);
}

void ImageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHight, int destWidth, int destHight)
{

}

void ImageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
	GImage* img = findImage(strKey);
	if (img) img->alphaRender(hdc,alpha);
}

void ImageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	GImage* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void ImageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHight, BYTE alpha)
{
	GImage* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHight,alpha);
}

void ImageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int destWidth, int destHight, int sourX, int sourY, int sourWidth, int sourHight, BYTE alpha)
{
	GImage* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, destWidth, destHight, sourX, sourY, sourWidth, sourHight, alpha);
}

void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	GImage* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY);
}

void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	GImage* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}
