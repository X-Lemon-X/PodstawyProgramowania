#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "ImageEditorPlus.h"
//#define DEBUG

#define PHOTO_MAX_SIZE_W 500
#define PHOTO_MAX_SIZE_H 500
#define PATH_SIZE 200
#define MENU_SIZE 9
#define MAX_LINE_LENGTH 70
#define PHOTO_FILE_BUFF 1000
#define DATEBUFFOR 50


void GetDate(char *dateOut);

int DisplayPhoto(char pathOut[PATH_SIZE]);
int LoadPhoto(struct Photo *photo, char path[PATH_SIZE]);
int SavePhoto(struct Photo *photo, char path[PATH_SIZE]);
int read(FILE *plik_we, struct Photo *photo);
int save(FILE *plik_we, struct Photo *photo);

struct Img{int data;};

#ifndef DEBUG
int fun(struct Img *img)
{
  img->data =1;
  printf("->  %i\n",img->data );
  printf("->  %lo\n", &img->data);

  *(&(img->data)) = 4;

  printf("->  %i\n", img->data);


}

int main()
{
  struct Img img;
  fun(&img);
}



#endif


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
