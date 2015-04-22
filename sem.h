#ifndef SEM_H_
#define SEM_H_

#include "threads.h"

typedef struct _Sem
{
	int count;
	Queue* queue;
}Sem;

void InitSem(Sem* sem, int value);
void P(Sem* sem);
void V(Sem* sem);

void InitSem(Sem* Sem, int value)
{
	Sem->count = value;
}

void P(Sem* Sem)
{
	ucontext_t *thisContext;
	struct TCB_t *DelQ_return;

	Sem->count--;
	if (Sem->count < 0) { //block operation
		thisContext = &(RunQ->head->context);
		DelQ_return = RunQ->DeleteItem(RunQ); //returns the RunQ head
		(Sem->queue)->NewItem(Sem->queue, DelQ_return); //add previous RunQ head to Sem Queue
		swapcontext(thisContext, &(RunQ->head->context));
	}
}

void V(Sem* Sem)
{
	struct TCB_t *DelQ_return;

	Sem->count++;
	if (Sem->count <= 0) {
		DelQ_return = (Sem->queue)->DeleteItem(Sem->queue); //deletes head from SemQ 
		RunQ->NewItem(RunQ, DelQ_return); //add the SemQ head back to the RunQ (unblock)
	}
	yield();  //important
	sleep(1);
}


#endif /* SEM_H_ */
