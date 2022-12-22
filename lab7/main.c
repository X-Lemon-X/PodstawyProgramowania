#include <stdio.h>
#include "Stos.h"

#define SIZE (size_t)40

void clearbuff(void *buffor, size_t size);
int GetTwonumbers(Lista *numbers, int *num1, int *num2);

int main()
{
  Element elem;
  Lista numbers;
  Init(&numbers);
  char buf[SIZE];
  char oper='\0', signNext;
  int arg;

  while(oper != 'q'){
    
    clearbuff(buf,SIZE);
    scanf("%40s", buf); 

    if(isdigit(buf[0]) || (buf[0]== '-' && isdigit(buf[1]))) 
    {
      Element el; el.data=atoi(buf);
      Push(&numbers,el);
    }
    else oper = buf[0];

    switch (oper)
    {
    case 'q':
      return;
    case 'P': Pop(&numbers,NULL);
      return;
    case 'c': Clear(&numbers);
      return;
    case 'r':{
      if(Count(&numbers)>=2){
      Element el1, el2;
      Pop(&numbers,&el1);
      Pop(&numbers,&el2);
      Push(&numbers,el1);
      Push(&numbers,el2);
      }
      return;
    }
    case 'd':{
     if(Count(&numbers)>=1){
      Element el1;
      Pop(&numbers,&el1);
      Push(&numbers,el1);
      Push(&numbers,el1);
      }
      return;
    }
    case 'p':{
      printf("Stos last elemnt:\n");
      Print(&numbers,1,stdout);
      printf("\n");
      return;
    }
    case 'f':{
      printf("Stos all elemnt:\n");
      Print(&numbers,Count(&numbers),stdout);
      printf("\n");
      return;
    }
    default:
      break;
    }

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
      Push(&numbers,el1);
      oper='\0';
    }

    printf("Numbers:\n");
    Print(&numbers,Count(&numbers),stdout);
    printf("\n");
  }


  return 0;
}

int GetTwoNumbers(Lista *numbers, int *num1, int *num2)
{
  if(Count(numbers)>=2)
  {
    Element el1, el2;
    Pop(&numbers,&el2);
    Pop(&numbers,&el1);
    *num1=el1.data, *num2=el2.data;
    return 0;
  }
  else
    return 1;
}


void clearbuff(void *buffor, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    *(size_t*)(buffor++)=0;
  }
}