#include <stdio.h>

// odkomentować odpowiednie opcej przed kompilacją programu

//------program tętno------------ 
#define TESTING_TETNO
//#define NORMAL_TETNO
#define FILEPATH "C:/Users/patdu/Desktop/IT/pwr/PodstawyProgramowania/laby3/dane1.txt"


//---------inne programy---------
//#define WYPISYWANIE_TABELKI       //program do wypisywani tebelki
//#define TEMPERATURA               //program z wyświtlanie komentarzów do zadanej temperatury
//#define WYPISYWANIE_NUMEROW       //program do zapamiętyeani liczby




#ifdef WYPISYWANIE_TABELKI
void WypisanieTabelki(int start, int end, int x, int y);
#define INNE
#endif

#ifdef TEMPERATURA
void Temperatura();
#define INNE
#endif

#ifdef WYPISYWANIE_NUMEROW
void wpisywanieNumerow();
#define INNE
#endif


#ifdef TESTING_TETNO
#define TETNO_
#endif

#ifdef NORMAL_TETNO
#define TETNO_
#endif



#ifdef TETNO_
void Tetno();
int DecodingValues(char string[],size_t size, float *value, char spliter);
int CkeckCharForNumber(char value,char *ret);
#endif


int main()
{
    printf("\nStart\n");

    #ifdef TEMPERATURA
    Temperatura();
    #endif

    #ifdef WYPISYWANIE_TABELKI
    WypisanieTabelki(1,99,10,10);
    #endif
    
    #ifdef WYPISYWANIE_NUMEROW
    wpisywanieNumerow();
    #endif

    #ifdef TETNO_
    Tetno();
    #endif

    printf("\nEnd\n");

    return 1;
}

#ifdef INNE
void WypisanieTabelki(int start, int end,int x, int y)
{
    long number = ++start;

    for (size_t i = 0; i < x; i++)
    {
        for (size_t a = 0; a < y; a++)
        {
            long num = ++number;
            
            if(num > end) 
            {
                printf("\n");        
                return;
            }
            
            if(num < 10)
            {
                printf(" %ld   ", num);
            }
            else
            {
                printf("%ld   ", num);
            }
            
        }
        printf("\n");
    }
    
}

void Temperatura()
{
    int temp=0;
    printf("\nPodaj temperaturę ->:");
    scanf("%i",&temp);

    if (temp<0)
    {
        printf("jedziemy na narty.");
    }
    else if (temp==0)
    {
        printf("wpoda zaczyna zamarcać");
    }
    else if (temp > 20)
    {
        printf("ciepło");
    }
    else if (temp > 15)
    {
        printf("chłodno");
    }
    else if (temp > 10)
    {
        printf("zimno");
    }
    else // od [10-0)
    {
        printf("bardzo zimno");
    }
    
}

void wpisywanieNumerow()
{
    int input =0;
    int count=0;
    int mem=0;
    
    for (;;)
    {
        printf("pruba %i: Podaj wartość->",count);
        scanf("%i", &input);

        if (input >= -5 && input <= 5 )
        {
            mem = input;
            printf("liczba ustawiona na: %i \n", input);
        }
        else if (input == 99)
        {
            return;
        }
        else
        {
            printf("Błędna wartość parametru\n");
        }

        count++;
    }
    
}

#endif

