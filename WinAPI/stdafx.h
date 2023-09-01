#pragma once
//��� ����
#pragma warning(disable : 4005)
// 4005: DXGI �� �׷��� �������̽����� ��ũ�� �����Ͽ� ��µǴ� ���

/*
�� Stdafx

- MS�� ���־� ��Ʃ��ø� �̿��Ͽ� ������Ʈ�� ����� �����Ǵ� Ŭ�����̴�
	�� �� ģ���� �ǹ��ϴ� �ٴ� ǥ�� ���ø����̼� ������ ��ũ�� ��

- ���ҿ��� �����ڵ��� �ɷ� ����� ���� ������ PCH����
	�� ���� ���̴� �������� ������� �̸� �������صξ� ���� �ٽ� ������ ���� �ʰ� ����ϰ� �ȴ�.

- ������ �ʱ� ����ܰ迡���� �� �ʿ伺�� ���������� ��������� ũ�Ⱑ Ŀ���ų� ���� ����������
Ȱ�뵵 �� ȿ���� �޻���Ѵ�.


*/

//SDKDDKVER.h �� ���α׷����� ������ os�� ���� or ���̺귯���� ���� Windows �������
//�ڵ忡 ���赵�� �Լ�/��� ���� �����ϴµ� ��� �Ѵ�.
#include <SDKDDKVER.h>

#include "targetver.h"

//#include <ole2.h>
// GDI+ �� ����Ϸ��� ������Ͽ��� �����;� �Ѵ�.
#define WIN32_LEAN_AND_MEAN

//�ܼ�â
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")  //?
//���̺귯�� �߰�
#pragma comment (lib,"msimg32.lib")
#pragma comment (lib,"lib/FMOD/fmodex_vc.lib")

#pragma comment (lib,"JsonCPP/lib_json/json_vc71_libmtd.lib")



#include <windows.h>

//�ܺ� �ش�
#include "inc/FMOD/fmod.hpp"
#include "JsonCPP/include/json/json.h"


//! C��Ÿ�� �������
#include <stdlib.h> // C��� ǥ�� ���̺귯�� �Լ�
#include <malloc.h>// C���� �޸� �Ҵ��Ҷ� ����Ѵ�
#include <memory.h> // �޸� ���� ������� memset,memcpy(windows����� ���Ե�(���������ؼ�))
#include <tchar.h> //
#include <time.h>

/*
�����ڿ� ��

- �����쿡�� ����� ���ڿ� ��� ����(����) ��(TextOut, DrawText, wsprinf ���)
�� �⺻������ �����ڵ���

MBCS (��Ƽ����Ʈ ĳ���� ��)

- ������ ����ϴ� ��Ƽ����Ʈ ������ ���ڿ��� ���Ѵ�
- ��Ƽ����Ʈ �ڵ�� ����� �ƽ�Ű �ڵ忡 ����Ǵ� ���ڴ� 1����Ʈ�� ǥ���ϰ�
  ���Ե��� �ʴ� ���ڴ� 2����Ʈ�� ö�Ѵ�

WBCS (���̵� ����Ʈ ĳ���� ��)

- ��� ���ڸ� 2����Ʈ�� ó���ϸ� �����ڵ� ����̴�

�� �����ڵ�� ��Ƽ����Ʈ�� ���

- VS������ ���߽� ��Ƽ����Ʈ / �����ڵ� ������ �⺻������ ������ ����� �Ѵ�.

- �����ڵ��� ��쿡�� ���ڿ��� ""�� ���ΰ� �� �տ� L�� ������ (L"")�̶�� ǥ���Ѵ�

- ��Ƽ����Ʈ ���� �Ͽ쿡�� �׳� ""�� ����ϸ� �ȴ�.

- �����ڵ�� ���ߵ� ���α׷��� ��Ƽ����Ʈ�� �̽��Ϸ���
�̵� ���ڿ��� ǥ������� �ٽ� ������� �ϱ⶧���� �ſ� �����ϴ�.
�� �׷��� _T ��ũ�θ� ����ؾ� �Ѵ�.

- ���ڿ��� ����ǥ�� ���ΰ� �����ڵ忡�� ����� "L"��� "_T"�� ����ϸ�
��ũ�ΰ� �˾Ƽ� ���� ȯ�濡 �°� ġȯ���ش�.

*/
#include <stdio.h> //ǥ�� ����� �������


//! C++��Ÿ�� ��� ����
#include <iostream>
/*
chrono
- c++11���� �߰��� �ð� ���� ���̺귯��(STL)
�� ���� c��Ÿ�ӿ��� �����ϴ� time�Լ����� �پ��� / Ȯ��� ����� �����Ѵ�.
�� ����: ���е��� ����.(���� �и� �� ����)
	�� time�Լ��� �ʴ��� ���� ������ �����ϱ� ������ �������� ������ ���ۿ� ����
�� OS�� ���������� ������ �Ѵ�.
*/
#include <chrono>
#include <random>
#include <vector>
#include <map>
#include <unordered_map> //Hash �ڷᱸ��
//�� �Ϲ��� ��Ȳ���� MAP���� �˻� �ӵ��� �� ������.
// �� ���� ������ �ߺ��� �����͸� ������� �ʱ� ������
//	�� ��. ���絥���Ͱ� ������(key) �ؽ� �浹�� �߻��� ������ ����� ������ ���� ���ϰ� �߻��Ѵ�.
#include <cassert> //c++���α׷����� ���. -> �� ����
#include <bitset>// ��Ʈ������ �� �� ���� �������ִ� �Լ��� �����ϴ� STL
// �� reset(),set(),flip(),all(),any(),size() ���..

