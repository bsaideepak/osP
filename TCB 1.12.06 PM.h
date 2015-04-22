/************************************************
 * Operating Systems CSE 430
 * Project 2 - Threading program with non-preemptive scheduling.
 *
 * Copyright (c) 2015
 *      Sydney Vanda
 *      Brittney RUssell
 *
 *  Module Name:
 *      \file TCB.h
 *
 *  Description:
 *      \brief TCB processing logic
 *
 *
 ***********************************************/
#ifndef _TCB_H_
#define _TCB_H_
#include <ucontext.h>
#include <string.h>

struct TCB_t
{
	ucontext_t context;
	struct TCB_t *next;
	struct TCB_t *previous;
};

void init_TCB(struct TCB_t *tcb, void *functionPointer, void *stackPointer, int stackSize);
/************************************************
* There is a routine in the tcb.h file called init_TCB,
* which is used to initialize a TCB for a new thread. The arguments to init_TCB are:
*
*    1. pointer to the function, to be executed
*    2. pointer to the thread stack
*    3. size of the stack
______________________________________________________________
u_context.h:
	uc_stack = user context stack used for this context, value doesn't need to be stack pointer

	getcontext() = function initalizes the varaible pointed to be ucp with the context of the calling thread,
		       returns 0 id successful and -1 otherwise

	makecontext() = calls the function and get the context that getcontext initalizes

uc_stack:
	ss = signal stack
	ss_sp = points to the base of the stack
	ss_size = size in bytes of the signal stack that ss_sp points to

***********************************************/
void init_TCB(struct TCB_t *tcb, void *functionPointer, void *stackPointer, int stackSize)
{
	memset(tcb, '\0', sizeof(struct TCB_t)); 
	getcontext(&tcb->context); // get parent context
	tcb->context.uc_stack.ss_sp = malloc(8192); //stackPointer failing - needs direct allocation
	tcb->context.uc_stack.ss_size = 8192; //(size_t)stackSize failing - need direct allocation
	makecontext(&tcb->context, functionPointer, 0); 
}

#endif /* _TCB_H_ */
