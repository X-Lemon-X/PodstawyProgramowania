#include <stdio.h>
#include "Stos.h"

#define SIZE (size_t)40

void clearbuff(void *buffor, size_t size);

int main()
{
  // inicjalizacja stosu
  _data_type dt;
  Element elem;
  Stack numbers;
  Init(&numbers,_Int);

  char buf[SIZE];
  char oper='\0';
  int arg, conditionLoop=1;

  printf("Calculator start:\n");

  while(conditionLoop){
    
    //czyści buffor wejśćiowy
    clearbuff(buf,SIZE);

    //zczytuje dane wejsciowe do buffora
    scanf("%40s", buf);
    
    //spraddza czy wprowadzona wartość jest liczbą  
    if(isdigit(buf[0]) || (buf[0]== '-' && isdigit(buf[1]))) 
    {
      dt._int=atoi(buf);
      Push(&numbers,SetValue(dt));
    }
    else oper = buf[0];

    // tu wykonywanie są wszytskie opreacje poleceniowe literowe
    if(isalpha(oper)){
    switch (oper)
    {
    case 'q':{ Clear(&numbers);
      conditionLoop=0;
      break;
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

    // tu wykonuje operacje na liczbach w pamięci 
    if(!isalpha(oper) && Count(&numbers)>=2 && oper!='\0')
    { 
      Element el1, el2;
      Pop(&numbers,&el2);
      Pop(&numbers,&el1);
      int num1=GetValue(el1)._int, num2=GetValue(el2)._int, result=0, cond=1;
      char*info="";
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
        if(num2!=0) result = num1/num2;
        else {cond=0; info = " Dividing by zero!";} 
        break;
      default: cond=0;
        break;
      }

      if(cond){
        printf("Equation: %i %c %i = %i\n", num1,oper, num2, result);
        dt._int=result;
        Push(&numbers,SetValue(dt));
      }
      else{
        Push(&numbers,el1);
        Push(&numbers,el2);
        printf("Invalid operation! [%c] %s\n",oper,info); 
      }
    }

    //wyśiwtela za każdym razem wszytskie liczby dostępnew pamięći
    printf("Numbers[");
    Print(&numbers,Count(&numbers),stdout);
    printf("]\n");
    oper='\0';
  }

  printf("Calculator stop!\n");
  return 0;
}


//zapełna buffor zerami
void clearbuff(void *buffor, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    *(size_t*)(buffor++)=0;
  }
}