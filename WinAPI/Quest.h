#pragma once
enum QUEST_TYPE
{
	QUEST_STAGE_1
};

struct Quests
{
    // 1. 구조체..?

};

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

class Quest
{
protected:
    int _exp;
    int _gold;
    int _monster;

    string _name;
    string _description;
    string _item;
    string _questCheck;
    string _monsterName;
    string _questStage;
    QUEST_TYPE _questType;
public:
    void init(string name, int gold, int exp, string description, string item, int monster, string questCheck,
        string monsterName, string questStage);

    // 2.참조형태
    int getGold() { return this->_gold; }
    int getExp() { return this->_exp; }
    int getMonster() { return this->_monster; }

    string getName() { return this->_name; }
    string getDescription() { return this->_description; }
    string getItem() { return this->_item; }
    string getQuestCheck() { return this->_questCheck; }
    string getMonsterName() { return this->_monsterName; }
    string getQuestStage() { return this->_questStage; }


    QUEST_TYPE getType() { return this->_questType; }
    Quest() {}
    ~Quest() {}

};

