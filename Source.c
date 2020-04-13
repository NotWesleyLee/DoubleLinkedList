#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include"dlist.h"
#include"slist.h"
#include"utils.h"
#include<assert.h>

//-------------------------------------------------
static void slist_check_frontback(slist* list, int front, int back) {
    printf("assert front of list is: %d\n", front);
    assert(slist_front(list) == front);
    printf("assert back of list is: %d\n", back);
    assert(slist_back(list) == back);
}

//-------------------------------------------------
static void slist_test_once(slist* list, int start, int end, int step, void (*fp)(slist*, int)) {
    for (int i = start; i < end; i += step) {
        fp(list, i);
    }
    slist_print(list, "list is created and is...");
    printf("list size is: %zu\n", slist_size(list));
    printf("list is empty? %s\n\n", yesorno(slist_empty(list)));

    int firstadded = start;
    int lastadded = start;
    while (lastadded + step < end) {
        lastadded += step;
    }
    if (fp == slist_pushback) { slist_check_frontback(list, firstadded, lastadded); }
    if (fp == slist_pushfront) { slist_check_frontback(list, lastadded, firstadded); }

    slist_clear(list);
    printf("after clearing the list, is the list is now empty? %s\n\n", yesorno(slist_empty(list)));
}

//-------------------------------------------------
void slist_test() {
    printf("\n//===================== TESTING SLIST =========================\n\n");
    slist* list = slist_create();
    slist_test_once(list, 10, 50, 10, slist_pushfront);
    slist_test_once(list, 10, 100, 20, slist_pushback);

    printf("\n    All Assertions passed!...\n");
    free(list);
    printf("//===================== END TESTING SLIST =========================\n\n");
}

static void dlist_check_frontback(dlist* list, int front, int back) {
    printf("assert front of list is: %d\n", front);
    assert(dlist_front(list) == front);
    printf("assert back of list is: %d\n", back);
    assert(dlist_back(list) == back);
}

//-------------------------------------------------
static void dlist_test_once(dlist* list, int start, int end, int step, void (*fp)(dlist*, int)) {
    for (int i = start; i < end; i += step) {
        fp(list, i);
    }
    dlist_print(list, "list is created and is...");
    printf("list size is: %zu\n", dlist_size(list));
    printf("list is empty? %s\n", yesorno(dlist_empty(list)));

    int firstadded = start;
    int lastadded = start;
    while (lastadded + step < end) {
        lastadded += step;
    }
    if (fp == dlist_pushback) { dlist_check_frontback(list, firstadded, lastadded); }
    if (fp == dlist_pushfront) { dlist_check_frontback(list, lastadded, firstadded); }

    dlist_clear(list);
    printf("after clearing the list, is the list is now empty? %s\n\n", yesorno(dlist_empty(list)));
}

//-------------------------------------------------
void dlist_test() {
    printf("//===================== TESTING DLIST =========================\n\n");
    dlist* list = dlist_create();
    dlist_test_once(list, 10, 50, 10, dlist_pushfront);
    dlist_test_once(list, 10, 100, 20, dlist_pushback);
    dlist_test_once(list, 0, 100, 1, dlist_pushback);

    printf("      All Assertions passed!...\n");
    free(list);
    printf("//===================== END TESTING DLIST =========================\n\n");
}

int main(int argc, const char* argv[]) {
	slist_test();
	dlist_test();

	return 0;
}
