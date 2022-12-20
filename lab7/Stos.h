#include <stdio.h>
#include <stdlib.h>

#ifndef STOS_H
#define STOS_H

typedef struct  {
    int data;
    struct Element *next;
}Element;

typedef struct {
    Element *first;
    Element *last;

    int count;
    Element watchdog;
}Lista;

void Push(Lista *lista, Element *elem);
void Pop(Lista *lista);
int Top(Lista *lista);




#endif