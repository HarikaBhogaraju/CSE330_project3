#include "threads.h"
#include "sem.h"
int in = 0;
int out = 0;

int b = 0;
int c = 0;
int p = 0;
int n = 0;

int item = 0;
sem* fullSem;
sem* emptySem;
sem* mutexSem;

void producer(){
  P(emptySem);
  buffer[in] = item;

  in = (in+1)%n;
  V(fullSem);
}

void consumer(){
  P(fullSem);
  item = buffer[out];
  out = (out+1)%n;
  V(emptySem);
}

int main(){
  scanf("%d,%d,%d,%d\n",&b,&p,&c,&n);

  fullSem = initSem(0);
  emptySem = initSem(n);
  mutexSem = initSem(1);

  extern int buffer[b];
  return 0;
}
