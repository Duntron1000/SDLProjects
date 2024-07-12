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
    Line value;
    struct node* next;
    struct node* last;
} node;

typedef struct linkedList {
    node* head;
    node* tail;
    int len;
} linkedList;

linkedList* newList() {
    linkedList* list = (linkedList*)malloc(sizeof(linkedList));
    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
    return list;
}

node* newNode(Line v) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->next = NULL;
    newNode->last = NULL;
    newNode->value = v;
    return newNode;
}

void addFirstNode(linkedList* l, Line value) {
    node* n = newNode(value);
    if (l->head == NULL) {
        l->head = n;
        l->tail = n;
    }
    n->next = l->head;
    l->head->last = n;
    l->head = n;
    l->len++;
}

void printList(linkedList* l) {
    node* cursor = l->head;
    for (int i = 0; i < l->len; i++){
        Line line = cursor->value;
        printf("{%d, %d, %d, %d}<->", line.x1, line.y1, line.x2, line.y2);
        cursor = cursor->next;
    }
    puts("\n");
}

Line listPopFirst(linkedList* l) {
    assert(l->head != NULL);
    Line ret = l->head->value;
    l->head->next->last = NULL;
    node * newHead = l->head->next;
    free(l->head);
    l->len--;
    l->head = newHead;
    return ret;
}

Line listPopLast(linkedList* l) {
    assert(l->tail != NULL);
    Line ret = l->tail->value;
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
