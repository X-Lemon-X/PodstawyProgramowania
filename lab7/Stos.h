#include <stdio.h>
#include <stdlib.h>

#ifndef STOS_H
#define STOS_H

typedef int TYPE_OF_DATA;

typedef struct  {
    TYPE_OF_DATA data;
    struct Element *next;
}Element;

typedef struct {
    Element *first;
    Element *last;

    int count;
    Element watchdog;
}Lista;

void Init(Lista *lista);
void Push(Lista *lista, Element *element);
void Pop(Lista *lista, Element *element);
int Top(Lista *lista);
void Clear(Lista *lista);
int Count(Lista *lista);
int Print(Lista *lista, FILE *stream);




#endif