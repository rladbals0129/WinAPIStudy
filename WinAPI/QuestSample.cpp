#include "stdafx.h"
#include "QuestSample.h"


void QuestSample::init(void)
{
	questSetup();
}
/*
      "_name": "스테이지1 - 몬스터 퇴치",
      "_exp": 500,
      "_description": "몬스터를 10명 퇴치",
      "_item": "보석",
      "_monster": 3,
      "_questCheck": "섬멸",
      "_gold": 1000,
      "_monsterName": "곰돌이",
      "_questStage": "1스테이지"

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
    ㄴ 변수가 NULL이면 별도의 예외 없이 NULL반환
    
    toString
    ㄴ 변수가 NULL이면 예외
    
    */


}
