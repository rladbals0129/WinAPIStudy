#include "stdafx.h"
#include "INIDataScene.h"

HRESULT INIDataScene::init(void)
{
    
    return S_OK;
}

void INIDataScene::release(void)
{
}

void INIDataScene::update(void)
{
    if (KEYMANAGER->isOnceKeyDown('9'))
    {
        INIDATA->addData("�뼮", "������", "10");
        INIDATA->addData("�ο�", "�ø��", "20");
        INIDATA->addData("����", "�ι���", "30");
        INIDATA->addData("ȣ��", "����", "40");
                         //�ɼ�, ���/������,  ��ġ

        INIDATA->iniSave("100��");
    }

    if (KEYMANAGER->isOnceKeyDown('0'))
    {
        int test = INIDATA->loadDataInteger("100��","�뼮","������");
        printf("�뼮: %d\n", test);
        int n = 0;

       // cout << n << endl;

    }
}

void INIDataScene::render()
{
}
