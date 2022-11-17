#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//#define DEBUG

#define PHOTO_MAX_SIZE_W 400
#define PHOTO_MAX_SIZE_H 400
#define PATH_SIZE 256
#define MENU_SIZE 9
#define MAX_LINE_LENGTH 70
#define PHOTO_FILE_BUFF 1000
#define DATEBUFFOR 50

#ifdef DEBUG
  #define PATH_IN "C:/Users/patdu/Desktop/IT/pwr/PodstawyProgramowania/lab4/kubus.pgm"
  #define PATH_OUT "C:/Users/patdu/Desktop/IT/pwr/PodstawyProgramowania/lab4/kubus2.pgm"
#endif

// struktura przetrzymująca informacje o zdjęciu
struct Photo
{
    int pixels[PHOTO_MAX_SIZE_H][PHOTO_MAX_SIZE_W];
    char comment[PHOTO_FILE_BUFF];
    unsigned int sizeW;
    unsigned int sizeH;
    int loaded;
    int maxWhiteValue;
};

struct Menu
{
    char *string;
};


int Inverse(struct Photo *);
int FindEdgeValues(int *min, int *max, struct Photo photo);
int EdgingPhoto(struct Photo *photoIn, int edge);
int FixPhotoToUseFullScaleValues(struct Photo *photoIn);
int Konturowanie(struct Photo *photoIn);
void AddComment(struct Photo *photo, char *comment);
void GetDate(char *dateOut);

int DisplayMenu();
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

#ifdef DEBUG
    LoadPhoto(&photo,);
    Inverse(&photo);
    EdgingPhoto(&photo, 200);
    FixPhotoToUseFullScaleValues(&photo);
    SavePhoto(&photo,"C:/Users/patdu/Desktop/IT/pwr/PodstawyProgramowania/lab4/kubus2.pgm");
#else

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
            errors = FixPhotoToUseFullScaleValues(&photo);
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
#endif
}

