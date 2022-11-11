#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#define DEBUG

#define PHOTO_MAX_SIZE_W 400
#define PHOTO_MAX_SIZE_H 400
#define PATH_SIZE 256
#define MENU_SIZE 9
#define MAX_LINE_LENGTH 70

#define PHOTO_FILE_BUFF 1000

// struktura przetrzymująca informacje o zdjęciu
struct Photo
{
    int pixels[PHOTO_MAX_SIZE_H][PHOTO_MAX_SIZE_W];
    unsigned int sizeX;
    unsigned int sizeY;
    int loaded;
    int maxWhiteValue;
};


struct Menu
{
    char *string;
};


// ----------------- przygotowawcze

int DisplayMenu();

//----------------- Funkcje Oeracji na zdjęciach
int Inverse(struct Photo *);
int CleanPhoto(struct Photo *photo, int defaultValue);
int FindEdgeValues(int *min, int *max, struct Photo photo);
int EdgingPhoto(struct Photo *photoIn, int edge);
int FixPhotoToUseFullSlcaeValues(struct Photo *photoIn);

int DisplayPhoto(char pathOut[PATH_SIZE]);
int LoadPhoto(struct Photo *photo, char path[PATH_SIZE]);
int SavePhoto(struct Photo *photo, char path[PATH_SIZE]);
int read(FILE *plik_we, struct Photo *photo);
int save(FILE *plik_we, struct Photo *photo);


int main()
{
    struct Photo photo = {photo.loaded=0};
    int errors=1;
    char pathIn[PATH_SIZE];
    char pathOut[PATH_SIZE];
    
    while (1)
    {
        int option = DisplayMenu();
        switch (option)
        {
        case 1:
            LoadPhoto(&photo,pathIn);  
            break;
        case 2:
            SavePhoto(&photo,pathOut);
            break;
        case 3:
            errors =Inverse(&photo);
            break;
        case 4:
            int edge;
            printf("\nType edge value\n");
            scanf("%i",&edge);
            errors = EdgingPhoto(&photo,edge);
            break;
        case 5:
            errors = FixPhotoToUseFullSlcaeValues(&photo);
        break;

        case 6:
            printf("\nSelect image:");
            scanf("%s",pathIn);
        break;
        case 7:
            printf("\nSelect image:");
            scanf("%s",pathOut);
        break;
        case 8:
            if(SavePhoto(&photo, pathOut))
                DisplayPhoto(pathOut);
        break;
        case 9:
            printf("\nExiting program...\n");
            return;
        break;
        default:
            printf("\nZła obcja\n");
            break;
        }

        if (errors == 0){  //1
            printf("\nPhoto not loaded!\n");
            errors =1;
        }
        
    }
}

int DisplayMenu()
{

    struct Menu menu[MENU_SIZE] =
    {   
        {"1 - LoadPhoto"},
        {"2 - SavePhoto"},
        {"3 - Inverse"},
        {"4 - Edging"},
        {"5 - FixScale"},
        {"6 - Select input image"},
        {"7 - Select output image"},
        {"8 - Show and Save"},
        {"9 - Close"},
    };

    printf("\n--------------------[MENU]-----------------------\n");

    for (size_t i = 0; i < MENU_SIZE; i++)
    {
        printf("%s\n",menu[i].string);
    }

    int opcja=0;
    printf("Wybierz opcję: ");
    scanf("%i", &opcja);

    if(opcja <= MENU_SIZE && opcja >0)
    {

        printf("\nwybrałęś: %s \n", menu[--opcja].string);
        return ++opcja;
    }
    else
        return -1;
        
}

//--------------------------------------------------------------------

int CleanPhoto(struct Photo *photo, int defaultValue)   //CZYŚCI ZAWARTOŚC PIXELI W ZDJĘCIU
{
    if(photo->loaded!=0){
        for (size_t y = 0; y < PHOTO_MAX_SIZE_H; y++)
            for (size_t x = 0; x < PHOTO_MAX_SIZE_W; x++) photo->pixels[y][x] = defaultValue;    
        return 1;
    }
    else
        return 0;
}

int Inverse(struct Photo *photoIn)  // ODWRACA WARTOŚCI PIKSELI  
{
    if(photoIn->loaded!=0){
        for (size_t y = 0; y < photoIn->sizeY; y++)
            for (size_t x = 0; x < photoIn->sizeX; x++)
                photoIn->pixels[y][x] = photoIn->maxWhiteValue - photoIn->pixels[y][x];  // przechodzi przez każdy pixel i odwraca wartości 
        return 1;
    }
    else
        return 0;
}

