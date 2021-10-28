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
  sem* s = (sem*)malloc(sizeof(sem));
  s->value = val;
  s->s_q = (q*)malloc(sizeof(q));
  InitQueue(s->s_q);
  return s;
}

void P(sem* s){
  if(s->value > 0){ //part b
    s->value--;
  }
  else{ //part a
    //remove from readyQ and move to semQ
    struct TCB_T* tcbItem;
    tcbItem = DeleteQueue(s->s_q);
    if(tcbItem != NULL){
      AddQueue(s->s_q,tcbItem);
    }
    //then call yield
    yield();
  }
}

void V(sem* s){
  s->value++; //part a

}
