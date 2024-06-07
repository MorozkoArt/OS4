struct statusProc {
	char condition;
	statusProc* next;
};

struct process {
	int id;
	int burstTime;
	int startTime;
	int endTime;
	int waitTime;
	int cntStatus;
	int tagPrev;
	int arriveTime;
	int kollllllll;
	statusProc* conditionProc;
	process* next;
};

process* newZveno();
statusProc* newZvenoCond();
process* addLast(process* head, int data, int idHist);
process* specDelete(process* head, int value);
process* getProc(process* queueProc, int index);
process* copyQueue(process* queueProc);
statusProc* addLastCond(statusProc* head, char cond);
void copyCond(process* queueProc, process* archiveProc);
process* getLast(process* head);
process* getMinList(process* archiveProc);
void sortIncr(process* archiveProc, process** queueProc, int timer);
process* missArrive(process* queueProc);
void dockQueue(process** archiveProc, process** queueProc, int timer, int* exePenalty);
