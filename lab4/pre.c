#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define TABLE_SIZE_X 10
#define TABLE_SIZE_Y 10

struct Tablica
{
    int tablica[TABLE_SIZE_X][TABLE_SIZE_Y];
    int sizeX;
    int sizeY;
};

struct Menu
{
    char *string;
};


// ----------------- przygotowawcze
void WypelnijIloczynem(struct Tablica *,int x, int y);
void CleanTable(struct Tablica *);
void PrintTable(struct Tablica tablica);
void ChangeSignsTable(struct Tablica *);
int DisplayMenu();

int main()
{
    printf("\nStart\n");

    struct Tablica tablica;
    tablica.sizeX = TABLE_SIZE_X;
    tablica.sizeY = TABLE_SIZE_Y;

    while (1)
    {
        switch (DisplayMenu())
        {
        case 1:
            PrintTable(tablica);
            break;
        case 2:
            ChangeSignsTable(&tablica);
            break;
        case 3:
            CleanTable(&tablica);
            break;
        case 4:
            int x,y;
            printf("podaj x:");
            scanf("%i",&x);
            printf("podaj y:");
            scanf("%i",&y);
            WypelnijIloczynem(&tablica,x,y);
            break;
        case 5:
            printf("\nStop\n");
            return 0;
            break;

        default:
            printf("\nzła obcja\n");
            break;
        }
    }
    
}

int DisplayMenu()
{
    int size=5;
    struct Menu menu[5] =
    {   
        {"1 - PrintTable"},
        {"2 - inverseTable"},
        {"3 - CleanTable"},
        {"4 - FillWithCR"},
        {"5 - endProgram"},
    };

    printf("\n--------------------[MENU]-----------------------\n");

    for (size_t i = 0; i < size; i++)
    {
        printf("%s\n",menu[i].string);
    }

    int opcja=0;
    printf("Wybierz opcję: ");
    scanf("%i", &opcja);

    opcja -= 1;

    if(opcja < size && opcja >=0)
    {
        printf("\nwybrałęś: %s \n", menu[opcja].string);
        return ++opcja;
    }
    else
        return -1;
        
}

void ChangeSignsTable(struct Tablica *tablica)
{
    for (size_t x = 0; x < tablica->sizeX; x++)
        for (size_t y = 0; y < tablica->sizeY; y++) tablica->tablica[y][x] *= (-1);
}

void CleanTable(struct Tablica *tablica)
{
    for (size_t y = 0; y < TABLE_SIZE_Y; y++)
        for (size_t x = 0; x < TABLE_SIZE_X; x++) tablica->tablica[y][x] = 0;

}

void WypelnijIloczynem(struct Tablica *tablica,int x, int y)
{
    for (size_t i = 0; i < y; i++)
        for (size_t p = 0; p < x; p++) tablica->tablica[i][p] = i*p; 
         
    tablica->sizeX = x;
    tablica->sizeY = y;
}

void PrintTable(struct Tablica tablica)
{
    printf("Tablica Zawartosc\n");

    for (size_t y = 0; y < tablica.sizeY; y++)
    {
        for (size_t x = 0; x < tablica.sizeX; x++) printf("    %d" ,tablica.tablica[y][x]);
        printf("\n");
    }
    
}