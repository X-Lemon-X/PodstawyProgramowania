#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "ImageEditor.h"



#define PATH_SIZE 400
#define PHOTO_FILE_BUFF 1000

void LoadImage(struct Image *photo, int *pixelsInTheFoto, int sizeW, int sizeH, int maxWhileValue, char *comments)
{
    photo->pixels = pixelsInTheFoto;
    photo->sizeH = sizeH;
    photo->sizeW = sizeW;
    photo->maxWhiteValue = maxWhileValue;
}

int InverseImage(struct Image *photoIn)  
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
int FixImageToUseFullScaleValues(struct Image *photoIn) // 
{
    if(photoIn->loaded!=0){
        int max, min;
        FindEdgeValues(&min, &max, *photoIn);
        AddComment(photoIn, "FixPhotoToUseFullScaleValues");
        for (size_t y = 0; y < photoIn->sizeH; y++)
            for (size_t x = 0; x < photoIn->sizeW; x++)
              if((max - min)) photoIn->pixels[y][x] = (photoIn->pixels[y][x] - min)* photoIn->maxWhiteValue / (max - min);       
              else  photoIn->pixels[y][x] = 0;
        return 1;
    }
    else
        return 0;
}

/*
ustawia wartości min dla pixeli mneijszych od progu
ustawia wartości max dla pixeli większych od progu
*/
int EdgingImage(struct Image *photoIn, int edge)
{
    if(photoIn->loaded!=0){
      AddComment(photoIn, "Edging Image");
      edge = abs(edge);
      if(edge > photoIn->maxWhiteValue) edge = photoIn->maxWhiteValue;
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
int FindEdgeValuesImage(int *min, int *max, struct Image photo)  
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

/*
funckja dodająca komnetaz do pliku z data jego dodania
*/
void AddComment(struct Image *photo, char *comment)
{
    char buff[DATEBUFFOR];
    for (size_t i = 0; i < DATEBUFFOR; i++) buff[i]=0;
    
    strcat(photo->comment,"# ");
    strcat(photo->comment,comment);
    strcat(photo->comment," -> ");
    GetDate(buff);
    strcat(photo->comment,buff);
}


int LoadImage(struct Image *photo, char *path)
{   
  FILE *plik;
  int odczytano=0;
  plik=fopen(path,"r");

  if (plik != NULL) { 
    odczytano = read(plik,photo);
    fclose(plik);
  }
  else  
    return -2;

  if(odczytano != 0){
    photo->loaded=1;
    return 0;
  }
  else
    return -1;
}

// funkcja zapisuje zdjecie
int SaveImage(struct Image *photo, char *path)
{
  int saved=0;
  if(photo->loaded){
    FILE *plik;
    plik = fopen(path,"w");

  if (plik != NULL) {  //otwiera plik w którym bedzie zapisany 
    saved = save(plik,photo);
    fclose(plik);
  }
  else return -2;
  }

  if(saved != 0)return 0;
  else return -1;

}

/*
funckja dodająca komnetaz do pliku z data jego dodania
*/
void AddComment(struct Image *photo, char *comment)
{
    char *buff; 
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
int save(FILE *plik_we,struct Image *photo) {

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
int read(FILE *plik_we,struct Image *photo) {
    
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


