#include "stdafx.h"
#include "Quest.h"

void Quest::init(string name, int gold, int exp, string description, string item, int monster, string questCheck, string monsterName, string questStage)
{
	//비주얼스튜디오 어시스트 (토마토아이콘 기억)
	_name = name;
	_gold = gold;
	_exp = exp;
	_description = description;
	_item = item;
	_monster = monster;
	_questCheck = questCheck;
	_monsterName = monsterName;
	_questStage = questStage;
}
