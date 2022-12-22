
#include "Stos.h"
#include <stdio.h>
#include <stdlib.h>

void Init(Lista *lista)
{
  lista->count=0;
  lista->first=NULL;
  lista->last=NULL;
}

void Push(Lista *lista, Element *element)
{   
  Element *temp = (Element*)malloc(sizeof(Element));
  
  if(element==NULL) return;

  temp->data = element->data;
  element->next==NULL;

  lista->count++;

  if(lista->first==NULL)
  {
    temp->next=NULL;
    lista->last = temp;
    lista->first = temp;
    return;  
  }
  temp->next = lista->last;
  lista->last = temp;
  
}

void Pop(Lista *lista, Element *element)
{
    if(lista == NULL) return;

    if(lista->last == NULL) return;
 
    lista->count--;
    element->data = lista->last->data;

    if(lista->last->next != NULL)
    {
      Element *temp = lista->last->next;
      free(lista->last);
      lista->last = temp;
    }
    else
    {
      free(lista->last);
      lista->last = NULL;
      lista->first = NULL;
    }
}

int Top(Lista *lista)
{
    if(lista == NULL) return -2;

    return lista->count;
}

void Clear(Lista *lista)
{
  Element el;
  for (size_t i = 0; i < Count(lista); i++)
    Pop(lista,&el);
}

int Count(Lista *lista)
{
  return lista->count;
}

int Print(Lista *lista, FILE *stream)
{
  if(lista==NULL);
  Element *el = lista->last;
  while ( el != NULL)
  {
    fprintf(stream,"%d, ",(TYPE_OF_DATA)el->data);
    el = el->next;
  }
}

/*
void main()
{
  Element el;
  Lista lista;

  int ele = Top(&lista);
  el.data = 1;

  Push(&lista,&el);
  el.data =2;
  Push(&lista,&el);
  el.data =3;
  Push(&lista,&el);
  Print(&lista,stdout);
    Pop(&lista,&el);
    Pop(&lista,&el);
    Pop(&lista,&el);
  Print(&lista,stdout);
}
*/