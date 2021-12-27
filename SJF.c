#include <stdio.h>
#include <stdlib.h>
#include "project.h"

int running_with_SJF(char * filename, quType * doneQ)
{
	int time=0,check=0;
	float utilization=0.0;
    quType * jobQ, * readyQ;
    pType *p;
    jobQ = newQueue();
    readyQ = newQueue();
    readFile (filename,jobQ);
    while (jobQ->count != 0 || readyQ->count != 0) {		//end loop if all the processes is finished
        setReadyQ (readyQ, jobQ, time);
        if (check>0){							
            sortQ_with_remainingTime(readyQ);	//move on to the next process
            check=0;
        }
        p=front(readyQ);
        if(front(readyQ)!=NULL){
            check=SJF(readyQ,doneQ,time);     //check if the process running  is finished
        }
        showPrsRun(time,p,&utilization);
        time++;
    }
	printf("\n Total run time: %d\n",time);
	printf(" Utilization: %f %%\n",(float)((utilization*100)/time));
	sortQ_with_arrivalTime (doneQ);
    return 0;
}

int SJF(quType *q,quType *doneQ,int time)		
{
	pType *p=q->front->p;
	q->front->p->remainingTime--;
	if(q->front->p->remainingTime<=0){		//count waiting time,turnaround time...and store into doneQ
        p=dequeue(q);
        p->waitingTime=time-p->burstTime-p->arrivalTime+1;
        p->turnaroundTime=time-p->arrivalTime+1;
        p->responseTime=p->waitingTime;
        enqueue(doneQ,p);
        return 1;
	}
	return 0;
}

