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
while(1){
  if(s->value > 0){ //part b
    s->value--;
    break;
  }
  else{ //part a
    //remove from readyQ and move to semQ

      struct TCB_T* tcbItem;
      tcbItem = DeleteQueue(s->s_q);
      if(tcbItem != NULL){ //queue is not empty
        AddQueue(s->s_q,tcbItem);
        swapcontext(&(s->s_q->element->prev->context), &(RunQ->element->context));
      }
  }
}
}

void V(sem* s){

  if(s->value <= 0){
    struct TCB_T* tcbItem;
    tcbItem = DeleteQueue(s->s_q);
      if (tcbItem != NULL){
        AddQueue(RunQ, tcbItem);
      }
  }

  s->value++;

  yield();
  sleep(1);

}
