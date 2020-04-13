#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct node node;
struct node {
	int data;
	node* next;
};

node* node_create(int data, node* next) {
	node* p = (node*)malloc(sizeof(node));
	p->data = data;
	p->next = next;
	return p;
}

typedef struct slist slist;
struct slist {
	node* head;
	node* tail;
	size_t size;
};

slist* slist_create(void)
{
	slist*p = (slist*)malloc(sizeof(slist));
	p->head = NULL;
	p->tail = NULL;
	p->size = 0;

	return p;
}

bool slist_empty(slist* list);

void checkempty(slist* list) {
	if (slist_empty(list)) {
		fprintf(stderr, "list is empty\n");
		exit(1);
	}
}

void slist_addfront_node(slist*list, node* no)
{
	no->next = list->head;
	list->head = no;
	if (list->size == 0) { list->tail = no; }
	++list->size;
}

void slist_addfront(slist* list, int data)
{
	slist_addfront_node(list, node_create(data, list->head));
}

void slist_addback_node(slist* list, node* no)
{
	if (list->size == 0) { slist_addfront_node(list, no); return; }

	no->next = NULL;
	list->tail->next = no;
	list->tail = no;
	++list->size;
}

void slist_addback(slist* list, int data)
{
	slist_addback_node(list, node_create(data, NULL));
}

void slist_popfront(slist* list) {
	if (slist_empty(list)) { fprintf(stderr, "underflow error\n"); exit(1); }
	node* p = list->head;
	list->head = list->head->next;
	free(p);

}

void slist_popback(slist* list) {
	if (slist_empty(list)) { fprintf(stderr, "underflow error\n"); exit(1); }
	
	node* p = list->head;
	while (p->next != list->tail) { p = p->next; }
	p->next = NULL;
	free(list->tail);
	list->tail = p;
}

int slist_front(slist* list) {
	checkempty(list);
	return list->tail->data;
}

int slist_back(slist* list) {
	checkempty(list);
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

void slist_print(slist* list, const char*msg) {
	printf("%s\n", msg);
	node* p = list->head;
	while (p != NULL) {
		printf("%d --> %p\n", p->data, p->next);
		p = p->next;
	}
}

void slist_test() {
	slist* list = slist_create();
	int i;
	for (i = 10; i < 50; i += 10) {
		slist_addfront(list, i);
	}
	slist_print(list, "list is now: ");
	slist_clear(list);
	slist_print(list, "list is now: ");
}

int main(int argc, const char* argv[]) {
	slist_test();


	return 0;
}
