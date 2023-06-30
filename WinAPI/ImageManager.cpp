#include "Stdafx.h"
#include "ImageManager.h"




HRESULT ImageManager::init(void)
{
	//gdi에선 사용 안함 // 
	return E_NOTIMPL;
}

void ImageManager::release(void)
{
	this->deleteAll();
}

GImage* ImageManager::addImage(string strKey, int width, int height)
{
	GImage* img = findImage(strKey); //추가하려는 이미지가 존재하는지 키값으로 확인하겠다

	//포인터를 사용할땐 항상 예외처리를 해주자
	if (img) return img;//주소값이 이미 차있다 = 이미지가 이미 있다-> 그럼 쓸대없는짓 하지말고 그냥 뱉어라
	
	//이미지가 없다..
	img = new GImage;
	//ㄴ 없으니까 새로 만든다


	if (FAILED(img->init(width, height))) //만약 이미지 만드는데 실패했다고??
	{
		SAFE_DELETE(img);	//원본을 훼손하지않겠다
		return NULL;
	}
	//ㄴ 여긴 들어오면 안된다 터진경우다

	//정확하게 명시해주는거 같다.
	//_mImageList.insert(pair<string, GImage*>(strKey, img));
	//make_pair가 들어오면서 뭔가 함수인거같다.
	_mImageList.insert(make_pair(strKey, img));
	
	return img;
}

GImage* ImageManager::addImage(string strKey, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	GImage* img = findImage(strKey); 

	if (img) return img;

	img = new GImage;
	//재귀?
	if (FAILED(img->init(fileName,width, height,isTrans,transColor))) 
	{
		SAFE_DELETE(img);	
		/*
	
					nullptr?? NULL??
		//c/c++ -> 사용되는 지역을 생각해보자 -> {}
			ㄴ FAILED안에서 사용되고있다 FAILED는winAPI에서 정의되어있는거고 winAPI는 c언어다
				ㄴ FAILED안에 정의되어있는것이니 c언어에있는 NULL을 사용했다.
				ㄴ nullptr을 사용해도 결과적으로는 문제가 없다 
				ㄴ 근데FAILED는 nullptr을 모른다 근데왜 문제가없을까?
				ㄴ FAILED는 nullptr을만나는 순간 난 모르는거니 GImage에 들어간다
					ㄴ이게뭐야?? 라고물어보고 찾는과정을 거쳐야한다.
				ㄴ NULL을 만나면 아는것이니 바로빠진다.
				ㄴ 솔찍히 속도차이 하나도없다 그냥 아무거나써라

		//1 .클래스?
		//2. 포인터?? 누가우선???
		int* 
		GImage* -> return ??  a. nullptr
		ㄴ 클래스쪽이 더 우위에있다 //GImage안에 또 포인터가 있을수도 있고..


		//누군 되고 누군 안될까?
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
	auto key = _mImageList.find(strKey);	//검색키

	if (key != _mImageList.end())	 //find. Key를 이용하여 iterator를 가져옵니다. 찾을 수 없다면 map.end()를 반환합니다.
	{
		return key->second;		//값 탐색후 ㄹ턴
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
		if (iter->second != NULL) //이미지가 있다면
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter); //이터레이터로 컨트롤중이니 _mImageList.erase(iter);로 쓰면안되고 iter=을 해줘야함
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
