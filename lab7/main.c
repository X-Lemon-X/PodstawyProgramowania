#include <stdio.h>
#include "Stos.h"

int main()
{
  Element elem;
  Lista numbers;
  Init(&numbers);
  char oper=' ';
  int arg;

  while(oper != 'q'){
    if(scanf("%d",&arg)){
      printf("Wczytano liczbe: %d\n",arg);
      elem.data = arg;
      Push(&numbers,&elem);
    }
    else{
      oper = getc(stdin);
      printf("Wczytano znak: >%c<\n",oper);
    }

  }


  return 0;
}