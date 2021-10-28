//Harika Bhogaraju
//1216938606
#include <stdio.h>
#include <stdlib.h>
#include "tcb.h"

	struct q{
		TCB_T* element;
	}q;

	TCB_T* newItem() {
		TCB_T* item = (TCB_T*)malloc(sizeof(TCB_T));
		return item;
	}


	void InitQueue(struct q* head) {
		head->element = NULL; //initialize the head if queue
	}


	void AddQueue(struct q* head, struct TCB_T* item) {
		if (head->element == NULL) { //for empty queue
			head->element = item;
			head->element->prev = item;
			head->element->next = item;
    }
		else {
			struct TCB_T* last = head->element->prev;
			item->next = head->element;
			item->prev = last;
			head->element->prev = item;
			last->next = item;
		}
	}

	TCB_T* DeleteQueue(struct q* head) {
		TCB_T* deletedItem = (TCB_T*)malloc(sizeof(TCB_T));
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
