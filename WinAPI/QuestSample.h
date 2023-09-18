#pragma once
#include "Quest.h"
//class Quest;

// 어떤자료구조가 들어가야할까?? -> 큐.
// cpu스캐줄링은 큐쓰자

#pragma region 큐
/*
특징 장점 단점 왜써야되는지

▶ 큐(queue)

- 큐는 리스트의 일종으로 스택과 다르게 FIFO(선입선출) 자료구조

- 삽입이 일어나는 쪽을 뒤, 삭제가 일어나는쪽을 앞(프론트) 이라고한다.

※ 프린트큐 / cpu스케줄링 / 버퍼(데이터) / BFS + DFS등에 자주 사용된다.

▷ 큐에서 자주 사용하는 맴버함수

- front()
ㄴ 첫번째 요소 접근
- back()
ㄴ 마지막 요소 접근
- push()
ㄴ 데이터 삽입
- size()
ㄴ 크기반환
- empty()
ㄴ 비엇는지?








*/
#pragma endregion

class QuestSample
{
private:
	queue<Quest*> _quest;
	//queue 하면 나오는거 ->cpu스캐줄링 , 프린트큐 , 데이터버퍼 , bfs dfs(너비우선 깊이우선) 


public:
	void init(void);
	void questSetup(Quest* pQuest = nullptr);
	
	queue<Quest*>* getQuest() { return &this->_quest; };

	QuestSample() {}
	~QuestSample() {}
};

