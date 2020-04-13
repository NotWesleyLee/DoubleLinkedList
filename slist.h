//
//  slist.h
//  linked_list
//
//  Created by William McCarthy on 084//20.
//  Copyright © 2020 William McCarthy. All rights reserved.
//

#ifndef slist_h
#define slist_h

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct snode snode;
struct snode {
  int data;
  snode* next;
};

typedef struct slist slist;
struct slist {
  snode* head;
  snode* tail;
  size_t size;
};

snode* snode_create(int data, snode* next);
slist* slist_create(void);

bool slist_empty(slist* list);
size_t slist_size(slist* list);

void slist_popfront(slist* list);
void slist_popback(slist* list);

void slist_pushfront(slist* list, int data);
void slist_pushback(slist* list, int data);

void slist_clear(slist* list);

void slist_print(slist* list, const char* msg);

int slist_front(slist* list);
int slist_back(slist* list);

void slist_test(void);

snode* snode_create(int data, snode* next) {
    snode* p = (snode*)malloc(sizeof(snode));
    p->data = data;
    p->next = next;
    return p;
}

slist* slist_create(void)
{
	slist* p = (slist*)malloc(sizeof(slist));
	p->head = NULL;
	p->tail = NULL;
	p->size = 0;

	return p;
}

void scheckempty(slist* list) {
	if (slist_empty(list)) {
		fprintf(stderr, "list is empty\n");
		exit(1);
	}
}

void slist_pushfront_node(slist* list, snode* no)
{
	no->next = list->head;
	list->head = no;
	if (list->size == 0) { list->tail = no; }
	++list->size;
}

void slist_pushfront(slist* list, int data)
{
	slist_pushfront_node(list, snode_create(data, list->head));
}

void slist_pushback_node(slist* list, snode* no)
{
	if (list->size == 0) { slist_pushfront_node(list, no); return; }

	no->next = NULL;
	list->tail->next = no;
	list->tail = no;
	++list->size;
}

void slist_pushback(slist* list, int data)
{
	slist_pushback_node(list, snode_create(data, NULL));
}

void slist_popfront(slist* list) {
	checkempty(list);
	snode* p = list->head;
	list->head = list->head->next;
	free(p);
	--list->size;
}

void slist_popback(slist* list) {
	if (slist_empty(list)) { fprintf(stderr, "underflow error\n"); exit(1); }

	snode* p = list->head;
	while (p->next != list->tail) { p = p->next; }
	p->next = NULL;
	free(list->tail);
	list->tail = p;
	--list->size;
}

int slist_front(slist* list) {
	scheckempty(list);
	return list->head->data;
}

int slist_back(slist* list) {
	scheckempty(list);
	return list->tail->data;
}

bool slist_empty(slist* list) {
	return list->size == 0;
}
size_t slist_size(slist* list) { return list->size; }

void slist_clear(slist* list) {
	while (!slist_empty(list)) {
		slist_popfront(list);
	}
}

void slist_print(slist* list, const char* msg) {
	printf("%s\n", msg);
	snode* p = list->head;
	while (p != NULL) {
		printf("%d --> %p\n", p->data, p->next);
		p = p->next;
	}
}



#endif /* slist_h */
