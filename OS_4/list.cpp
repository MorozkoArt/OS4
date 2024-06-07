#define _CRT_SECURE_NO_WARNINGS
#define N 10
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

process* newZveno() {
	process* V;
	V = (process*)malloc(sizeof(process));
	V->burstTime = 0;
	V->id = V->startTime = V->endTime = V->waitTime = V->cntStatus = V->tagPrev = V->arriveTime = V->kollllllll = 0;
	V->conditionProc = NULL;
	V->next = NULL;
	return V;
}

process* addLast(process* head, int data, int idHist) {
	process* v = newZveno();
	if (head == NULL) {
		v->burstTime = data;
		if (idHist != -1)
			v->id = idHist;
		else
			v->id = 1;
		v->next = NULL;
		head = v;
		return head;
	}
	process* p = head;
	while (p->next != NULL)
		p = p->next;
	p->next = v;
	v->burstTime = data;
	v->startTime = 0;
	v->endTime = 0;
	v->waitTime = 0;
	v->next = NULL;

	if (idHist != -1)
		v->id = idHist;

	return head;
}

process* specDelete(process* head, int value) {
	process* pZveno = head;
	if (pZveno->burstTime == value) {
		process* tempZveno = pZveno;
		head = pZveno->next;

		free(tempZveno);
		return head;
	}

	while (pZveno->next != NULL && pZveno->next->burstTime != value)
		pZveno = pZveno->next;

	if (pZveno->next != NULL) {
		process* tempZveno = pZveno->next;
		pZveno->next = tempZveno->next;

		free(tempZveno);
	}
	else {
		printf("Элемент со значением %d не найден\n", value);
		return head;
	}

	return head;
}

process* getProc(process* queueProc, int index) {
	process* pProc = queueProc;
	int cnt = 0;
	while (pProc != NULL && cnt != index) {
		pProc = pProc->next;
		cnt++;
	}
	if ((cnt == index) && (pProc != NULL))
		return pProc;
	else
		return NULL;
}

process* copyQueue(process* queueProc) {
	process* pProc = queueProc;
	process* newQueue = newZveno();
	process* newProc = NULL;
	process* lastNewProc = newQueue;
	newQueue->id = pProc->id;
	newQueue->burstTime = pProc->burstTime;
	newQueue->startTime = pProc->startTime;
	newQueue->endTime = pProc->endTime;
	newQueue->waitTime = pProc->waitTime;
	newQueue->cntStatus = pProc->cntStatus;
	newQueue->tagPrev = pProc->tagPrev;
	newQueue->arriveTime = pProc->arriveTime;
	newQueue->kollllllll = pProc->kollllllll;
	copyCond(pProc, newQueue);
	newQueue->next = NULL;

	pProc = pProc->next;
	while (pProc != NULL) {
		newProc = newZveno();
		newProc->id = pProc->id;
		newProc->burstTime = pProc->burstTime;
		newProc->startTime = pProc->startTime;
		newProc->endTime = pProc->endTime;
		newProc->waitTime = pProc->waitTime;
		newProc->cntStatus = pProc->cntStatus;
		newProc->tagPrev = pProc->tagPrev;
		newProc->arriveTime = pProc->arriveTime;
		newProc->kollllllll = pProc->kollllllll;
		copyCond(pProc, newProc);
		newProc->next = NULL;
		lastNewProc->next = newProc;
		lastNewProc = lastNewProc->next;
		pProc = pProc->next;
	}
	return newQueue;
}

statusProc* newZvenoCond() {
	statusProc* V;
	V = (statusProc*)malloc(sizeof(statusProc));
	V->next = NULL;
	return V;
}

statusProc* addLastCond(statusProc* head, char cond) {
	statusProc* v = newZvenoCond();
	if (head == NULL) {
		v->next = NULL;
		v->condition = cond;
		head = v;
		return head;
	}
	statusProc* p = head;
	while (p->next != NULL)
		p = p->next;
	p->next = v;
	v->condition = cond;
	v->next = NULL;
	return head;
}

void copyCond(process* queueProc, process* archiveProc) {
	process* pProc = queueProc;
	while (pProc != NULL) {
		process* pArchive = archiveProc;
		while ((pArchive != NULL) && (pProc->id != pArchive->id)) {
			pArchive = pArchive->next;
		}
		if ((pProc != NULL) && (pArchive != NULL)) {
			statusProc* pCondProc = pProc->conditionProc;
			statusProc** ppCondArchive = &(pArchive->conditionProc);
			while (pCondProc != NULL) {
				if (pCondProc->condition != NULL) {
					statusProc* newCond = new statusProc;
					*newCond = *pCondProc;
					*ppCondArchive = newCond;
					ppCondArchive = &(newCond->next);
				}
				pCondProc = pCondProc->next;
			}
		}
		pProc = pProc->next;
	}
}

process* getLast(process* head) {
	process* last = head;
	while (last != NULL && last->next != NULL) {
		last = last->next;
	}
	return last;
}

process* getMinList(process* archiveProc) {
	process* pProc = archiveProc;
	process* minList = copyQueue(pProc);
	int minBurst = pProc->burstTime;
	while (pProc != NULL) {
		if ((pProc->burstTime < minBurst) && (!pProc->tagPrev)) {
			minBurst = pProc->burstTime;
			minList = copyQueue(pProc);
		}
		if (pProc->tagPrev)
			pProc->tagPrev = 0;
		pProc = pProc->next;
	}
	return minList;
}

void sortIncr(process* archiveProc, process** queueProc, int timer) {

	process* pProc = archiveProc;
	while (archiveProc != NULL) {
		process* pProc = archiveProc;
		int deleteValue = 0;
		while (pProc != NULL) {
			if (pProc->burstTime == getMinList(archiveProc)->burstTime) {
				*queueProc = addLast(*queueProc, pProc->burstTime, pProc->id);
				getLast(*queueProc)->cntStatus += pProc->cntStatus;
				getLast(*queueProc)->tagPrev = pProc->tagPrev;
				getLast(*queueProc)->arriveTime = pProc->arriveTime;
				getLast(*queueProc)->kollllllll += pProc->kollllllll;
				copyCond(pProc, *queueProc);

				deleteValue = pProc->burstTime;
				pProc = pProc->next;
				archiveProc = specDelete(archiveProc, deleteValue);
			}
			else
				pProc = pProc->next;
		}
	}
}

process* missArrive(process* queueProc) {
	process* pProc = queueProc;
	while (pProc != NULL) {
		pProc->arriveTime = 0;
		pProc = pProc->next;
	}
	return queueProc;
}

void dockQueue(process** archiveProc, process** queueProc, int timer, int* exedock) {
	process* pProc = *archiveProc;
	int deleteValue = 0;
	while (pProc != NULL) {
		if (pProc->arriveTime <= timer) {
			*queueProc = addLast(*queueProc, pProc->burstTime, pProc->id);
			getLast(*queueProc)->tagPrev = pProc->tagPrev;
			getLast(*queueProc)->arriveTime = 0;
			for (int i = 0; i < timer; i++) {
				pProc->conditionProc = addLastCond(pProc->conditionProc, ' ');
			}
			pProc->kollllllll += timer;
			exedock[pProc->id - 1] += timer;
			pProc->cntStatus += timer;
			getLast(*queueProc)->cntStatus += pProc->cntStatus;
			getLast(*queueProc)->kollllllll += pProc->kollllllll;
			copyCond(pProc, *queueProc);
			deleteValue = pProc->burstTime;
			pProc = pProc->next;
			*archiveProc = specDelete(*archiveProc, deleteValue);
		}
		else
			pProc = pProc->next;
	}
}




