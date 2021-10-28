//Harika Bhogaraju
//1216938606
#include <ucontext.h>
#include <stdio.h>
#include <string.h>

typedef struct TCB_T {
	struct TCB_T* next;
	struct TCB_T* prev;
	ucontext_t	context;
} TCB_T;

void init_tcb(TCB_T* tcb, void* function, void* stackp, int stack_size) {
	memset(tcb, '\0', sizeof(TCB_T));
	getcontext(&tcb->context);

	// have to get parent context, else snow forms on hell
	tcb->context.uc_stack.ss_sp = stackp;

	tcb->context.uc_stack.ss_size = (size_t) stack_size;
	makecontext(&tcb->context, function, 0);// context is now cooked
}
