#include <stdio.h>
#include <stdlib.h>

int fib(int n);

int main(int agr, char *args[]){

    if(agr >= 1){
        long number= atoi(args[1]);

        long lfib[10000];
        lfib[0]= 1;
        lfib[1]= 1;
        for (size_t i = 2; i < number; i++){
            lfib[i] = lfib[i-1] + lfib[i-2];
        }

        for (size_t i = 0; i < number; i++){
            printf("fiba [%i]: %i\n",i,lfib[i]);
        }
        
        

        int temp;
        int a = 1;
        int b = 1;
        for (int i = 2; i < number; i++) {
            temp = b;
            b = a + b;
            a = temp;
        }
        printf("fib: %i\n",b);
        printf("fib: %i\n",fib(number));
    }
    return 0;
}


/* Funkcja wylicza rekurencyjnie liczby */
/* Fibonacciego. UWAGA: n musi byc >= 0 */
int fib(int n){
    if (n == 0) return 0; 
    else if (n == 1) return 1; 
    else
        return fib(n-1) + fib(n-2);
}