#include <algorithm> //����
//�Լ� ������ ����ó�� �ְ�������ִ�
//bind : Ư�� ���ڿ� ���ؼ��� �Լ��� �����Ű�������/Ư�����ڿ� Ư�� �Լ��� ���������
// �� �Լ�������->�̺�Ʈ->Ʈ����->��������Ʈ->�׼�Ʈ����->����������
//�츮�� �����־���. ���������ν���(�ݹ��Լ�)
#include <functional>
#include <fstream>
#include <queue>
#include <deque>

using namespace std;
/*
//D2D/D3D ��� ����
#include <D2D1.h>
#include <d2d1helper.h>
#include <d3dx0.h>
#include <D3DX11.h>
#include <d3d11shader.h>
#include <dinput.h>

#pragma comment (lib,"d2d1.lib")
#pragma comment (lib,"d3d9.lib")
#pragma comment (lib,"d3dx9.lib")
#pragma comment (lib,"d3d11.lib")
#pragma comment (lib,"d3dx11.lib")
#pragma comment (lib,"dinput8.lib")
#pragma comment (lib,"dxguid.lib")

ID2D1Factory* _ID2DFactory = nullptr;
ID2D1HwndRenderTarget* _ID2DRenderTarget = nullptr;
 */

// �� ����� ���� �ش����ϸ�
#include "CommonMacroFunction.h"
#include "RandomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "TempSoundManager.h"
#include "Utils.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "INIData.h"
#include "SoundManager.h"
using namespace MY_UTIL;

// # �̱��� #
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define FONTMANAGER FontManager::getSingleton()
#define TEMPSOUNDMANAGER TempSoundManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()
#define INIDATA INIData::getSingleton()
#define SOUNDMANAGER SoundManager::getSingleton()

//Ÿ��Ʋ
#define WINNAME		(LPTSTR)(TEXT("WindowsAPI"))

// !��üȭ��
//#define FULLSCREEN

#ifdef FULLSCREEN

#define WINSTART_X	0
#define WINSTART_Y	0
#define WINSIZE_X	GetSystemMetrics(SM_CXSCREEN) //GetSystemMetrics()���ڷ� ���޵Ǵ� �ý��� ���� ������ ��ȯ
#define WINSIZE_Y	GetSystemMetrics(SM_CYSCREEN) //SM_CXSCREEN ,SM_CYSCREEN ���� ȭ�� �ػ� ��ȯ(x,y��) 
#define WINSTYLE	WS_POPUPWINDOW | WS_MAXIMIZE

#else

#define WINSTART_X	0
#define WINSTART_Y	0
#define WINSIZE_X	600
#define WINSIZE_Y	800
#define WINSTYLE	WS_CAPTION | WS_SYSMENU
#endif

// #��ũ��# (������ â �ʱ�ȭ)
//#define WINNAME		(LPTSTR)(TEXT("WindowsAPI"))
//#define WINSTART_X	0
//#define WINSTART_Y	0
//#define WINSIZE_X	1280
//#define WINSIZE_Y	800
////WS_CAPTION : Ÿ��Ʋ�ٸ� ������ ���� �ɼ�
////WS_SYSMENU : ���� ǥ���ٿ� ��Ʈ�� �޴� ���� â
//#define WINSTYLE	WS_CAPTION | WS_SYSMENU

//# ��ũ�� �Լ� #   -> ��ũ���Լ��� ���ٸ��ν� �̾������� �Ʒ�ó�� \ �� �������
// (Ŭ�������� �����Ҵ�� �κ� ����)
#define SAFE_DELETE(p) {if(p) { delete (p); (p) = nullptr; }}
#define SAFE_DELETE_ARRAY(p) {if(p) { delete[] (p); (p) = nullptr; }}
#define SAFE_RELEASE(p)	{if(p) {(p)->release(); (p) = nullptr; }}
#define SAFE_RELEASE_SCNEN(p) {if(p) {(p)->Release(); (p) = nullptr; }}

// ���Ͻ��� / �÷����� / ����					  /   ����    / RPG / ����  -> ���� �帣 ��õ
//  �� ������          ���ﰢ�Լ��� ���õǾ���� 
//

// # ���� ���� # (������ ����, ������Ʈ ��ü���� ���ٰ����ؼ� �����ؾ���)
//		��(ex - �÷��̾� �κ��丮 ��õ)
//static vs extern   ?? 
// static �� ���̻� ������ �ƴϰ� �ٲ��ټ� �ִ�.
// extern �� ������Ʈ�� ���������� ��� ����
// ��externŰ����� �ٸ���� /cpp ���� ������ �����ؼ� ���� ���� ����Ѵ�
// ����ü
// �⺻������ ���������� externŰ���带 �����ص� �⺻������ externȭ �Ǵ� ��찡 ����. (��ø� ��������)
// ID2D1HwndRenderTarget* _ID2DRenderTarget = nullptr; <- �̰Ŵ� �ȵȴ�. nullptr�� �ƴ϶� ��Ȯ�� ��ø� �������
//	�� Ŭ������ �����ϰ��ִ� �����ͺ���

//��������
extern HINSTANCE _hInstance;
extern HWND      _hWnd;

extern POINT	 _ptMouse;
// �� x��ǥ�� y��ǥ�� ����� ��ǥ�� �����ҋ� ����� �Ѵ�. (ex ->���콺 Ŀ�� why? ���������� �ɼ��� �ѵ� ���콺�� ��� �����ϱ�.)
//			���������� ���� ����.


