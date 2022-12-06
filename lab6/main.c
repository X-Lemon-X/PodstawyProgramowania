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


#ifndef DEBUG
int fun()
{
  Image img;
  LoadImage(&img, "kostka.png",NULL);
  SaveImage_as_png(img);

  char *buf1 = (char*)malloc(20);
  char *buf = (char*)malloc(sizeof(buf1));

  printf("->  %i\n", sizeof(buf1));
  printf("->  %i\n", sizeof(buf));


}

int main()
{
  Image Img;

  int z,y;
  z=5;
  y=6;
  int (*tab)[z];
  
  
  tab = (int(*)[z])malloc(y * z * sizeof(int));
  tab[1][2]=3;
  tab[1][1]=2;
  printf("kon %i\n", tab[1][1]);
  printf("kon %i\n", tab[1][2]);

  fun();

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
