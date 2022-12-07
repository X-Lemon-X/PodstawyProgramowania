#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "ImageEditorPlus.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STBI_NO_STDIO

#define DEFAULT_IMAGE_OUTPUT_FILE_NAME_PNG "out.png"
#define DEFAULT_IMAGE_OUTPUT_FILE_NAME_JPG "out.jpg"
#define PIXELMAXVALUE 255

int main()
{
    Image img;
    char *pathIn = "/home/lemonx/IT/podstawyProgramowania/lab6/kostka.png";
    char *pathOut = "/home/lemonx/IT/podstawyProgramowania/lab6/kostaout.png";
    size_t sizeIN = 54;
    size_t sizeOut = 56;
    printf("--> %i",sizeIN);
    int ret = LoadImage(&img, pathIn, sizeIN, pathOut, sizeOut);
    printf("--> %i", ret);
    SaveImage_as_png(img);
    FreeMemory(&img);
}

/*
    sprawdza czy podana zotala ścieżka do pliku dla wyjścia i wejścia 
    funkcja ladujaca zdjęcie kożystając z funkcji biblioteki stbi_load 
    wiecej informacji nie bedę przepisywał są dostępne w stb_image.h linia 138
*/
int LoadImage(Image *image ,char *inPath, size_t sizeIn ,char *outPath, size_t sizeOut){
    
    if(inPath == NULL) return -3;
    if(outPath == NULL) image->outPath = NULL;
    else{
         image->outPath = (char*)calloc(sizeOut,sizeof(char));
         memcpy(image->outPath,outPath,sizeOut);
         image->sizeOut = sizeOut;
    }
    
    image->inPath = (char*)calloc(sizeIn,sizeof(char));
    memcpy(image->inPath,inPath,sizeIn);
    image->sizeIn = sizeIn;


    int x,y,n;
    if(!stbi_info(inPath, &x, &y, &n)) return -2;
    
    image->img = stbi_load(inPath, &image->width, &image->height, &image->channels, 0);
    if(image->img == NULL) return -1;
    
    image->imageSize = x * y * n;
    image->loaded=1;
    return 0;
}

void CopyArray(char **dest, char *source, size_t sizeSource)
{
    *dest = (char*)calloc(sizeSource,sizeof(char));
    memcpy(*dest,source, sizeSource);
}

/*
    Zapisuje zdjęcie jako png
*/
int SaveImage_as_png(Image image)
{
    char *path =image.outPath ;
    if(path == NULL) path=DEFAULT_IMAGE_OUTPUT_FILE_NAME_PNG;

    return stbi_write_png(path, image.width, image.height, image.channels, image.img, image.width * image.channels);    
}

/*
    Zapisuje zdjęcie jako jpg
*/
int SaveImage_as_jpg(Image image)
{
    char *path =image.outPath ;
    if(path == NULL) path=DEFAULT_IMAGE_OUTPUT_FILE_NAME_JPG;
    return stbi_write_jpg(path,image.width, image.height, image.channels, image.img, 100); 
}

/*
    zwalnia pamięć używaną przez obraz
*/
void FreeMemory(Image *image)
{
    free(image->img);
    free(image->inPath);
    free(image->outPath);
}

void Clear(Image *image)
{   
    FreeMemory(image);
    image->imageSize=0;
    image->height=0;
    image->width=0;
    image->channels=0;
    image->inPath=NULL;
    image->outPath=NULL;
    image->in=NULL;
    image->out=NULL;
}

int CheckIfLoaded(Image image)
{
    if(image.loaded) return 0;
    else return 1;
}

int Inverse(Image *image)
{
    for (size_t x = 0; x < image->width; x++)
    {
        for (size_t y = 0; y < image->height; y++)
        {
            unsigned char red, green, blue;
            GetPixel(image,x,y,red,green,blue);

            red = PIXELMAXVALUE - red;
            green = PIXELMAXVALUE - green;
            blue = PIXELMAXVALUE - blue;

            SetPixel(image,x,y,red,green,blue);
        }
        
    }
    
}

void SetPixel(Image *image,size_t x, size_t y, unsigned char red, unsigned char green, unsigned char blue)
{
    unsigned char *p = image->img;
    size_t index = x * image->channels + y * image->channels * image->width; 
    *(p + index) = red;
    *(p + index + 1) = green;
    *(p + index + 2) = blue;
}

void GetPixel(Image *image,size_t x, size_t y, unsigned char *red, unsigned char *green, unsigned char *blue)
{
    unsigned char *p = image->img;
    size_t index = x * image->channels + y * image->channels * image->width; 
    *red = (uint8_t)*(p + index);
    *green = (uint8_t)*(p + index + 1);
    *blue = (uint8_t)*(p + index + 2);
}