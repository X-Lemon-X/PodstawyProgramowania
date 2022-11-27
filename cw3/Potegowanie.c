#include <stdio.h>
#include <stdlib.h>



int main(int agr, char *args[]){

    //if(agr >= 2){
        int x =2;//atoi(args[1]);
        int n =6;//atoi(args[2]);

        int r=1;
        while (n>0)
        {
            if(2%n == 0)
                r = r *x;
            else{
                x = x*x;
                n = n /2;
            }
        }
        
    
  //  }
    return 0;
}