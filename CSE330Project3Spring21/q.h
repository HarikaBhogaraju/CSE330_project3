//HARIKA BHOGARAJU
#include<stdio.h>
#include<stdlib.h>


#include "tcb.h"


typedef struct q
{

	struct TCB_t *element;
}q;


void InitQueue(q *head)
{

	head->element = NULL;
}


TCB_t *newItem()
{

	TCB_t *item = (TCB_t *)malloc(sizeof(TCB_t));

	item->next = NULL;
    item->prev = NULL;

	return item;
}


void AddQueue(q *head, TCB_t *item)
{

	if(head->element == NULL)
	{
		head->element = item;
		item->next = item;
		item->prev = item;
	}
	else
	{

		item->prev = head->element->prev;
		item->next = head->element;
		head->element->prev->next = item;
		head->element->prev = item;
	}
}


TCB_t * DeleteQueue(q *head)
{

	if(head->element == NULL)
	{

		return NULL;
	}
	TCB_t *delItem = head->element;
	if(head->element->next == head->element)
	{
		head->element = NULL;
		return delItem;
	}
	else
	{
		head->element->next->prev = head->element->prev;
		head->element->prev->next = head->element->next;
		head->element = head->element->next;
		delItem->next = delItem->prev = NULL;
		return delItem;
	}
}

void rotateQ(q *head)
{
	if(head->element != NULL){
		head->element = head->element->next;
	}
}
