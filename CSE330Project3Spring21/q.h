//Harika Bhogaraju
//1216938606
#include <stdio.h>
#include <stdlib.h>
#include "tcb.h"

	struct q{
		TCB_t* element;
	}q;

	TCB_t* newItem() {
		TCB_t* item = (TCB_t*)malloc(sizeof(TCB_t));
		return item;
	}


	void InitQueue(struct q* head) {
		head->element = NULL; //initialize the head if queue
	}


	void AddQueue(struct q* head, struct TCB_t* item) {
		if (head->element == NULL) { //for empty queue
			head->element = item;
			head->element->prev = item;
			head->element->next = item;
    }
		else {
			struct TCB_t* last = head->element->prev;
			item->next = head->element;
			item->prev = last;
			head->element->prev = item;
			last->next = item;
		}
	}

	TCB_t* DeleteQueue(struct q* head) {
		TCB_t* deletedItem = (TCB_t*)malloc(sizeof(TCB_t));
		deletedItem = head->element;

		if (head->element != NULL) { //for empty queue
			if (head->element->next == NULL) {
				head->element = NULL;
			}
			else {
				deletedItem->prev->next = deletedItem->next;
				deletedItem->next->next->prev = deletedItem->prev;
				head->element = deletedItem->next;
			}
		}

		return deletedItem;
	}

	void RotateQ(struct q* head) {
		AddQueue(head, DeleteQueue(head));
	}
