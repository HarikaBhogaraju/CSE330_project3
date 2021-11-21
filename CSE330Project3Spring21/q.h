//including standard libraries
#include<stdio.h>
#include<stdlib.h>
//including TCB.h to change typeto TCB_t
#include "tcb.h"

//struct type for queue implementation
typedef struct q
{
	//pointer to head of queue
	struct TCB_t *head;
}q;

//creating empty queue using q
void initQueue(q *headOfQ)
{
	//pointing head to NULL
	//empty queue
	headOfQ->head = NULL;
}

//creates a new queue element of type TCB_t and returns it
TCB_t *newItem()
{
	//allocating memory for new item using malloc
	TCB_t *newItm = (TCB_t *)malloc(sizeof(TCB_t));
	//pointing next and prev to NULL
	newItm->next = NULL;
    newItm->prev = NULL;
        //returning new queue element
	return newItm;
}

//adds item to the queue
void addQueue(q *headOfQ, TCB_t *item)
{
	//adds in the start if queue is empty
	if(headOfQ->head == NULL)
	{
		headOfQ->head = item;
		item->next = item;
		item->prev = item;
	}
	else
	{
		//adds to the end
		item->prev = headOfQ->head->prev;
		item->next = headOfQ->head;
		headOfQ->head->prev->next = item;
		headOfQ->head->prev = item;
	}
}

// deletes item from the head and return it
TCB_t * delQueue(q *headOfQ)
{
	//if queue is empty
	if(headOfQ->head == NULL)
	{
		//return NULL
		return NULL;
	}
	//temp pointer to help delete
	TCB_t *temp = headOfQ->head;
	//if next item and curr item is same
	if(headOfQ->head->next == headOfQ->head)
	{
		headOfQ->head = NULL;
		return temp;
	}
	//if not same
	else
	{
		//setting next item prev as current prev
		headOfQ->head->next->prev = headOfQ->head->prev;
		//setting prev item next as current next
		headOfQ->head->prev->next = headOfQ->head->next;
		//setting next as curr
		headOfQ->head = headOfQ->head->next;
		//setting head next and prev NULL
		temp->next = temp->prev = NULL;
		return temp;
	}
}

//moves head pointer to the next pointer
void rotateQ(q *headOfQ)
{
	//checking if queue is not empty and then assigning
	if(headOfQ->head != NULL)
	{
		headOfQ->head = headOfQ->head->next;
	}
}
