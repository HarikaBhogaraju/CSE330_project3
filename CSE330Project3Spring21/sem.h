//Harika Bhogaraju
//1216938606

#include <stdio.h>
#include <stdlib.h>
#include "threads.h"
/*---
typedef struct sem {
  int value;
  struct q* s_q; //queue of the sem
} sem;

void initSem(sem* s, int val){
  //sem* s = (struct sem*)malloc(sizeof(sem));
  s->value = val;
  s->s_q = (struct q*)malloc(sizeof(q));
  InitQueue(s->s_q);

}

void P(sem* s){
  while(1){
    if(s->value > 0){ //part b
      s->value--;
      return;
    }
    else{ //part a
      //remove from readyQ and move to semQ
        struct TCB_T* tcbItem;
        tcbItem = DeleteQueue(RunQ);
        //if(tcbItem != NULL){ //queue is not empty
          AddQueue(s->s_q,tcbItem);
          if(RunQ->element == NULL){
            exit(0);
          }
          swapcontext(&(s->s_q->element->prev->context), &(RunQ->element->context));
        //}
    }
  }
}

void V(sem* s){
  s->value++;

  if(s->s_q->element != NULL){
    struct TCB_T* tcbItem;
    tcbItem = DeleteQueue(s->s_q);
      //if (tcbItem != NULL){
        AddQueue(RunQ, tcbItem);
      //}
  }



}
-----*/

//struct type for semaphore data structure
typedef struct semaphore
{
    int value;
    struct q *qOfTCBs;
} semaphore;

//to initialize semaphores with given value
void initSem(semaphore *sem, int value)
{
    sem->qOfTCBs = (struct q*) malloc(sizeof(struct q));
    initQueue(sem->qOfTCBs);
    sem->value = value;
}

//P semaphore
void P(semaphore *sem)
{
    struct TCB_t *tcb;
	//checks for all Ids
    while(1)
    {
    	//if there is space in the critical section
        if(sem->value > 0)
        {
        	//decrements accordingly
            sem->value--;
            return;
        }
        else
        {
            //delete tcb from readyQ
            tcb = delQueue(ReadyQ);
            //add to semaphore queue
            addQueue(sem->qOfTCBs, tcb);

            //if head NULL exit
            if(ReadyQ->head == NULL)
            {
                exit(0);
            }
            //swap current node with previous nodes
            swapcontext(&(sem->qOfTCBs->head->prev->context), &(ReadyQ->head->context));
        }
    }
}

//V semaphore
void V(semaphore *sem)
{
    struct TCB_t *tcb;
    //incrementing the value
    sem->value++;

	//checking if any threads are waiting in semaphore queue
    if(sem->qOfTCBs->head != NULL)
    {
    	//if yes delete from semaphore queue and add to readyQ
        tcb = delQueue(sem->qOfTCBs);
        addQueue(ReadyQ, tcb);
    }
}
