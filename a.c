#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    size_t x;
    size_t y;
}Position;

Position z1d_na2d(size_t index)
{
    Position pos;
    pos.y = index/5;
    pos.x =  index%5;
    return pos;
}

size_t z2d_na1d(Position pos)
{
    return pos.y*5 + pos.x;
}

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

Position ruch(Position pos, int ruch)
{
    Position posNew = { posNew.x = pos.x , posNew.y = pos.y};
    switch (ruch)
    {
    case LEFT:
        posNew.x--;
        if(posNew.x<0) posNew.x=0;
    break;
    case RIGHT:
        posNew.x++;
        if(posNew.x<5) posNew.x=5;
    break;
    
    case UP:
        posNew.y--;
        if(posNew.y<0) posNew.y=0;
    break;
    
    case DOWN:
        posNew.y++;
        if(posNew.y>5) posNew.y=5;
    break;
    
    default:
        break;
    }
    return posNew;
}

int mainM ( ) {
    int i , ti [ 15 ] , *tp1 [ 15 ] , *tp2[ 15 ] , *tp3 [ 15 ] ,*tp4 [ 15 ] ;
    for( i =0; i <=14; i ++) {
        ti [ i ]= i ;
        tp1 [ i ]= i ;
        tp2[ i ]=&i;
        tp3[ i ]=&ti [ i ] ;
        tp4[14 - i ]= ti +i ;
    }
    printf( "%d\n" , tp1 [ 10 ] ) ;
    printf( "%p\n" , tp1 [ 10 ] ) ;
    //printf( "%d\n" , *( tp1 [ 10 ] ) ) ;
printf( "%d\n" , *( ti + *tp4 [ *( ti + 3 ) ] ) ) ;
    return 1;
}



 int MaxEl(int *tablica, size_t size)
 {
    int maxprev=*tablica;
    for (;size-- != 0; tablica++)
    {
        if(*tablica > maxprev) maxprev = *tablica;
        
    }
    return maxprev;
 }
#define LENGTH 40
 void dopisz(char *p, char *q)
 {
    int sizeP = strlenV2(p);
    int sizeQ = strlenV2(q);
    if(sizeP + sizeQ > LENGTH) return;
    p+=sizeP;
    for (;sizeQ--;) *p++ = *q++;
 }



int strlenV2( char *str)
{
    int count=0;
    while ( *str !=  0)
    {
        str++;
        count++;
    }
    return count;
}

int strlenV3( char str[])
{
    int count=0;
    while ( *str !=  0)
    {
        str++;
        count++;
    }
    return count;
}


int main(int agr, char *args[]){

    if(agr >= 2){

    }

    int aco = ((int)0.1*17);
    //printf("%i\n",aco);

    int tabe[] = {1,6,3,4,5,8};

    mainM();


    char nameN[LENGTH] = "siema";
    char *name = " byku";
    dopisz(nameN,name);
    

return 0 ;

     for (size_t p = 0; p < 4; p++)
        {
            printf("tab[%i]: %i  ",p, (p));
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
    
    return 0;
}
