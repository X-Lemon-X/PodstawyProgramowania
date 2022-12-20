
#include "Stos.h"

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

void Pop(Lista *lista)
{
    if(lista == NULL) return;

    if(lista->last == NULL) return;
 
    if(lista->last->next == NULL)
    {
        lista->last = NULL;
        lista->first = NULL;
    }
    lista->count--;

    Element *temp = lista->last->next;
    free(lista->last);
    lista->last = temp;
}

int Top(Lista *lista)
{
    if(lista == NULL) return -2;

    return lista->count;
}


void main()
{
  Element el;
  Lista lista;

  int ele = Top(&lista);
  el.data = 1;

  Push(&lista,&el);

el.data =2;
  Push(&lista,&el);
ele = Top(&lista);
el.data =3;
  Push(&lista,&el);

el.data =4;
  Push(&lista,&el);

ele = Top(&lista);
el.data =5;
  Push(&lista,&el);

    Pop(&lista);
    Pop(&lista);
    Pop(&lista);

}