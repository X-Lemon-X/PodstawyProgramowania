#include <stdio.h>
#include "Stos.h"

#define SIZE (size_t)40

void clearbuff(void *buffor, size_t size);

int main()
{
  Element elem;
  Lista numbers;
  Init(&numbers);
  char buf[SIZE];
  char oper='\0', signNext;
  int arg;
  printf("Calculator start:\n");

  while(1){
    
    clearbuff(buf,SIZE);
    scanf("%40s", buf); 

    if(isdigit(buf[0]) || (buf[0]== '-' && isdigit(buf[1]))) 
    {
      Element el; el.data=atoi(buf);
      Push(&numbers,el);
    }
    else oper = buf[0];

    if(isalpha(oper)){
    switch (oper)
    {
    case 'q':{ Clear(&numbers);
      return;
    }
    case 'P':{ Pop(&numbers,NULL);
      break;
    }
    case 'c':{ Clear(&numbers);
      break;
    }
    case 'r':{
      if(Count(&numbers)>=2){
      Element el1, el2;
      Pop(&numbers,&el1);
      Pop(&numbers,&el2);
      Push(&numbers,el1);
      Push(&numbers,el2);
      }
      break;
    }
    case 'd':{
     if(Count(&numbers)>=1){
      Element el1;
      Pop(&numbers,&el1);
      Push(&numbers,el1);
      Push(&numbers,el1);
      }
      break;
    }
    case 'p':{
      printf("Stack last elemnt:\n[");
      Print(&numbers,1,stdout);
      printf("]\n");
      break;
    }
    case 'f':{
      printf("Stack all elemnt:\n[");
      Print(&numbers,Count(&numbers),stdout);
      printf("]\n");
      break;
    }
    default: printf("Invalid option! [%c]\n",oper);
      break;
    }
    }

    if(!isalpha(oper) && Count(&numbers)>=2)
    { 
      Element el1, el2;
      Pop(&numbers,&el2);
      Pop(&numbers,&el1);
      int num1=el1.data, num2=el2.data, result, cond=1;
     
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
      default: cond=0;
        break;
      }

      if(cond){
        printf("Equation: %i %c %i = %i\n", num1,oper, num2, result);
        el1.data = result;
        Push(&numbers,el1);
      }
      else{
        Push(&numbers,el1);
        Push(&numbers,el2);
        printf("Invalid operation! [%c]\n",oper); 
      }
    }

    printf("Numbers[");
    Print(&numbers,Count(&numbers),stdout);
    printf("]\n");
    oper='\0';
  }

  printf("Calculator stop!\n");
  return 0;
}

void clearbuff(void *buffor, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    *(size_t*)(buffor++)=0;
  }
}