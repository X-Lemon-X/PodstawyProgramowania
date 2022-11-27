#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int agr, char *args[]){

    if(agr >= 2){

    }


    int a=5, j=10;

    float z,h =0.13;
    z = h * j;
    j =strlen("Wrocław");

    int tabu[4] = {1,2,3,4};
    int *ta;
    ta = tabu;

     for (size_t p = 0; p < 4; p++)
        {
            printf("tab[%i]: %i  ",p, *(ta+p));
        }
        printf("\n");

    int tabli[3][4] = {1,2,3,4, 5,6,7,8, 9,10,11,12};
    int (*tab)[4];

    tab = tabli[0];

    for (size_t i = 0; i < 3; i++)
    {
        for (size_t p = 0; p < 4; p++)
        {
            printf("tab[%i][%i]: %i  ",i,p, (*tab)[p]);
        }
        printf("\n");
        tab++;
    }
    

    int p = (65-strlen("Wrocław"))/2 ;
    printf("->%f\n",z);
int i=-12;
    return 0;
}