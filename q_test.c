/************************************************
 * Operating Systems CSE 430
 * Project 1 - Circular doubly linked list
 *
 * Copyright (c) 2015
 *      Sydney Vanda
 *      Brittney RUssell
 *
 *  Module Name:
 *      \file q_test.cpp
 *
 *  Description:
 *      \brief Queue processing test
 *
 *
 ***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include "q.h"

Queue* RunQ; // global Queue

int main()
{
	int selection = 0;
	int data = 0;
	struct TCB_t *newElem;

	RunQ = new_Queue(); // allow RunQ to access all data members and functions of Queue struct

	while(selection != 5)
	{
	printf("Queue Test\n");
	printf(" 1. Add Element\n 2. Delete Element\n 3. Rotate Head\n 4. Print Queue\n 5. Quit\n");

	printf("Select Menu Option: ");
	scanf("%d", &selection);

		switch(selection)
		{
		case 1:
			printf("Data to add: ");
			scanf("%d", &data);

			newElem = RunQ->NewItem(data);
			break;

		case 2:
			printf("Delete Item.\n");
			RunQ->DeleteItem();
			break;

		case 3:
			printf("Rotate Head.\n");
			RunQ->RotateHead();
			break;

		case 4:
			printf("Printing Queue.\n");
			RunQ->PrintQueue();
			break;

		case 5:
			printf("Bye!\n");
			return -1;

		default:
			printf("Not reaching case!\n");
			return -1;
		}
	}

}
