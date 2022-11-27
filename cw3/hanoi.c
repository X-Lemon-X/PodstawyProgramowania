#include <stdio.h>
#include <stdlib.h>

void hanoi(int n, char A, char B, char C, int *count );

int main(int agr, char *args[]){
    int count=0;
    hanoi(5,'A','B','C',&count);
    printf("%i",count);

}

void hanoi(int n, char A, char B, char C, int *count)
{
  // przekłada n krążków z A korzystając z B na C
  if (n > 0)
  {
    (*count)++;
    hanoi(n-1, A, C, B,count);
    printf("%c -> %c\n",A,C);
    hanoi(n-1, B, A, C,count);
    
  }
}