#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ImageEditorPlus.h"

#define W_OK 0                   /* wartosc oznaczajaca brak bledow */
#define B_NIEPOPRAWNAOPCJA -1    /* kody bledow rozpoznawania opcji */
#define B_BRAKNAZWY   -2
#define B_BRAKWARTOSCI  -3
#define B_BRAKPLIKU   -4
#define B_FILETYPE -5


#define SETCOLOR_IMAGETYPE_JPG IMAGE_TYPE_JPG
#define SETCOLOR_IMAGETYPE_PNG IMAGE_TYPE_PNG
#define SETCOLOR_IMAGETYPE_PPM IMAGE_TYPE_PPM

/* strukura do zapamietywania opcji podanych w wywolaniu programu */
typedef struct {
  FILE *plik_we;
  char  *plik_wy;        /* uchwyty do pliku wej. i wyj. */
  int negatyw,progowanie,grayScale,useFullScale,wyswietlenie, typPlikuWyj;      /* opcje */
  int w_progu;              /* wartosc progu dla opcji progowanie */ 
} t_opcje;

void GetDate(char *dateOut);
void wyzeruj_opcje(t_opcje * wybor);
int DisplayPhoto(char *pathOut);
int przetwarzaj_opcje(int argc, char **argv, t_opcje *wybor);
void PrintError(int errorCode);
void PrintErrorOpcje(int errorCode);

//gcc main.c ImageEditorPlus.c -o result -lm
int main(int argc, char **argv)
{
  t_opcje opcje;
  PrintErrorOpcje(przetwarzaj_opcje(argc,argv,&opcje));

  Image image;
  PrintError(LoadImage(&image,opcje.plik_we,opcje.plik_wy,opcje.typPlikuWyj));
  
  if(opcje.negatyw)
    PrintError(Inverse(&image));
  
  if(opcje.progowanie)
    PrintError(EdgingPhoto(&image,(unsigned char)opcje.w_progu,(unsigned char)opcje.w_progu,(unsigned char)opcje.w_progu));

  if(opcje.useFullScale)
    PrintError(UseFullScale(&image));

  if(opcje.grayScale)
    PrintError(GrayScale(&image));

  PrintError(SaveImage(&image));

  if(opcje.wyswietlenie)
    DisplayPhoto(image.outPath);

}

void PrintError(int errorCode)
{
  switch (errorCode)
  {
  case IMAGENOTLOADED:
    printf("IMAGENOTLOADED\n");
    exit(IMAGENOTLOADED);
    return;
  case FILEEXTENSIONNOTSUPPORTED:
    printf("FILEEXTENSIONNOTSUPPORTED\n");
    exit(FILEEXTENSIONNOTSUPPORTED);
    return;
  case NOINPUTFILE:
    printf("NOINPUTFILE\n");
    exit(NOINPUTFILE);
    return;
  case ERROR_IMAGETYPE:
    printf("ERROR_IMAGETYPE\n");
    exit(ERROR_IMAGETYPE);
    return;
  case ERROR_IMAGE_DIDNT_SAVE:
    printf("ERROR_IMAGE_DIDNT_SAVE\n");
    return;
  case OK:
    return;
  default:
    printf("ERROR");
    exit(200);
    return;
  }
}

void PrintErrorOpcje(int errorCode)
{
  switch (errorCode)
  {
  case B_NIEPOPRAWNAOPCJA:
    printf("B_NIEPOPRAWNAOPCJA\n");
    break;
  case B_BRAKNAZWY:
    printf("B_BRAKNAZWY\n");
    break;
  case B_BRAKWARTOSCI:
    printf("B_BRAKWARTOSCI\n");
        break;
  case B_BRAKPLIKU:
    printf("B_BRAKPLIKU\n");
        break;
  case B_FILETYPE:
    printf("B_FILETYPE\n");
    break;
  case W_OK:
    return;
  default:
    printf("ERROR");
        break;
  }

  exit(errorCode);
}

