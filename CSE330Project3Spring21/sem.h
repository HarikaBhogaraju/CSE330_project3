//Harika Bhogaraju
//1216938606
#include <stdio.h>
#include <stdlib.h>
#include "threads.h"

typedef struct sem {
  int value;
  struct q* s_q;
} sem;

sem* initSem(int val){
  sem* s = (struct sem*)malloc(sizeof(sem));
  s->value = val;
  s->s_q = (struct q*)malloc(sizeof(q));
  InitQueue(s->s_q);
  return s;
}

void P(sem* s){
  if(s->value > 0){ //part b
    s->value--;
  }
  else{ //part a
    //remove from readyQ and move to semQ
    s->value--;
    struct TCB_T* tcbItem;
    tcbItem = DeleteQueue(s->s_q);
    if(tcbItem != NULL){
      AddQueue(s->s_q,tcbItem);
      swapcontext(&(tcb->context), &(RunQ->head->context));
    }
    //then call yield
    yield();
  }
}

void V(sem* s){
  s->value++; //part a
  struct TCB_T* tcbItem;
  tcbItem = DeleteQueue(s->s_q);
    if (tcb != NULL){
      AddQueue(RunQ, tcbItem);
    }

    yield();

}
