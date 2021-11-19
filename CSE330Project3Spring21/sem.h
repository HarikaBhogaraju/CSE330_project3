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
    if(s->value < 0){
      struct TCB_T* tcbItem;
      tcbItem = DeleteQueue(s->s_q);
      if(tcbItem != NULL){ //queue is not empty
        AddQueue(s->s_q,tcbItem);
        swapcontext(&(tcbItem->context), &(RunQ->element->context));

      }
      s->value--;
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
