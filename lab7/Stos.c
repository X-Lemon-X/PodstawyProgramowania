
#include "Stos.h"
#include <stdio.h>
#include <stdlib.h>


void Init(Stack *stack, _data_type_type type)
{
  stack->typeOfData = type;
  stack->count=0;
  stack->first=NULL;
  stack->last=NULL;
}

void Push(Stack *stack, Element element)
{   
  Element *temp = (Element*)malloc(sizeof(Element));
  temp->data = element.data;
  element.next==NULL;
  stack->count++;

  if(stack->first==NULL)
  {
    temp->next=NULL;
    stack->last = temp;
    stack->first = temp;
    return;  
  }
  temp->next = stack->last;
  stack->last = temp;
  
}

void Pop(Stack *stack, Element *element)
{
    if(stack == NULL) return;

    if(stack->last == NULL) return;
 
    stack->count--;
    
    if(element!=NULL)
      element->data = stack->last->data;
    else if(stack->typeOfData == _Custom)
    {
      free(stack->last->data._custom);
    }

    if(stack->last->next != NULL)
    {
      Element *temp = stack->last->next;
      free(stack->last);
      stack->last = temp;
    }
    else
    {
      free(stack->last);
      stack->last = NULL;
      stack->first = NULL;
    }
}

int Top(Stack *stack)
{
    if(stack == NULL) return -2;
    return stack->count;
}

void Clear(Stack *stack)
{
  while (Count(stack)!=0)
     Pop(stack,NULL);
}

int Count(Stack *stack)
{
  return stack->count;
}

int Print(Stack *stack,size_t n_lastelements, FILE *stream)
{
  if(stack==NULL);
  Element *el = stack->last;
  size_t count=0;
  char *format;

  switch (stack->typeOfData)
  {
  case _Int: 
    format = "%i,";
    while ( el != NULL && count++ < n_lastelements)
    {
      fprintf(stream,format,el->data._int);
      el = el->next;
    }
    break;
  case _Char: 
    format = "%c,";
    while ( el != NULL && count++ < n_lastelements)
    {
      fprintf(stream,format,el->data._char);
      el = el->next;
    }
    break;
  case _Float: 
    format = "%f,";
    while ( el != NULL && count++ < n_lastelements)
    {
      fprintf(stream,format,el->data._float);
      el = el->next;
    }
    break;
  case _Double: 
    format = "%ld,";
    while ( el != NULL && count++ < n_lastelements)
    {
      fprintf(stream,format,el->data._double);
      el = el->next;
    }
    break;
  default:  fprintf(stream,"Can't print Custom values\n");
    return;
  }

 
}

int GetDataType(Stack *stack)
{
  return stack->typeOfData;
}

Element SetValue( _data_type data)
{   
  Element element;
  element.data = data;
  return element;
}

_data_type GetValue(Element element)
{
    return element.data;
}
