/************************************************
 * Operating Systems CSE 430
 * Project 3 - Implementing Semaphores
 *
 * Copyright (c) 2015
 *      Sydney Vanda
 *      Brittney RUssell
 *
 *  Module Name:
 *      \file proj-3.c
 *
 *  Description:
 *      \brief program to test implementation for
 *      semaphores
 *
 ***********************************************/

#include "sem.h"

/********************
 * Gobal Variables
 ********************/
Queue* RunQ;
int globalInt = 0;

Semaphore* mutex;

Semaphore* empty;
Semaphore* full;
Semaphore* bufferMutex;
Queue* buffer;

int in = 0;
int out = 0;

/********************
 * Function Prototypes
 ********************/
void function_f1();
void function_f2();
void producer();
void consumer();

/*************************
 * Function Pointers
************************/
void (*f1)();
void (*f2)();
void (*p1)();
void (*c1)();
void (*p2)();
void (*c2)();

int main()
{	
	RunQ = new_Queue();

	mutex = (Semaphore*)malloc(sizeof(Semaphore));
	mutex->queue = new_Queue();
	InitSem(mutex, 1);

	empty = (Semaphore*)malloc(sizeof(Semaphore));
	empty->queue = new_Queue();
	InitSem(empty,1);

	full = (Semaphore*)malloc(sizeof(Semaphore));
	full->queue = new_Queue();
	InitSem(full, 0);

	bufferMutex = (Semaphore*)malloc(sizeof(Semaphore));
	bufferMutex->queue = new_Queue();
	InitSem(bufferMutex, 1);

	buffer = new_Queue();

	f1 = function_f1;
	f2 = function_f2;
	p1 = producer;
	c1 = consumer;
	p2 = producer;
	c2 = consumer;

	/*************************
	 * Initialize Threads
	 ************************/
	/* Uncomment either f1 and f2 for method 1, or produce and consumer for method 2 */
	// F1 and F2 are for method 1 (mutex semaphore)
//	start_thread(f1);
//	start_thread(f2);

	// producer and consumer are for method 2 
	start_thread(p1);
	start_thread(p2);
	start_thread(c1);
	start_thread(c2);

	run(); //starts the first thread
	return 0;
}

//Function 1 & 2 are for Method 1

void function_f1()
{
	int f1_local = 0;

	while(1) {
		if (globalInt > 0)
			printf("Trying F1 ... BLOCKING, F2 in CS\n");

		P(mutex);
		
		printf("In F1 CS\n");
		yield(); //context switch to F2

		globalInt++;
		f1_local++;
		printf("In F1 : global variable = %d\n", globalInt);
		printf("In F1 : local = %d\n", f1_local);
		sleep(1);

		V(mutex);
		
		printf("F1 out of CS\n");
		sleep(1);
	}
}

void function_f2()
{
	int f2_local = 0;

	while(1) {
		printf("Trying F2 ... BLOCKING, F1 in CS\n");

		P(mutex);

		printf("In F2 CS\n");
		yield(); //context switch to F1

		globalInt++;
		f2_local++;
		printf("In F2 : global variable = %d\n", globalInt);
		printf("In F2 : local = %d\n", f2_local);
		sleep(1);

		V(mutex);

		printf("F2 out of CS\n");
		sleep(1);
	}
}

void producer()
{
	int produce_local = 0;
	while(1) {
		P(bufferMutex);
		P(empty);
		yield(); //context switch to consumer
		(bufferMutex->queue)->NewItem(bufferMutex->queue, RunQ->head);
		globalInt++;
		produce_local++;
		printf("In producer : global variable = %d\n", globalInt);
		printf("In producer : local = %d\n", produce_local);
		sleep(1);
		V(full);
		V(bufferMutex);
		
	}	
}

void consumer()
{
	int consume_local = 0;
	while(1) {
		P(bufferMutex);
		P(full);
		yield(); //context switch to producer
		(bufferMutex->queue)->DeleteItem(bufferMutex->queue);
		globalInt++;
		consume_local++;
		printf("In consumer : global variable = %d\n", globalInt);
		printf("In consumer : local = %d\n", consume_local);
		sleep(1);
		V(empty);
		V(bufferMutex);
	}

}
