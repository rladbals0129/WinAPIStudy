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
        INIDATA->addData("용석", "무서움", "10");
        INIDATA->addData("민우", "시리어스", "20");
        INIDATA->addData("기태", "민방위", "30");
        INIDATA->addData("호영", "군대", "40");
                         //옵션, 밝기/사운드등등,  수치

        INIDATA->iniSave("100팀");
    }

    if (KEYMANAGER->isOnceKeyDown('0'))
    {
        int test = INIDATA->loadDataInteger("100팀","용석","무서움");
        printf("용석: %d\n", test);
        int n = 0;

       // cout << n << endl;

    }
}

void INIDataScene::render()
{
}
