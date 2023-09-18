#pragma once
#include "Quest.h"
//class Quest;

// ��ڷᱸ���� �����ұ�?? -> ť.
// cpu��ĳ�ٸ��� ť����

#pragma region ť
/*
Ư¡ ���� ���� �ֽ�ߵǴ���

�� ť(queue)

- ť�� ����Ʈ�� �������� ���ð� �ٸ��� FIFO(���Լ���) �ڷᱸ��

- ������ �Ͼ�� ���� ��, ������ �Ͼ������ ��(����Ʈ) �̶���Ѵ�.

�� ����Ʈť / cpu�����ٸ� / ����(������) / BFS + DFS� ���� ���ȴ�.

�� ť���� ���� ����ϴ� �ɹ��Լ�

- front()
�� ù��° ��� ����
- back()
�� ������ ��� ����
- push()
�� ������ ����
- size()
�� ũ���ȯ
- empty()
�� �������?








*/
#pragma endregion

class QuestSample
{
private:
	queue<Quest*> _quest;
	//queue �ϸ� �����°� ->cpu��ĳ�ٸ� , ����Ʈť , �����͹��� , bfs dfs(�ʺ�켱 ���̿켱) 


public:
	void init(void);
	void questSetup(Quest* pQuest = nullptr);
	
	queue<Quest*>* getQuest() { return &this->_quest; };

	QuestSample() {}
	~QuestSample() {}
};

