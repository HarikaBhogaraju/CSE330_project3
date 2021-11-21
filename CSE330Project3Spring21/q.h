//including standard libraries
#include<stdio.h>
#include<stdlib.h>
//including TCB.h to change typeto TCB_t
#include "tcb.h"

//struct type for queue implementation
typedef struct q
{
	//pointer to element of queue
	struct TCB_t *element;
}q;

//creating empty queue using q
void InitQueue(q *head)
{
	//pointing element to NULL
	//empty queue
	head->element = NULL;
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
void AddQueue(q *head, TCB_t *item)
{
	//adds in the start if queue is empty
	if(head->element == NULL)
	{
		head->element = item;
		item->next = item;
		item->prev = item;
	}
	else
	{
		//adds to the end
		item->prev = head->element->prev;
		item->next = head->element;
		head->element->prev->next = item;
		head->element->prev = item;
	}
}

// deletes item from the element and return it
TCB_t * DeleteQueue(q *head)
{
	//if queue is empty
	if(head->element == NULL)
	{
		//return NULL
		return NULL;
	}
	//temp pointer to help delete
	TCB_t *temp = head->element;
	//if next item and curr item is same
	if(head->element->next == head->element)
	{
		head->element = NULL;
		return temp;
	}
	//if not same
	else
	{
		//setting next item prev as current prev
		head->element->next->prev = head->element->prev;
		//setting prev item next as current next
		head->element->prev->next = head->element->next;
		//setting next as curr
		head->element = head->element->next;
		//setting element next and prev NULL
		temp->next = temp->prev = NULL;
		return temp;
	}
}

//moves element pointer to the next pointer
void rotateQ(q *head)
{
	//checking if queue is not empty and then assigning
	if(head->element != NULL)
	{
		head->element = head->element->next;
	}
}
