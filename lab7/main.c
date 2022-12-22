#include <stdio.h>
#include "Stos.h"


int main()
{
  Element elem;
  Lista numbers;
  Init(&numbers);
  char oper='\0', signNext;
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

      if(oper=='-')
      {
        signNext = getc(stdin);
        if(signNext != ' ')
        {
          ungetc(signNext,stdin);
          
        }
        else
        {
          scanf("%d",&arg);
          arg = -arg;
          oper='\0';
          elem.data = arg;
          Push(&numbers,&elem);
        }
      }

      if(oper != '+' && oper != '-' && oper != '*' && oper != '/' && oper != 'q') oper = '\0';

    }

    printf("operacja >%c \n",oper);

    if(oper!='\0' && Count(&numbers)>=2)
    {
      
      Element el1, el2;
      Pop(&numbers,&el2);
      Pop(&numbers,&el1);
      int num1=el1.data, num2=el2.data, result;
      printf("operacja >%c  wykonywanie liczba1: %i   liczba2: %i\n",oper, num1, num2);

      switch (oper)
      {
      case '+':
        result = num1+num2;
        break;
      case '-':
        result = num1-num2;
        break;
      case '*':
        result = num1*num2;
        break;
      case '/':
        result = num1/num2;
        break;

      default: printf("Sign error!\n");
        break;
      }

      printf("resultat=>%i\n",result);
      el1.data = result;
      //el1.next = NULL;
      Push(&numbers,&el1);
      oper='\0';
    }

    printf("Numbers!\n");
    Print(&numbers,stdout);
    printf("\n--------\n");
  }


  return 0;
}