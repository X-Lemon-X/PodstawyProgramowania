#include <stdio.h>
#include <stdlib.h>

#ifndef STOS_H
#define STOS_H

typedef int TYPE_OF_DATA;

// niepotrzebne ale może jendak nie
typedef enum {
    _Int =1,
    _Char=2,
    _Float=3,
    _Double=4,
    _Custom=5,
}_data_type_type;

// prztrzymóje dane 
typedef union {
    int _int;
    char _char;
    float _float;
    double _double;
    void *_custom;
}_data_type;

// struktóra pojednyńczego elemnt w stosie
typedef struct  {
    _data_type data;
    struct Element *next;
}Element;


//struktóra stosu
typedef struct {
    Element *first;
    Element *last;
    int count;
    int typeOfData;
}Stack;


//inicjuje stos
void Init(Stack *stack, _data_type_type type);

//wstawia następny elemet do stosu
void Push(Stack *stack, Element element);

//usówa ostatni elemet ze stosu
void Pop(Stack *stack, Element *element);


int Top(Stack *stack);

//czyści stos zwalani całą pamięć
void Clear(Stack *stack);

//zwraca ilość elementów na stosie
int Count(Stack *stack);

//drokuje stos na dany stream
int Print(Stack *stack, size_t n_lastelements, FILE *stream);

//zwraca rodzaj danych jaki jest n astosie
int GetDataType(Stack *stack);

//ustawia wartość elemen pozwala skrócic zapis o 1 linijkę
Element SetValue(_data_type data);

//pobiera wartość elementu pozwala skrócic zapis o 1 linijkę
_data_type GetValue(Element element);

#endif