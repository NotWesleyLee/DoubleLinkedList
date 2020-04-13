//
//  dlist.h
//  linked_list
//
//  Created by William McCarthy on 084//20.
//  Copyright © 2020 William McCarthy. All rights reserved.
//

#ifndef dlist_h
#define dlist_h

#include <stdio.h>
#include <stdbool.h>


//-------------------------------------------------
typedef struct dnode dnode;
struct dnode {
  int data;
  dnode* prev;
  dnode* next;
};

typedef struct dlist dlist;
struct dlist {
  dnode* head;
  dnode* tail;
  size_t size;
};

//-------------------------------------------------
dnode* dnode_create(int data, dnode* prev, dnode* next);
dlist* dlist_create(void);

bool dlist_empty(dlist* list);
size_t dlist_size(dlist* list);

void dlist_popfront(dlist* list);
void dlist_popback(dlist* list);

void dlist_pushfront(dlist* list, int data);
void dlist_pushback(dlist* list, int data);

void dlist_clear(dlist* list);
void dlist_print(dlist* list, const char* msg);

int dlist_front(dlist* list);
int dlist_back(dlist* list);

void dlist_test(void);

dnode* dnode_create(int data, dnode*prev, dnode* next) {
	dnode* p = (dnode*)malloc(sizeof(dnode));
	p->data = data;
	p->next = next;
	p->prev = prev;
	return p;
}

dlist* dlist_create(void)
{
	dlist* p = (dlist*)malloc(sizeof(dlist));
	p->head = NULL;
	p->tail = NULL;
	p->size = 0;

	return p;
}


void checkempty(dlist* list) {
	if (dlist_empty(list)) {
		fprintf(stderr, "list is empty\n");
		exit(1);
	}
}

void dlist_pushfront(dlist* list, int data)
{
	dnode* p = dnode_create(data, NULL, list->head);
	if (list->head != NULL) { list->head->prev = p; }
	list->head = p;
	if (list->size == 0) { list->tail = p; }
	++list->size;
}

void dlist_pushback(dlist* list, int data)
{
	if (list->size == 0) { dlist_pushfront(list, data); return; }

	dnode* p = dnode_create(data, list->tail, NULL);
	list->tail->next = p;
	list->tail = p;
	++list->size;
}

void dlist_popfront(dlist* list) {
	checkempty(list);
	dnode* p = list->head;
	list->head = list->head->next;
	list->head->prev = NULL;
	free(p);
	--list->size;

}

void dlist_popback(dlist* list) {
	checkempty(list);

	dnode* p = list->head;
	dnode* prev = p;
	while (p->next != NULL)
	{
		prev = p;
		p = p->next;
	}
	prev->next = NULL;
	free(p);
	list->tail = prev;
	--list->size;
}

int dlist_front(dlist* list) {
	checkempty(list);
	return list->head->data;
}

int dlist_back(dlist* list) {
	checkempty(list);
	return list->tail->data;
}

bool dlist_empty(dlist* list) {
	return list->size == 0;
}
size_t dlist_size(dlist* list) { return list->size; }

void dlist_clear(dlist* list) {
	while (!dlist_empty(list)) {
		dlist_popback(list);
	}
}

void dlist_print(dlist* list, const char* msg) {
	printf("%s\n", msg);
	if (dlist_empty(list)) { printf("List is empty\n"); return; }
	dnode* p = list->head;
	while (p != NULL) {
		printf("%d --> %p\n", p->data, p->next);
		p = p->next;
	}
}

#endif /* dlist_h */
