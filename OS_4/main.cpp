#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "list.h"

int main() {
	setlocale(LC_ALL, "Rus");
	int quantumTime = 0;
	printf("Введите квант времени: ");
	scanf("%d", &quantumTime);
	int numProc = 0;
	printf("Введите количество процессов: ");
	scanf("%d", &numProc);
	process* archiveProc = NULL;
	int procTime = 0;
	int procArrive = 0;
	for (int i = 0; i < numProc; i++) {
		printf("\nВведите время процесса %d: ", i + 1);
		scanf("%d", &procTime);
		archiveProc = addLast(archiveProc, procTime, -1);
		getProc(archiveProc, i)->id = i + 1;
		printf("Введите время поступления процесса %d: ", i + 1);
		scanf("%d", &procArrive);
		getProc(archiveProc, i)->arriveTime = procArrive;
	}
	process* queueProc = copyQueue(archiveProc);
	int timer = 0;
	float sumWaitTime = 0;
	float avgTime = 0;
	int remainingProc = numProc;
	while (remainingProc > 0) {
		process* curProc = copyQueue(queueProc);
		if (curProc == NULL) {
			break;
		}
		queueProc = specDelete(queueProc, curProc->burstTime);
		curProc->startTime = timer;
		for (int i = 0; i < timer - curProc->cntStatus; i++) {
			curProc->conditionProc = addLastCond(curProc->conditionProc, 'Г');
		}
		curProc->cntStatus += timer - curProc->cntStatus;
		copyCond(curProc, archiveProc);
		if (quantumTime >= curProc->burstTime) {
			timer += curProc->burstTime;
			curProc->endTime = timer;
			curProc->waitTime = curProc->startTime - curProc->kollllllll;
			sumWaitTime += curProc->waitTime;
			avgTime += curProc->endTime;
			for (int i = 0; i < curProc->burstTime; i++) {
				curProc->conditionProc = addLastCond(curProc->conditionProc, 'И');
			}
			curProc->cntStatus += curProc->burstTime;
			copyCond(curProc, archiveProc);
			remainingProc--;
		}
		else {
			timer += quantumTime;
			curProc->kollllllll += quantumTime;
			curProc->burstTime -= quantumTime;
			for (int i = 0; i < quantumTime; i++) {
				curProc->conditionProc = addLastCond(curProc->conditionProc, 'И');
			}
			curProc->cntStatus += quantumTime;
			copyCond(curProc, archiveProc);
			queueProc = addLast(queueProc, curProc->burstTime, curProc->id);
			getLast(queueProc)->cntStatus += curProc->cntStatus;
			getLast(queueProc)->kollllllll += curProc->kollllllll;
			copyCond(curProc, queueProc);
		}
	}
	float sumTime = timer;
	avgTime /= numProc;
	float avgWaitTime = sumWaitTime / numProc;
	printf("-------\nFCFS\n-------\n");
	printf("Время, необходимое для обработки всех процессов: %g\n", sumTime);
	printf("Среднее полное время выполнения: %6.1f\n", avgTime);
	printf("Среднее время ожидания: %6.1f\n", avgWaitTime);
	printf("T");
	for (int i = 0; i < sumTime; i++) {
		printf("%5d", i + 1);
	}
	printf("\n");
	for (int i = 0; i < numProc; i++) {
		process* curProc = getProc(archiveProc, i);
		if (curProc != NULL) {
			printf("%d", i + 1);

			for (int j = 0; j < sumTime; j++) {
				if (curProc->conditionProc != NULL) {
					printf("%5c", curProc->conditionProc->condition);
					curProc->conditionProc = curProc->conditionProc->next;
				}
				else {
					printf("%5c", ' ');
				}
			}
			printf("\n");
		}
	}
	process* tempQueue = copyQueue(archiveProc);
	sortIncr(missArrive(tempQueue), &queueProc, timer);
	timer = 0;
	sumWaitTime = 0;
	avgTime = 0;
	remainingProc = numProc;
	while (remainingProc > 0) {
		tempQueue = copyQueue(queueProc);
		queueProc = NULL;
		sortIncr(tempQueue, &queueProc, timer);
		process* curProc = copyQueue(queueProc);
		if (curProc == NULL) {
			break;
		}
		curProc->tagPrev = 1;
		queueProc = specDelete(queueProc, curProc->burstTime);
		curProc->startTime = timer;
		for (int i = 0; i < timer - curProc->cntStatus; i++) {
			curProc->conditionProc = addLastCond(curProc->conditionProc, 'Г');
		}
		curProc->cntStatus += timer - curProc->cntStatus;
		copyCond(curProc, archiveProc);
		if (quantumTime >= curProc->burstTime) {
			timer += curProc->burstTime;
			curProc->endTime = timer;
			curProc->waitTime = curProc->startTime - curProc->kollllllll;
			sumWaitTime += curProc->waitTime;
			avgTime += curProc->endTime;
			for (int i = 0; i < curProc->burstTime; i++) {
				curProc->conditionProc = addLastCond(curProc->conditionProc, 'И');
			}
			curProc->cntStatus += curProc->burstTime;
			copyCond(curProc, archiveProc);
			remainingProc--;
		}
		else {
			timer += quantumTime;
			curProc->kollllllll += quantumTime;
			curProc->burstTime -= quantumTime;
			for (int i = 0; i < quantumTime; i++) {
				curProc->conditionProc = addLastCond(curProc->conditionProc, 'И');
			}
			curProc->cntStatus += quantumTime;
			copyCond(curProc, archiveProc);
			queueProc = addLast(queueProc, curProc->burstTime, curProc->id);
			getLast(queueProc)->cntStatus += curProc->cntStatus;
			getLast(queueProc)->tagPrev = curProc->tagPrev;
			getLast(queueProc)->kollllllll += curProc->kollllllll;
			copyCond(curProc, queueProc);
		}
	}
	sumTime = timer;
	avgTime /= numProc;
	avgWaitTime = sumWaitTime / numProc;
	printf("\n\n\n\n");
	printf("-------\nSJF\n-------\n");
	printf("Время, необходимое для обработки всех процессов: %g\n", sumTime);
	printf("Среднее полное время выполнения: %6.1f\n", avgTime);
	printf("Среднее время ожидания: %6.1f\n", avgWaitTime);
	printf("T");
	for (int i = 0; i < sumTime; i++) {
		printf("%5d", i + 1);
	}
	printf("\n");
	for (int i = 0; i < numProc; i++) {
		process* curProc = getProc(archiveProc, i);
		if (curProc != NULL) {
			printf("%d", i + 1);
			for (int j = 0; j < sumTime; j++) {
				if (curProc->conditionProc != NULL) {
					printf("%5c", curProc->conditionProc->condition);
					curProc->conditionProc = curProc->conditionProc->next;
				}
				else {
					printf("%5c", ' ');
				}
			}
			printf("\n");
		}
	}
	timer = 0;
	sumWaitTime = 0;
	avgTime = 0;
	int* exedockQueue = (int*)calloc(numProc, sizeof(int));
	process* varArchiveProc = copyQueue(archiveProc);
	remainingProc = numProc;
	tempQueue = NULL;
	quantumTime = 1;
	while (remainingProc > 0) {
		dockQueue(&varArchiveProc, &queueProc, timer, exedockQueue); //создаёт новую очередь... 
		tempQueue = copyQueue(queueProc);
		queueProc = NULL;
		sortIncr(tempQueue, &queueProc, timer);
		process* curProc = copyQueue(queueProc);
		if (curProc == NULL) {
			break;
		}
		queueProc = specDelete(queueProc, curProc->burstTime);
		curProc->startTime = timer;
		for (int i = 0; i < timer - curProc->cntStatus; i++) {
			curProc->conditionProc = addLastCond(curProc->conditionProc, 'Г');
		}
		curProc->cntStatus += timer - curProc->cntStatus;
		copyCond(curProc, archiveProc);
		if (quantumTime >= curProc->burstTime) {
			timer += curProc->burstTime;
			curProc->endTime = timer - exedockQueue[curProc->id - 1];
			curProc->waitTime = curProc->startTime - curProc->kollllllll;
			sumWaitTime += curProc->waitTime;
			avgTime += curProc->endTime;
			for (int i = 0; i < curProc->burstTime; i++) {
				curProc->conditionProc = addLastCond(curProc->conditionProc, 'И');
			}
			curProc->cntStatus += curProc->burstTime;
			copyCond(curProc, archiveProc);
			remainingProc--;
		}
		else {
			timer += quantumTime;
			curProc->kollllllll += quantumTime;
			curProc->burstTime -= quantumTime;
			curProc->conditionProc = addLastCond(curProc->conditionProc, 'И');
			curProc->cntStatus += quantumTime;
			copyCond(curProc, archiveProc);
			queueProc = addLast(queueProc, curProc->burstTime, curProc->id);
			getLast(queueProc)->cntStatus += curProc->cntStatus;
			getLast(queueProc)->tagPrev = curProc->tagPrev;
			getLast(queueProc)->kollllllll += curProc->kollllllll;
			copyCond(curProc, queueProc);
		}
	}
	sumTime = timer;
	avgTime /= numProc;
	avgWaitTime = sumWaitTime / numProc;
	printf("\n\n\n\n");
	printf("-------\nSJF 2.0\n-------\n");
	printf("Время, необходимое для обработки всех процессов: %g\n", sumTime);
	printf("Среднее полное время выполнения: %6.1f\n", avgTime);
	printf("Среднее время ожидания: %6.1f\n", avgWaitTime);
	printf("T");
	for (int i = 0; i < sumTime; i++) {
		printf("%5d", i);
	}
	printf("\n");
	for (int i = 0; i < numProc; i++) {
		process* curProc = getProc(archiveProc, i);
		if (curProc != NULL) {
			printf("%d", i + 1);
			for (int j = 0; j < sumTime; j++) {
				if (curProc->conditionProc != NULL) {
					printf("%5c", curProc->conditionProc->condition);
					curProc->conditionProc = curProc->conditionProc->next;
				}
				else {
					printf("%5c", ' ');
				}
			}
			printf("\n");
		}
	}
}