#pragma region 
/************************************************************************/
/* Funkcja rozpoznaje opcje wywolania programu zapisane w tablicy argv                                   */
/* i zapisuje je w strukturze wybor                                                                      */
/* Skladnia opcji wywolania programu                                                                     */
/*         program {[-i nazwa] [-o nazwa] [-p liczba] [-n] [-k] [-g] [-d] [-s typ_zdjęcia_wyjściowego]}  */
/*         typ_zdjęcia_wyjściowego - p dla png  j dal jpg  m dla ppm                                               */
/* Argumenty funkcji:                                                                                    */
/*         argc  -  liczba argumentow wywolania wraz z nazwa programu                                    */
/*         argv  -  tablica argumentow wywolania                                                         */
/*         wybor -  struktura z informacjami o wywolanych opcjach                                        */
/* PRE:                                                                                                  */
/*      brak                                                                                             */
/* POST:                                                                                                 */
/*      funkcja otwiera odpowiednie pliki, zwraca uchwyty do nich                                        */
/*      w strukturze wybór, do tego ustawia na 1 pola dla opcji, ktore                                   */
/*	poprawnie wystapily w linii wywolania programu,                                                      */          
/*	pola opcji nie wystepujacych w wywolaniu ustawione sa na 0;                                          */          
/*	zwraca wartosc W_OK (0), gdy wywolanie bylo poprawne                                                 */          
/*	lub kod bledu zdefiniowany stalymi B_* (<0)                                                          */          
/* UWAGA:                                                                                                */
/*      funkcja nie sprawdza istnienia i praw dostepu do plikow                                          */
/*      w takich przypadkach zwracane uchwyty maja wartosc NULL                                          */
/************************************************************************/
#pragma endregion

int przetwarzaj_opcje(int argc, char **argv, t_opcje *wybor) {
  int i, prog;
  char kolor='\0';

  wyzeruj_opcje(wybor);
  wybor->plik_wy=NULL;

  for (i=1; i<argc; i++) {
    if (argv[i][0] != '-')  /* blad: to nie jest opcja - brak znaku "-" */
      return B_NIEPOPRAWNAOPCJA; 
    switch (argv[i][1]) {
        case 'i': {                 /* opcja z nazwa pliku wejsciowego */
          if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
              wybor->plik_we=argv[i];
            } 
            else 
              return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
          break;
        }       
        case 'o': {                 /* opcja z nazwa pliku wyjsciowego */
          if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
            wybor->plik_wy=argv[i];
          } 
          else 
             return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
          break;
        }
        case 's': {                 /* opcja z nazwa pliku wyjsciowego */
          if (++i<argc) {   /* wczytujemy kolejny argument jako kolor */\
            kolor= argv[i][0];
            switch (argv[i][0])
            {
            case 'p':
              wybor->typPlikuWyj = SETCOLOR_IMAGETYPE_PNG;
            break;
            case 'j':
              wybor->typPlikuWyj = SETCOLOR_IMAGETYPE_JPG;
            break;
            case 'm':
              wybor->typPlikuWyj = SETCOLOR_IMAGETYPE_PPM;
            break;
            default:
                return B_FILETYPE;
              break;
            }
          } 
          else 
             return B_FILETYPE;                   /* blad: brak nazwy pliku */
          break;
        }
        case 'p': {                 /* mamy wykonac progowanie          */
          if (++i<argc) { /* wczytujemy kolejny argument jako wartosc progu */
            if (sscanf(argv[i],"%d",&prog)==1) {
              wybor->progowanie=1;
              wybor->w_progu=prog;
          } 
          else
            return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc progu */
          } 
          else 
            return B_BRAKWARTOSCI;             /* blad: brak wartosci progu */
        break;
        }
        case 'n': {                 /* mamy wykonac negatyw */
          wybor->negatyw=1;
          break;
        }
        case 'k': {                 /* mamy wykonac useFullScale */
          wybor->useFullScale=1;
          break;
        }
        case 'd': {                 /* mamy wyswietlic obraz */
          wybor->wyswietlenie=1;
          break;
        }
        case 'g':{                  /* mamy wykonac konwersje do szarość */
          wybor->grayScale=1;
          break;
        }
        default:                    /* nierozpoznana opcja */
          return B_NIEPOPRAWNAOPCJA;
    } /* koniec switch */
  } /* koniec for */

  if(kolor=='\0')
    return B_FILETYPE;

  if (wybor->plik_we!=NULL)     /* ok: wej. strumien danych zainicjowany */
    return W_OK;
  else 
    return B_BRAKPLIKU;         /* blad:  nie otwarto pliku wejsciowego  */
}

void wyzeruj_opcje(t_opcje * wybor) {
  wybor->plik_we=NULL;
  wybor->plik_wy=NULL;
  wybor->negatyw=0;
  wybor->useFullScale=0;
  wybor->progowanie=0;
  wybor->wyswietlenie=0;
  wybor->typPlikuWyj=0;
  wybor->grayScale=0;
}


//funkcja wyświetlająca obraz za pomocą programu ristrettro
int DisplayPhoto(char *pathIn)
{
  char command[1000];
  strcpy(command,"ristretto ");
  strcat(command,pathIn);
  printf("%s\n",command);
  system(command);

}

