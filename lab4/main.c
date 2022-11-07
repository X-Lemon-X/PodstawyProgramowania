#include <stdio.h>

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


void WypelnijIloczynem(struct Tablica *,int x, int y);
void CleanTable(struct Tablica *);
void PrintTable(struct Tablica tablica);
void ChangeSignsTable(struct Tablica *);
void Menu();


int main()
{
    printf("\nStart\n");

    struct Tablica tablica;
    CleanTable(&tablica);

    WypelnijIloczynem(&tablica,7,3);

    PrintTable(tablica);

    ChangeSignsTable(&tablica);

    PrintTable(tablica);

    Menu();

    printf("\nStop\n");
}

void Menu()
{
    int size=5;
    struct Menu menu[5] =
    {   
        {"Opcja 0"},
        {"Opcja 1"},
        {"Opcja 2"},
        {"Opcja 3"},
        {"Opcja 4"},
    };


    for (size_t i = 0; i < size; i++)
    {
        printf("%s\n",menu[i].string);
    }

    int opcja=0;
    printf("Wybierz opcję: ");
    scanf("%i", &opcja);
    
    switch (opcja)
    {
    case 0:
        printf("wpbrałeś: 0");
        break;
    case 1:
        printf("wpbrałeś: 1");
        break;
    case 2:
        printf("wpbrałeś: 2");
        break;
    case 3:
        printf("wpbrałeś: 3");
        break;
    case 4:
        printf("wpbrałeś: 4");
        break;

    default:
        printf("zła obcja");
        Menu();
        break;
    }

}

void ChangeSignsTable(struct Tablica *tablica)
{
    for (size_t x = 0; x < tablica->sizeX; x++)
    {
        for (size_t y = 0; y < tablica->sizeY; y++)
        {
            tablica->tablica[y][x] *= (-1);
        }
    }
}

void CleanTable(struct Tablica *tablica)
{
    for (size_t y = 0; y < TABLE_SIZE_Y; y++)
    {
        for (size_t x = 0; x < TABLE_SIZE_X; x++)
        {
            tablica->tablica[y][x] = 0;
        }
    }
}

void WypelnijIloczynem(struct Tablica *tablica,int x, int y)
{
    for (size_t i = 0; i < y; i++)
    {
        for (size_t p = 0; p < x; p++)
        {
            tablica->tablica[i][p] = i*p; 
        } 
    }

    tablica->sizeX = x;
    tablica->sizeY = y;
}

void PrintTable(struct Tablica tablica)
{
    printf("Tablica Zawartosc\n");

    for (size_t y = 0; y < tablica.sizeY; y++)
    {
        for (size_t x = 0; x < tablica.sizeX; x++)
        {
            printf("    %d" ,tablica.tablica[y][x]);
        }
        printf("\n");
    }
    
}