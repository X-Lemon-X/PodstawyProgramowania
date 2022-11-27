#include <stdio.h>
#include <stdlib.h>



int main(int agr, char *args[]){

    if(agr >= 2){
        int number= atoi(args[1]);
        int number2= atoi(args[2]);
        int dividerMax =0;

        for(int a=1; a <=min(number2,number); a++)
        {   
            if(number%a ==0 && number2%a ==0){
                printf("divider: %i\n", a);
                dividerMax =a;
            }
        }
        printf("Max divide:%i",dividerMax);
    }
    return 0;
    
}