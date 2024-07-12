#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Line {
    int x1;
    int y1;
    int x2;
    int y2;
} Line;

typedef struct node {
    void *value;
    struct node* next;
    struct node* last;
} node;

typedef struct linkedList {
    node* head;
    node* tail;
    int len;
} linkedList;

linkedList* newList() {
    linkedList* list = (struct linkedList*)malloc(sizeof(linkedList));
    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
    return list;
}

node* newNode(void *newData) {
    node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->next = NULL;
    newNode->last = NULL;
    newNode->value = newData;
    return newNode;
}

void pushFirst(linkedList* l, void *value) {
    node* n = newNode(value);
    if (l->head == NULL) {
        l->head = n;
        l->tail = n;
    } else {
        n->next = l->head;
        l->head->last = n;
        l->head = n;
    }
    l->len++;
}

void printList(linkedList* l, void (*fptr)(void *)) {
    node* cursor = l->head;
    for (int i = 0; i < l->len; i++){
        (*fptr)(cursor->value);
        cursor = cursor->next;
    }
    puts("\n");
}

void* listPopFirst(linkedList* l) {
    assert(l->head != NULL);
    void *ret = l->head->value;
    l->head->next->last = NULL;
    node * newHead = l->head->next;
    free(l->head);
    l->len--;
    l->head = newHead;
    return ret;
}

void* listPopLast(linkedList* l) {
    assert(l->tail != NULL);
    void *ret = l->tail->value;
    l->tail->last->next = NULL;
    node * newTail = l->tail->last;
    free(l->tail);
    l->len--;
    l->tail = newTail;
    return ret;
}

void linkedListDel(linkedList* l) {
    node* cursor = l->head;
    for (int i = 0; i < l->len; i++) {
        node* temp = cursor->next;
        free(cursor);
        cursor = temp;
    }
    free(l);
}

void printLine(void *value) {
    Line *line = (struct Line *)value;
    printf("{%d, %d, %d, %d}->", (int)line->x1, (int)line->y1, (int)line->x2, (int)line->y2);
}
