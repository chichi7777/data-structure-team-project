#define SIZE 100

typedef struct average {
	float waitTime;
	float respTime;
	float turnardTime;
} aveType;	

typedef struct process {
    int ID;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
    int responseTime;
    int flag;
} pType;

typedef struct Queue {
    pType * p[SIZE];
    int front;
    int count;
    int rear;
} quType;

quType * newQueue();
int enqueue (quType * queue, pType * data_pointer);	// return 0 if queue is full, else return 1
pType * dequeue (quType * queue);
pType * front (quType * queue);
void readFile (char * filename, quType * queue);
int setReadyQ (quType * readyQ, quType * jobQ, int time);	// return 1 if data_pointer move to readyQ from jobQ, return 0 if no action	
void setReadyQ2 (quType * readyQ, quType * jobQ, int currentTime, int elapsedTime);	//for Round Robin
int showPrsRun (int time, pType * data_pointer ,float * utilization);
void showPrsRun2 (int time, int elapsedTime, pType * data_pointer, float *utilization);	//for Round Robin
void sortQ_with_remainingTime (quType * queue);
void sortQ_with_arrivalTime (quType * queue);
aveType printAverageTime (quType * queue); 
void printResult (quType * queue);
void schedule (quType * doneQ, pType * data_pointer, int currentTime);
pType * FIFO (quType * readyQ, quType * doneQ, int time);
int RR (quType * jobQ, quType * readyQ, quType * doneQ, int currentTime, int timeQuantum, float * utilization);
int SJF (quType * readyQ, quType * doneQ, int time);
pType * SRTF (quType * readyQ, quType * doneQ, int time);
int running_with_FIFO (char * filename, quType * doneQ);
int running_with_RR (char * filename, quType * doneQ);
int running_with_SJF (char * filename, quType * doneQ);
int running_with_SRTF (char * filename, quType * doneQ);