void Tetno()
{
	char line[30];

	FILE *file = fopen(FILEPATH , "r");   // wskazujemy plik z danymi najlepiej txt 

	if(file == NULL)                        //sparwdzamy czy taki plik możemy otworzyć oraz czy istnieje
    {           
        perror("Error: Problem z plikiem");   
        return; 
  	}

	int countZeros=0;
	int countLines=0;
	int value = 0;
	float valuef = 0;
    int valuePrev=0;
    int warunekkońca=0;

	while(fgets(line, sizeof(line), file) != NULL)  //czyta plik linia po lini w pętli dopuki plik sie nie skończy 
	{
	    if(DecodingValues(line,30, &valuef, ' ') > 0)   // konwertuje przeczytaną linie z textem  na liczbę i sprawdza czy udało się ją zinterpretować 
        {
            countLines++;          //zlicza ilość przeczytanych wartośći
            value = (int)valuef;

            if (value < 10 && value > -10)    //filtruje wartości nie zawierające się w zadanym zakiresie
            {

                if( (value * valuePrev) < 0) countZeros++;  // sprawdza warunek przejścia przez zero jeśli mają dwa rużne znaki zlicza przejścia

                if(value != 0) valuePrev = value; //aby ignorował zera podczas zliczania przejść

            }
            else if (value ==99) // warunek końca pliku koniec programu
            {
                printf("End of the file\n");
                warunekkońca=1;
            }            
        }

        #ifdef TESTING_TETNO  //dla testów wypisuje watrtości przeczytane z każdej lini
            printf("Przeczytana wartość to (float): %f     (int): %d,    lpl: %d -> linia:%s", valuef, value, countLines, line);
        #endif

        if(countLines == 99)  // co 99 lini powina zosatć obliczone tetno okre t=10s
        {
            float puls = (float)countZeros * 6;  // puls wyświelany w pulsach na minute


            #ifdef TESTING_TETNO
                //printf("------------ 99 lini minelo ------------\n");
                if(puls < 80 && puls > 50) printf("Puls hb %f\n",puls); //sprawdza czy wynik pulsu znjduje się w odpowiednim zakresie 
                else printf("Puls: %f poza zakresem\n",puls);    //wywitla informacje o pulsie zpoza zakresu
                printf("Zeros count: %i\n", countZeros);
            #endif
            

            #ifdef NORMAL_TETNO
            //sprawdza czy wynik pulsu jest poza zakresem
            //wywitla informacje o pulsie zpoza zakresu

            if(puls > 80 || puls < 50) printf("Puls: %d poza zakresem\n", (int)puls);    
            
            #endif
            
            countZeros=0;       // resetuje licznik przejśc przez zera i przeczytanych lini dla nowej kolumny z informacjami 
            countLines=0;
        }

        for (size_t i = 0; i < sizeof(line); i++)
        {
            line[i]= '\000';  //czyści buffor dla następnej lini
        }
        
        if (warunekkońca==1)
        {
            return;
        }
        
	}

}

int CkeckCharForNumber(char value, char *ret)
{   
    if(value == ',' || value == '.' || value == '-' ||( (int)value >= (int)'0' && (int)value <= (int)'9'))  //sprawdza czy znaki w pliki txt mogą być liczbą lub jej częścią
    {
        *ret = value; 
            return 1;
    }
    else
        return -1;
}

int DecodingValues(char string[], size_t size ,float *value, char spliter)
{
    float val;
    char buffor[size];
    size_t a=0;

    for (size_t i = 0; i < size; i++)
    {
        buffor[i]='\000';    //czyści buffor do którego zostanie wpisana liczby
    }
    

    for (size_t i = 0; i < size; i++)       //szuka elementu ' ' który jest znakiem symboliczny oznaczającym rozpoczęcie liczby 
    {          
        if(string[i] == ' ')      // sprwdza czy 
        {
            i++;    //pomijamy sprawdzanie elementu ' '

            for (; i < size; i++)   //dla każdego elementu po znaku ' ' sprawdza które są liczbami i wpisuje znak(z częscią liczby) do buffora 
            {   
                //sprawdza czy znaki w pliki txt mogą być liczbą lub jej częścią
                if(1 == CkeckCharForNumber(string[i],&buffor[a])) a++; 
            }
            break;
        }
    }

    if(a == 0) return -1;  //jeśli program nie szycztał żadaenj liczby to zwraca błąd dekodowania lini

    sscanf(buffor,"%f",&val);  //konwertuje string na float 
    *value = val;   //zwraca wartość zczytaną

    return 1;      //zwraca wartosc pozytywnego dekodowania lini
}