int FixPhotoToUseFullSlcaeValues(struct Photo *photoIn) // Rozciąganie histogramu
{
    if(photoIn->loaded!=0){
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
        return 1;
    }
    else
        return 0;
}

int EdgingPhoto(struct Photo *photoIn, int edge) // Rozciąganie histogramu
{
    if(photoIn->loaded!=0){
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
        return 1;
    }
    else 
        return 0;
}

int FindEdgeValues(int *min, int *max, struct Photo photo)  // funkcja wyszukuje wartości najmniejsze i największą
{   
    if(photo.loaded!=0){
    
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
        return 1;
    }
    else
        return 0;
}

int DisplayPhoto(char pathIn[PATH_SIZE])
{
  char command[PHOTO_FILE_BUFF];
  strcpy(command,"ristretto ");  /* konstrukcja polecenia postaci */
  strcat(command,pathIn);     /* display "nazwa_pliku" &       */
  printf("%s\n",command);      /* wydruk kontrolny polecenia */
  system(command);    

}

int LoadPhoto(struct Photo *photo, char path[PATH_SIZE])
{   
  FILE *plik;

  int odczytano=0;
  plik=fopen(path,"r");

  if (plik != NULL) {  //odczytuje zdjęcie  i wpisuje je 
    odczytano = read(plik,photo);
    fclose(plik);
  }
  else  
    printf("Error: Specify the input file first.\n");

  if(odczytano != 0){
    photo->loaded=1;
    printf("Loaded\n");
    return 1;
  }
  else
    return 0;
}

int SavePhoto(struct Photo *photo, char path[PATH_SIZE])
{
    FILE *plik;

    int saved=0;
    plik = fopen(path,"w");

  if (plik != NULL) {  //otwiera plik w którym bedzie sapisany 
    saved = save(plik,photo);
    fclose(plik);
  }
  else  
    printf("Specify the output file first.\n");

  if(saved != 0)
    return 1;
  else
    return 0;

}

int save(FILE *plik_we,struct Photo *photo) {

  /*Sprawdzenie czy podano prawid�owy uchwyt pliku */
  if (plik_we==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }

  fprintf(plik_we,"P2\n");
  fprintf(plik_we,"%i %i\n",photo->sizeX,photo->sizeY);
  fprintf(plik_we,"%i\n",photo->maxWhiteValue);
    
  int maxLineSizeCounter = 0;

  for (size_t y = 0; y < photo->sizeY; y++)
  {
    for (size_t x = 0; x < photo->sizeX; x++)
    {
        if(maxLineSizeCounter > MAX_LINE_LENGTH){
            maxLineSizeCounter =0;
            fprintf(plik_we,"\n");
        }
        fprintf(plik_we,"%i ",photo->pixels[y][x]);
        maxLineSizeCounter++;
    }
    fprintf(plik_we,"\n");
  }
  


}

int read(FILE *plik_we,struct Photo *photo) {
    
    //int obraz_pgm[][PHOTO_MAX_SIZE_W],int *wymx,int *wymy, int *szarosci

  char buf[PHOTO_FILE_BUFF];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int i,j;

  /*Sprawdzenie czy podano prawid�owy uchwyt pliku */
  if (plik_we==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }

  /* Sprawdzenie "numeru magicznego" - powinien by� P2 */
  if (fgets(buf,PHOTO_FILE_BUFF,plik_we)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    koniec=1;                              /* Nie udalo sie? Koniec danych! */

  if ( (buf[0]!='P') || (buf[1]!='2') || koniec) {  /* Czy jest magiczne "P2"? */
    fprintf(stderr,"Blad: To nie jest plik PGM\n");
    return(0);
  }

  /* Pominiecie komentarzy */
  do {
    if ((znak=fgetc(plik_we))=='#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf,PHOTO_FILE_BUFF,plik_we)==NULL)  /* Przeczytaj ja do bufora                */
	koniec=1;                   /* Zapamietaj ewentualny koniec danych */
    }  else {
      ungetc(znak,plik_we);                   /* Gdy przeczytany znak z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (znak=='#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(plik_we,"%d %d %d", &photo->sizeX, &photo->sizeY, &photo->maxWhiteValue)!=3) {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(0);
  }
  /* Pobranie obrazu i zapisanie w tablicy pixels*/
  for (i=0;i<photo->sizeY;i++) {
    for (j=0;j<photo->sizeX;j++) {
      if (fscanf(plik_we,"%d",&(photo->pixels[i][j]))!=1) {
	fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
	return(0);
      }
    }
  }
  return photo->sizeX*photo->sizeY;   /* Czytanie zakonczone sukcesem    */
}                   