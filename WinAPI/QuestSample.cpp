#include "stdafx.h"
#include "QuestSample.h"


void QuestSample::init(void)
{
	questSetup();
}
/*
      "_name": "��������1 - ���� ��ġ",
      "_exp": 500,
      "_description": "���͸� 10�� ��ġ",
      "_item": "����",
      "_monster": 3,
      "_questCheck": "����",
      "_gold": 1000,
      "_monsterName": "������",
      "_questStage": "1��������"

*/
void QuestSample::questSetup(Quest* pQuest)
{
    Json::Value root = JSONDATAMANAGER->loadJsonFile("Quest.json");
    for (auto it = root["Quest"].begin(); it != root["Quest"].end(); it++)
    {
        if ((*it).isObject())
        {
            Quest* qQuest = new Quest;
            qQuest->init
            (
                (*it)["_name"].asString(),
                (*it)["_gold"].asInt(),
                (*it)["_exp"].asInt(),
                (*it)["_description"].asString(),
                (*it)["_item"].asString(),
                (*it)["_monster"].asInt(),
                (*it)["_questCheck"].asString(),
                (*it)["_monsterName"].asString(),
                (*it)["_questStage"].asString()
               // (*it)["_questStage"].asString()

            );
            _quest.push(qQuest);
        }


    }
    /*
    asString 
    �� ������ NULL�̸� ������ ���� ���� NULL��ȯ
    
    toString
    �� ������ NULL�̸� ����
    
    */


}
