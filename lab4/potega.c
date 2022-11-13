#include <stdio.h>
#include <stdlib.h>

long potega(int x, int n);

int main(int argc, char* argv[])
{
    if(argc > 1)
    {
        int x = atoi(argv[1]);
        int n = atoi(argv[2]);
        printf("wynik: %i" ,potega(x,n));
        return 0;
    }

    return 1;
}


long potega(int x, int n)
{
    
    long ret =x;

    if(n == 0) return 1;
    else if(n < 0) return 0;
    
    for (; n > 1 ; n--)
    {
        ret *= x;
    }

    return ret;
}
