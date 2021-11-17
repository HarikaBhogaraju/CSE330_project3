//Harika Bhogaraju
//1216938606
#include "q.h"

struct q* RunQ;

void startThread(void (*function)(int,int),int p1,int p2){
	//	allocate a stack(via malloc) of a certain size(choose 8192)
	void* stack_pointer = (void*)malloc(8192);
	//	allocate a TCB(via malloc)
	TCB_T* tcb = (TCB_T*)malloc(sizeof(TCB_T));
	//	call init_TCB with appropriate arguments
	init_tcb(tcb, function, stack_pointer, p1, p2, 8192);
	//	call addQ to add this TCB into the "RunQ" which is a global element pointer
	AddQueue(RunQ, tcb);
}

void run(){
	ucontext_t parent;
	getcontext(&parent);
	swapcontext(&parent, &(RunQ->element->context));
}

void yield(){
	ucontext_t prev;
	getcontext(&prev);
	RotateQ(RunQ);
	swapcontext(&(RunQ->element->prev->context), &(RunQ->element->context));
}
