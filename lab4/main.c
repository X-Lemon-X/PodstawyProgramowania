#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define TABLE_SIZE_X 10
#define TABLE_SIZE_Y 10

#define PHOTO_MAX_SIZE_W 400
#define PHOTO_MAX_SIZE_H 400

#define PHOTO_FILE_BUFF 10000

struct Tablica
{
    int tablica[TABLE_SIZE_X][TABLE_SIZE_Y];
    int sizeX;
    int sizeY;
};

// struktura przetrzymująca informacje o zdjęciu
struct Photo
{
    int pixels[PHOTO_MAX_SIZE_H][PHOTO_MAX_SIZE_W];
    unsigned int sizeX;
    unsigned int sizeY;
    char *type;
    int maxWhiteValue;
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

//----------------- Funkcje Oeracji na zdjęciach
int Inverse(struct Photo *);
void CleanPhoto(struct Photo *photo, int defaultValue);
void CopyPhoto(struct Photo photoIn, struct Photo *photoDes);
void FindEdgeValues(int *min, int *max, struct Photo photo);
void EdgingPhoto(struct Photo *photoIn, int edge);
void FixPhotoToUseFullSlcaeValues(struct Photo *photoIn);
int LoadPhoto(struct Photo *photo, char *path);


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

//--------------------------------------------------------------------

void CleanPhoto(struct Photo *photo, int defaultValue)   //CZYŚCI ZAWARTOŚC PIXELI W ZDJĘCIU
{
 for (size_t y = 0; y < TABLE_SIZE_Y; y++)
        for (size_t x = 0; x < TABLE_SIZE_X; x++) photo->pixels[y][x] = defaultValue;    
}

int Inverse(struct Photo *photoIn)  // ODWRACA WARTOŚCI PIKSELI  
{
    for (size_t y = 0; y < photoIn->sizeY; y++)
        for (size_t x = 0; x < photoIn->sizeX; x++)
        {
            photoIn->pixels[y][x] = photoIn->maxWhiteValue - photoIn->pixels[y][x];  // przechodzi przez każdy pixel i odwraca wartości 
        }

    return 1;
}

void CopyPhoto(struct Photo photoIn, struct Photo *photoDes) //kopiuje dane zdjęcia do buffora do edycji 
{
    memcpy(photoDes, &photoIn, sizeof(photoIn));
}

void FixPhotoToUseFullSlcaeValues(struct Photo *photoIn) // Rozciąganie histogramu
{
    int max, min;
    FindEdgeValues(&min, &max, *photoIn);  //wyszukuje najmniejszą i największa wartość

    for (size_t y = 0; y < photoIn->sizeY; y++)
    {
        for (size_t x = 0; x < photoIn->sizeX; x++)
        {
            /*rozciąga gamę pikseli do maksymalnych i minimalnych wartości*/
            photoIn->pixels[y][x] = (photoIn->pixels[y][x] - min)* photoIn->maxWhiteValue / (max - min);   
        }
    }
}

void EdgingPhoto(struct Photo *photoIn, int edge) // Rozciąganie histogramu
{
    /*
    ustawia wartości min dla pixeli mneijszych od progu
    ustawia wartości max dla pixeli większych od progu
    */

    for (size_t y = 0; y < photoIn->sizeY; y++)
    {
        for (size_t x = 0; x < photoIn->sizeX; x++)
        {
            if (photoIn->pixels[y][x] <= edge)
            {
                photoIn->pixels[y][x] = 0;
            }
            else    
                photoIn->pixels[y][x] = photoIn->maxWhiteValue;   
        }        
    }
}

void FindEdgeValues(int *min, int *max, struct Photo photo)  // funkcja wyszukuje wartości najmniejsze i największą
{   
    *min = photo.pixels[0][0];
    *max = photo.pixels[0][0];

    for (size_t y = 0; y < photo.sizeY; y++)
    {
        for (size_t x = 0; x < photo.sizeX; x++)
        {
            if(photo.pixels[y][x] < *min) *min = photo.pixels[y][x]; 
            if (photo.pixels[y][x] > *max) *max = photo.pixels[y][x]; 
        }
    }
}

int LoadPhoto(struct Photo *photo, char *path)
{
    if(FILE *)

}