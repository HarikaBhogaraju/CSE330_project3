//including q.h
#include "q.h"

//global variable RunQ of q type
struct q *RunQ;

//now accepts an extra parameter threadId
void start_thread(void (*function)(int), int threadId)
{ // begin pseudo code
    // allocate a stack (via malloc) of a certain size (choose 8192)
	void *stack;
	stack = malloc(8192);
	TCB_t *item;
	// allocate a TCB (via malloc)
	item = (TCB_t *)malloc(sizeof(TCB_t));
        // call init_TCB with appropriate arguments
	init_TCB(item, function, stack, 8192, threadId);
        // call addQ to add this TCB into the "RunQ" which is a global elementer pointer
	AddQueue(RunQ, item);
  	//end pseudo code
}

void run()
{       // real code
	ucontext_t parent;     // get a place to store the main context, for faking
	getcontext(&parent);   // magic sauce
	swapcontext(&parent, &(RunQ->element->context));  // start the first thread
}

void yield() // similar to run
{
	ucontext_t prev;
	// rotate the run Q;
	rotateQ(RunQ);
	getcontext(&prev);
        // swap the context, from previous thread to the thread pointed to by RunQ
	swapcontext(&(RunQ->element->prev->context), &(RunQ->element->context));
}
