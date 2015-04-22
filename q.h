#include <stdio.h>
#include <stdlib.h>
#include "TCB.h"

typedef struct _Queue Queue;

typedef void (*fptrNewItem)(Queue*,struct TCB_t *);
typedef struct TCB_t* (*fptrDeleteItem)(Queue*);
typedef	void (*fptrRotateHead)(Queue*);
typedef	void (*fptrInitQueue)(Queue*);
typedef	void (*fptrPrintQueue)(Queue*);
typedef	void (*fptrAddQueue)(Queue*,struct TCB_t *, struct TCB_t *);
typedef	struct TCB_t* (*fptrDelQueue)(Queue* ,struct TCB_t *);
typedef	void (*fptrRotateQ)(Queue*);

typedef struct _Queue{
	int numElements;
	struct TCB_t *head;
	// interface for function
	fptrNewItem NewItem;
	fptrDeleteItem DeleteItem;
	fptrRotateHead RotateHead;
	fptrInitQueue InitQueue;
	fptrPrintQueue PrintQueue;
	fptrAddQueue AddQueue;
	fptrDelQueue DelQueue;
	fptrRotateQ RotateQ;
}Queue;

// forward declaration of Queue functions
Queue* new_Queue(); //constructor, sets pointer functions
void Queue_NewItem(Queue* Q, struct TCB_t *new_item);
struct TCB_t* Queue_DeleteItem(Queue* Q);
void Queue_RotateHead(Queue* Q);
void Queue_InitQueue(Queue* Q);
void Queue_PrintQueue(Queue* Q);
void Queue_AddQueue(Queue* Q, struct TCB_t *head, struct TCB_t *item);
struct TCB_t* Queue_DelQueue(Queue* Q, struct TCB_t *head);
void Queue_RotateQ(Queue* Q);

extern Queue* RunQ; // global Queue

// function definitions
/*constructor, sets pointer functions*/
Queue* new_Queue()
{
	Queue* newQueue;
	/* setting up queue */
	newQueue = (Queue*)malloc(sizeof(Queue));
	newQueue->numElements = 0; //initially set number of elements to 0

	// allow access to Queue functions thru function pointers
	newQueue->NewItem = Queue_NewItem;
	newQueue->DeleteItem = Queue_DeleteItem;
	newQueue->RotateHead = Queue_RotateHead;
	newQueue->InitQueue = Queue_InitQueue;
	newQueue->PrintQueue = Queue_PrintQueue;
	newQueue->AddQueue = Queue_AddQueue;
	newQueue->DelQueue = Queue_DelQueue;
	newQueue->RotateQ = Queue_RotateQ;

	return newQueue; //after obj creation can access data members and function similar to C++ class inheritance
}

/*returns a pointer to a new qelement*/
void Queue_NewItem(Queue* Q, struct TCB_t *new_item)
{
	int i;
	struct TCB_t *temp;

	if (Q->numElements == 0) { //first Queue element added
		Q->head = new_item;
		Q->InitQueue(Q);
	} else {
		temp = Q->head->previous;
		Q->AddQueue(Q,temp, new_item);
	}

	Q->numElements++;
	//Q->PrintQueue(Q);
}


struct TCB_t* Queue_DeleteItem(Queue* Q)
{
	struct TCB_t *d_node;

	d_node = Q->DelQueue(Q,Q->head);
	//Q->PrintQueue(Q);

	return d_node;
}

void Queue_RotateHead(Queue* Q)
{
	Q->RotateQ(Q);
	//Q->PrintQueue(Q);
}

/*creates an empty queue, pointed to by the variable head*/
void Queue_InitQueue(Queue* Q)
{
	Q->head->next = Q->head;
	Q->head->previous = Q->head;
}

/*adds a queue item pointed to by "item" to the queue pointed to by head*/
void Queue_AddQueue(Queue* Q, struct TCB_t *tempHead, struct TCB_t *item)
{
	tempHead->next = item;
	item->next = Q->head;
	item->previous = tempHead;
	Q->head->previous = item; 
}

/*deletes an item from head and returns a pointer to the deleted item*/
struct TCB_t* Queue_DelQueue(Queue* Q, struct TCB_t *tempHead)
{
	struct TCB_t *deleteNode;

	deleteNode = tempHead;
	/* assuming rotating clockwise */
	Q->head = deleteNode->next;
	(deleteNode->previous)->next = deleteNode->next;
	(deleteNode->next)->previous = deleteNode->previous;
	
	//free(deleteNode); // corrupts heap
	Q->numElements--;

	return deleteNode;
}

/*moves the head pointer to the next element in the queue*/
void Queue_RotateQ(Queue* Q)
{
	if (Q->numElements > 1)
		Q->head = Q->head->next;
	//else
	//	printf("No rotation!\n");
}

void Queue_PrintQueue(Queue* Q)
{
	int i;
	struct TCB_t *temp;
	temp = RunQ->head;

	printf("Thread Head= %p\n", RunQ->head);

	for (i = 0; i < RunQ->numElements; i++) {
		printf("Item %d = %p\n", i+1, temp);
		temp = temp->next;
	}
}
