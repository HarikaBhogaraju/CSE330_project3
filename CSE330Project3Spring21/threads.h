
#include "q.h"


struct q *RunQ;


void start_thread(void (*function)(int), int threadId)
{
	void *stack;
	stack = malloc(8192);
	TCB_t *item;

	item = (TCB_t *)malloc(sizeof(TCB_t));

	init_TCB(item, function, stack, 8192, threadId);

	AddQueue(RunQ, item);

}

void run()
{
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