/*
funkcja wyświetlajca menu (użycie strukrury do trzymania opcji moz e nie jets najlepszym pomysłem ale chciałem to przetestować)
zczytuje opcje od urzytkownika i wyświetla wybrną opcje 
*/
int DisplayMenu()
{
  struct Menu menu[MENU_SIZE] ={   
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
    printf("%s\n",menu[i].string);
  
  int opcja=0;
  printf("Wybierz opcję: ");
  scanf("%i", &opcja);

  if(opcja <= MENU_SIZE && opcja >0){
      printf("\nwybrałęś: %s \n", menu[--opcja].string);
      return ++opcja;
  }
  else
      return -1;
        
}

//--------------------------------------------------------------------

/*
ODWRACA WARTOŚCI PIKSELI  
przechodzi przez każdy pixel aktualnie załadowany
i odwraca względem maksymalnej ich warości 
*/ 
int Inverse(struct Photo *photoIn)  
{
    if(photoIn->loaded!=0){
      AddComment(photoIn, "Inverse");
      for (size_t y = 0; y < photoIn->sizeH; y++)
          for (size_t x = 0; x < photoIn->sizeW; x++)
              photoIn->pixels[y][x] = photoIn->maxWhiteValue - photoIn->pixels[y][x];  
      return 1;         
    }
    else
        return 0;
}

/*
Rozciąganie histogramu
przechodzi przez każdy pixel aktualnie załadowany
i przeskalowuje wartości za pomocą funkcji aby obraz 
mógł użyć wszystkich wartosci
*/ 
int FixPhotoToUseFullScaleValues(struct Photo *photoIn) // 
{
    if(photoIn->loaded!=0){
        int max, min;
        FindEdgeValues(&min, &max, *photoIn);
        AddComment(photoIn, "FixPhotoToUseFullScaleValues");
        for (size_t y = 0; y < photoIn->sizeH; y++)
            for (size_t x = 0; x < photoIn->sizeW; x++)
                photoIn->pixels[y][x] = (photoIn->pixels[y][x] - min)* photoIn->maxWhiteValue / (max - min);        
        return 1;
    }
    else
        return 0;
}

/*
ustawia wartości min dla pixeli mneijszych od progu
ustawia wartości max dla pixeli większych od progu
*/
int EdgingPhoto(struct Photo *photoIn, int edge)
{
    if(photoIn->loaded!=0){
      AddComment(photoIn, "Edging Photo");
      for (size_t y = 0; y < photoIn->sizeH; y++)
          for (size_t x = 0; x < photoIn->sizeW; x++){
              if (photoIn->pixels[y][x] <= edge)
                  photoIn->pixels[y][x] = 0;
              else    
                  photoIn->pixels[y][x] = photoIn->maxWhiteValue;   
          }        
      return 1;
    }
    else 
        return 0;
}

//wyszukuje wartości najmniejsze i największą
int FindEdgeValues(int *min, int *max, struct Photo photo)  
{   
    if(photo.loaded!=0){
        *min = photo.pixels[0][0];
        *max = photo.pixels[0][0];
        for (size_t y = 0; y < photo.sizeH; y++)
            for (size_t x = 0; x < photo.sizeW; x++){
                if(photo.pixels[y][x] < *min) *min = photo.pixels[y][x]; 
                if (photo.pixels[y][x] > *max) *max = photo.pixels[y][x]; 
            }
        return 1;
    }
    else
        return 0;
}

//funkcja wyświetlająca obraz za pomocą programu ristrettro
int DisplayPhoto(char pathIn[PATH_SIZE])
{
  char command[PHOTO_FILE_BUFF];
  strcpy(command,"ristretto ");
  strcat(command,pathIn);
  printf("%s\n",command);
  system(command);

}

//funkcja ładuje zdjęcie do pamięci 
int LoadPhoto(struct Photo *photo, char path[PATH_SIZE])
{   
  FILE *plik;

  int odczytano=0;
  plik=fopen(path,"r");

  if (plik != NULL) { 
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

// funkcja zapisuje zdjecie
int SavePhoto(struct Photo *photo, char path[PATH_SIZE])
{
    FILE *plik;

    int saved=0;
    plik = fopen(path,"w");

  if (plik != NULL) {  //otwiera plik w którym bedzie zapisany 
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

/*
funckja dodająca komnetaz do pliku z data jego dodania
*/
void AddComment(struct Photo *photo, char *comment)
{
    char buff[DATEBUFFOR];
    for (size_t i = 0; i < DATEBUFFOR; i++) buff[i]=0;
    
    strcat(photo->comment,"# ");
    strcat(photo->comment,comment);
    strcat(photo->comment," -> ");
    GetDate(buff);
    strcat(photo->comment,buff);
}

/*
Funkcja pobiera aktualny czas i zwraca go
*/
void GetDate(char *dateOut)
{
  struct tm* local;
  time_t t = time(NULL);
  local = localtime(&t); 
  strcat(dateOut,asctime(local));
}


/*
funkcja wpisuje ustawienia w pliku zdjecia,
następnie wpisuje do niego wartosci pixeli
*/
int save(FILE *plik_we,struct Photo *photo) {

  /*Sprawdzenie czy podano prawid�owy uchwyt pliku */
  if (plik_we==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }

  fprintf(plik_we,"P2\n");
  fprintf(plik_we,photo->comment);
  fprintf(plik_we,"%i %i\n",photo->sizeW,photo->sizeH);
  fprintf(plik_we,"%i\n",photo->maxWhiteValue);
  int maxLineSizeCounter = 0;

  for (size_t y = 0; y < photo->sizeH; y++){
    for (size_t x = 0; x < photo->sizeW; x++){
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


//zmodyfikowana funckja odczytu z programu odczyt.c która wpisuje wartości pizeli do struktury ze zdjeciem
// oraz komentarze 
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
	      koniec=1;                                   /* Zapamietaj ewentualny koniec danych */
      strcat(photo->comment,"#");
      strcat(photo->comment,buf);                
    }  else {
      ungetc(znak,plik_we);                   /* Gdy przeczytany znak z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (znak=='#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */
  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(plik_we,"%d %d %d", &photo->sizeW, &photo->sizeH, &photo->maxWhiteValue)!=3) {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(0);
  }
  /* Pobranie obrazu i zapisanie w tablicy pixels*/
  for (i=0;i<photo->sizeH;i++) {
    for (j=0;j<photo->sizeW;j++) {
      if (fscanf(plik_we,"%d",&(photo->pixels[i][j]))!=1) {
	fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
	return(0);
      }
    }
  }
  return photo->sizeW*photo->sizeH;   /* Czytanie zakonczone sukcesem    */
}                   