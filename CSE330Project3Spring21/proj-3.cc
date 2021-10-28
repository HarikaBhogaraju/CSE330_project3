#include "threads.h"
#include "sem.h"
int in = 0;
int out = 0;

int b = 0;
int c = 0;
int p = 0;
int n = 0;

void producer(){
  P(emptySem);
  buffer[in] = item;

  in = (in+1)%N;
  V(fullSem);
}

void consumer(){
  P(fullSem);
  item = buffer[out];
  out = (out+1)%N;
  V(emptySem);
}

int main(){
  scanf("%d,%d,%d,%d\n",&b,&p,&c,&n);

  sem* fullSem = initSem(0);
  sem* emptySem = initSem(n);
  sem* mutexSem = initSem(1);
  int buffer[b];



  int item = ;
  return 0;
}
