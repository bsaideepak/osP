/************************************************
 * Operating Systems CSE 430
 * Project 2 - Threading program with non-preemptive scheduling.
 *
 * Copyright (c) 2015
 *      Sydney Vanda
 *      Brittney RUssell
 *
 *  Module Name:
 *      \file threads.h
 *
 *  Description:
 *      \brief Threads processing logic
 *
 ***********************************************/
#ifndef THREADS_H_
#define THREADS_H_

#include <stdlib.h>
//#include "util.h"
#include "q.h"

void start_thread(void (*function)(void));
void run();
void yield();

void start_thread(void (*function)(void))
{
	/*******************************************
	* begin pseudo code:
	* allocate a stack (via malloc) of a certain size (choose 8192)
	* allocate a TCB (via malloc)
	* call init_TCB with appropriate arguments
	* call addQ to add this TCB into the “RunQ” which is a global header pointer
	* end pseudo code
	*******************************************/
	struct TCB_t *TCB;
	void *stack;
	
	TCB = (struct TCB_t *)malloc(sizeof(struct TCB_t));
	if(!TCB)
		printf("Out of Memory! \n");

	stack = malloc(8192); //stack is an array of 8192 ints

	init_TCB(TCB, function, stack, sizeof(stack));
	RunQ->NewItem(RunQ, TCB);
}

void run() 
{  
	ucontext_t parent;     // get a place to store the main context, for faking
	getcontext(&parent);   // magic sauce
	swapcontext(&parent, &(RunQ->head->context));  // start the first thread
}

void yield() // similar to run
{
	ucontext_t *thisContext, *runQContext;

	thisContext = &(RunQ->head->context);
	RunQ->RotateHead(RunQ); //rotate the run Q
	runQContext = &(RunQ->head->context);
	swapcontext(thisContext, runQContext); //swap the context, from previous thread to the thread pointed to by RunQ
}

#endif /* THREADS_H_ */
