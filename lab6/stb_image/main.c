#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ImageEditorPlus.h"

#define W_OK 0                   /* wartosc oznaczajaca brak bledow */
#define B_NIEPOPRAWNAOPCJA -1    /* kody bledow rozpoznawania opcji */
#define B_BRAKNAZWY   -2
#define B_BRAKWARTOSCI  -3
#define B_BRAKPLIKU   -4
#define B_KOLORU -5


#define SETCOLOR_RED 1
#define SETCOLOR_GREEN 2
#define SETCOLOR_BLUE 3
#define SETCOLOR_GRAY 4


#define PATH_SIZE 256 
#define PHOTO_FILE_BUFF 400

/* strukura do zapamietywania opcji podanych w wywolaniu programu */
typedef struct {
  FILE *plik_we, *plik_wy;        /* uchwyty do pliku wej. i wyj. */
  int negatyw,progowanie,useFullScale,wyswietlenie, kolorWybur;      /* opcje */
  int w_progu;              /* wartosc progu dla opcji progowanie */ 
} t_opcje;

void GetDate(char *dateOut);
void wyzeruj_opcje(t_opcje * wybor);
int DisplayPhoto(char pathOut[PATH_SIZE]);
int przetwarzaj_opcje(int argc, char **argv, t_opcje *wybor);

//gcc main.c ImageEditorPlus.c -o result -lm
int main(int argc, char **argv)
{
  t_opcje opcje;
  Image image;
  char *pathIn = "/home/lemonx/IT/podstawyProgramowania/lab6/stb_image/ptasz.png";
  char *pathOut = "/home/lemonx/IT/podstawyProgramowania/lab6/stb_image/kostka2.png";
  int i =LoadImage(&image,pathIn,pathOut,IMAGE_TYPE_PNG);
  
  int error;
  switch(przetwarzaj_opcje(argc,argv,&opcje))
  {  default:
    printf("error");
    exit(1);
    break;
  }
}

/************************************************************************/
/* Funkcja rozpoznaje opcje wywolania programu zapisane w tablicy argv                              */
/* i zapisuje je w strukturze wybor                                                                 */
/* Skladnia opcji wywolania programu                                                                */
/*         program {[-i nazwa] [-o nazwa] [-p liczba] [-n] [-r] [-d] [-s typ_zdjęcia_wyjściowego]}  */
/*         typ_zdjęcia_wyjściowego - p dla png  j dal jpg                                           */
/* Argumenty funkcji:                                                                               */
/*         argc  -  liczba argumentow wywolania wraz z nazwa programu                               */
/*         argv  -  tablica argumentow wywolania                                                    */
/*         wybor -  struktura z informacjami o wywolanych opcjach                                   */
/* PRE:                                                                                             */
/*      brak                                                                                        */
/* POST:                                                                                            */
/*      funkcja otwiera odpowiednie pliki, zwraca uchwyty do nich                                   */
/*      w strukturze wybór, do tego ustawia na 1 pola dla opcji, ktore                              */
/*	poprawnie wystapily w linii wywolania programu,                                                 */          
/*	pola opcji nie wystepujacych w wywolaniu ustawione sa na 0;                                     */          
/*	zwraca wartosc W_OK (0), gdy wywolanie bylo poprawne                                            */          
/*	lub kod bledu zdefiniowany stalymi B_* (<0)                                                     */          
/* UWAGA:                                                                                           */
/*      funkcja nie sprawdza istnienia i praw dostepu do plikow                                     */
/*      w takich przypadkach zwracane uchwyty maja wartosc NULL                                     */
/************************************************************************/

int przetwarzaj_opcje(int argc, char **argv, t_opcje *wybor) {
  int i, prog;
  char kolor='\0';
  char *nazwa_pliku_we, *nazwa_pliku_wy;

  wyzeruj_opcje(wybor);
  wybor->plik_wy=stdout;        /* na wypadek gdy nie podano opcji "-o" */

  for (i=1; i<argc; i++) {
    if (argv[i][0] != '-')  /* blad: to nie jest opcja - brak znaku "-" */
      return B_NIEPOPRAWNAOPCJA; 
    switch (argv[i][1]) {
        case 'i': {                 /* opcja z nazwa pliku wejsciowego */
          if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
            nazwa_pliku_we=argv[i];
            if (strcmp(nazwa_pliku_we,"-")==0) /* gdy nazwa jest "-"        */
                  wybor->plik_we=stdin;            /* ustwiamy wejscie na stdin */
            else                               /* otwieramy wskazany plik   */
              wybor->plik_we=fopen(nazwa_pliku_we,"r");
          } 
          else 
            return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
          break;
        }
        case 'o': {                 /* opcja z nazwa pliku wyjsciowego */
          if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
            nazwa_pliku_wy=argv[i];
            if (strcmp(nazwa_pliku_wy,"-")==0)/* gdy nazwa jest "-"         */
              wybor->plik_wy=stdout;          /* ustwiamy wyjscie na stdout */
            else                              /* otwieramy wskazany plik    */
              wybor->plik_wy=fopen(nazwa_pliku_wy,"w");
          } 
          else 
             return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
          break;
        }
        case 'p': {
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
        case 's': {                 /* opcja z nazwa pliku wyjsciowego */
          if (++i<argc) {   /* wczytujemy kolejny argument jako kolor */
            kolor=argv[i][2];
            printf("--> typ: %c",kolor);
            switch (kolor == "r")
            {
            case 'p':
              wybor->kolorWybur = SETCOLOR_RED;
            break;
            case 'j':
              wybor->kolorWybur = SETCOLOR_GREEN;
            break;
            case 'b':
              wybor->kolorWybur = SETCOLOR_BLUE;
            break;
             case 's':
              wybor->kolorWybur = SETCOLOR_GRAY;
            break;
            default:
                return B_KOLORU;
              break;
            }
          } 
          else 
             return B_KOLORU;                   /* blad: brak nazwy pliku */
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
        default:                    /* nierozpoznana opcja */
          return B_NIEPOPRAWNAOPCJA;
    } /* koniec switch */
  } /* koniec for */

  if(kolor=='\0')
    return B_KOLORU;

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
  wybor->kolorWybur=0;
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

