#include <stdio.h>
#include <stdlib.h>
#include "project.h"

quType * newQueue()							
{
    quType * q = malloc(sizeof(quType));
    q->count = 0;
    q->front = NULL;
    q->rear = NULL;
    return q;
}

void enqueue (quType * q, pType * p)	//push item into queue
{
    lkType * L;

    if (q->front == NULL) {
        q->front = malloc(sizeof(quType));
        L = q->front;
        L->p = p;
        L->Link = NULL;
        q->rear = q->front;
        q->count++;
    }
    else {
        L = q->front;
        while (L->Link != NULL) {
            L = L->Link;
        }
        L->Link = malloc(sizeof(lkType));
        L = L->Link;
        L->p = p;
        L->Link = NULL;
        q->rear = L;
        q->count++;
    }
}

pType * dequeue (quType * q)			//remove item from queue
{
    pType * p = NULL;
    lkType * L;

    if (q->count == 0) {
        return NULL;
    }
    else {
        L = q->front;
        q->front = q->front->Link;
        q->count--;
        p = L->p;
        free(L);
        if (q->front == NULL) {
            q->rear = NULL;
        }
        return p;
    }
}

pType * front (quType * q)			//return the front item of queue
{
    if (q->front == NULL) {
        return NULL;
    }
    else {
        return q->front->p;
    }
}

