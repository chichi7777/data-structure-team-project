#include <stdio.h>
#include <stdlib.h>
#include "project.h"

int main()
{
    int choice = 1;
    char filename[20];
    quType * FIFO_doneQ, * RR_doneQ, * SJF_doneQ, * SRTF_doneQ;
    aveType FIFO_ave, RR_ave, SJF_ave, SRTF_ave;

    FIFO_doneQ = newQueue();
    RR_doneQ = newQueue();
    SJF_doneQ = newQueue();
    SRTF_doneQ = newQueue();

	system("clear");
	printf("*********************************************\n");
	printf("*             Please enter a file           *\n");
	printf("*********************************************\n");
	printf("File name: ");
	scanf("%s",filename);
    
    
 
 	while(0 < choice && choice < 6) {  
		printf("*********************************************\n");
		printf("* Choose a scheduling method:               *\n");
		printf("* 1.First Come, First Serve (FIFO)          *\n");
		printf("* 2.Round-robin (RR)                        *\n");
		printf("* 3.Non-preemptive Shortest Job First (SJF) *\n");
		printf("* 4.Preemptive Shortest Job First (SRTF)    *\n");
		printf("* 5.Comparison (average time of 4 modes)    *\n");
		printf("* 6.Quit                                    *\n");
		printf("*********************************************\n");
		printf("Choice = ");
		scanf("%d",&choice);
			
		switch(choice) {
		    case 1 :	
		    	system("clear");
		    	printf("*********************************************\n");
				printf("*      First Come, First Serve (FIFO)       *\n");
				printf("*********************************************\n");
    			running_with_FIFO(filename, FIFO_doneQ);
    			printResult(FIFO_doneQ);
    			FIFO_ave = printAverageTime(FIFO_doneQ);	
    			break;	
			case 2 :	
				system("clear");
				printf("*********************************************\n");
				printf("*              Round-robin (RR)             *\n");
				printf("*********************************************\n");
				running_with_RR(filename, RR_doneQ);
				printResult(RR_doneQ);
				RR_ave = printAverageTime(RR_doneQ);		
				break;		
			case 3 :	
				system("clear");
				printf("*********************************************\n");
				printf("*  Non-preemptive Shortest Job First (SJF)  *\n");
				printf("*********************************************\n");
				running_with_SJF(filename, SJF_doneQ);
				printResult(SJF_doneQ);
				SJF_ave = printAverageTime(SJF_doneQ);
				break;	
			case 4 :	
				system("clear");
				printf("*********************************************\n");
				printf("*    Preemptive Shortest Job First (SRTF)   *\n");
				printf("*********************************************\n");
				running_with_SRTF(filename, SRTF_doneQ);
				printResult(SRTF_doneQ);
				SRTF_ave = printAverageTime(SRTF_doneQ);
				break;
			case 5 :
				system("clear");
				printf("\n Comparison\n");
				printf("\t\t\t     FIFO       RR       SFF       SRTF\n");
				printf(" Average waiting time:    %9f %9f %9f %9f\n", FIFO_ave.waitTime, RR_ave.waitTime, SJF_ave.waitTime, SRTF_ave.waitTime);
    			printf(" Average response time:   %9f %9f %9f %9f\n", FIFO_ave.respTime, RR_ave.respTime, SJF_ave.respTime, SRTF_ave.respTime);
    			printf(" Average turnaround time: %9f %9f %9f %9f\n\n", FIFO_ave.turnardTime, RR_ave.turnardTime, SJF_ave.turnardTime, SRTF_ave.turnardTime);
		}	
	}
}
