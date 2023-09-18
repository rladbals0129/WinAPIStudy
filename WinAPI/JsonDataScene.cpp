#include "stdafx.h"
#include "JsonDataScene.h"

HRESULT JsonDataScene::init(void)
{
	_questSample = new QuestSample;
	_questSample->init();


	return S_OK;
}

void JsonDataScene::release(void)
{
}

void JsonDataScene::update(void)
{
	//Do Nothing
}

void JsonDataScene::render()
{
	questPopUp();
}

void JsonDataScene::questPopUp()
{
	char str[256];
	
	queue<Quest*>* temp = _questSample->getQuest();
	Quest* node = temp->front();
	

	sprintf_s(str, "%s", node->getName().c_str());
	TextOut(getMemDC(), 200, 150, str, strlen(str));

	sprintf_s(str, "����: %s", node->getDescription().c_str());
	TextOut(getMemDC(), 200, 200, str, strlen(str));

	sprintf_s(str, "���� �̸�: %s", node->getMonsterName().c_str());
	TextOut(getMemDC(), 200, 250, str, strlen(str));

	sprintf_s(str, "óġ�ؾ��� ����: %d ����", node->getMonster());
	TextOut(getMemDC(), 200, 300, str, strlen(str));

	sprintf_s(str, "����Ʈ üũ: %s", node->getQuestCheck().c_str());
	TextOut(getMemDC(), 200, 350, str, strlen(str));

	sprintf_s(str, "���� ����ġ: %d", node->getExp());
	TextOut(getMemDC(), 200, 400, str, strlen(str));

	sprintf_s(str, "����Ʈ ���� ������: %s", node->getItem().c_str());
	TextOut(getMemDC(), 200, 450, str, strlen(str));

	sprintf_s(str, "����Ʈ ���� ���: %d", node->getGold());
	TextOut(getMemDC(), 200, 500, str, strlen(str));

	//sprintf(str, "Ÿ��: %s", node->getType().c_str());
	//TextOut(getMemDC(), 200, 150, str, strlen(str));

}

void JsonDataScene::currentQuest()
{

}
