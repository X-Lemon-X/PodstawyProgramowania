
#include "Stos.h"
#include <stdio.h>
#include <stdlib.h>

void Init(Lista *lista)
{
  lista->count=0;
  lista->first=NULL;
  lista->last=NULL;
}

void Push(Lista *lista, Element element)
{   
  Element *temp = (Element*)malloc(sizeof(Element));
  temp->data = element.data;
  element.next==NULL;
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
    if(element!=NULL)
    {
      element->data = lista->last->data;
      //element->el = lista->last->el;
    }

    if(lista->last->next != NULL)
    {
      Element *temp = lista->last->next;
      //free(lista->last->el);
      free(lista->last);
      lista->last = temp;
    }
    else
    {
      //free(lista->last->el);
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
  for (size_t i = 0; i < Count(lista); i++)
    Pop(lista,NULL);
}

int Count(Lista *lista)
{
  return lista->count;
}

int Print(Lista *lista,size_t n_lastelements, FILE *stream)
{
  if(lista==NULL);
  Element *el = lista->last;
  size_t count=0;
  while ( el != NULL && count++ < n_lastelements)
  {
    fprintf(stream,"%d, ",(TYPE_OF_DATA)el->data);
    el = el->next;
  }
}
