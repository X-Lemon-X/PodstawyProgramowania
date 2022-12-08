#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "ImageEditorPlus.h"

#define STBI_NO_STDIO

#define DEFAULT_IMAGE_OUTPUT_FILE_NAME_PNG "out.png"
#define DEFAULT_IMAGE_OUTPUT_FILE_NAME_JPG "out.jpg"
#define BUFFSIZE 256

#define true 1
#define false 0


int SaveImage(Image *image);
int SaveImage_as_png(Image image);
int SaveImage_as_jpg(Image image);
void Clear(Image *image);
int CheckIfLoaded(Image image);
void SetPixel(Image *image,size_t x, size_t y, Pixel pixel);
void GetPixel(Image *image,size_t x, size_t y, Pixel *pixel);


/*
int main()
{
    Image img;
    char *pathIn = "/home/lemonx/IT/podstawyProgramowania/lab6/sampl.ppm";
    char *pathOut = "/home/lemonx/IT/podstawyProgramowania/lab6/samplout.png";
    size_t sizeIN = 53;
    size_t sizeOut = 56;
    printf("--> %i\n",sizeIN);
    int ret = LoadImage(&img, pathIn, sizeIN, pathOut, sizeOut, IMAGE_TYPE_PNG);
    printf("--> %i\n", ret);
    
    //GrayScaleAvarage(&img);
    //Inverse(&img);
    //EdgingPhoto(&img,100,100,100);
    UseFullScale(&img);
    SaveImage_as_png(img);
    FreeMemory(&img);
}
*/

/*
    sprawdza czy podana zotala ścieżka do pliku dla wyjścia i wejścia 
    funkcja ladujaca zdjęcie kożystając z funkcji biblioteki stbi_load 
    wiecej informacji nie bedę przepisywał są dostępne w stb_image.h linia 138
*/
int LoadImage(Image *image ,char *inPath, size_t sizeIn ,char *outPath, size_t sizeOut, int saveAsImageType){
    
    Clear(image);

    if(saveAsImageType!= IMAGE_TYPE_JPG && saveAsImageType!=IMAGE_TYPE_PNG) return ERROR_IMAGETYPE;

    if(inPath == NULL) return NOINPUTFILE;

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
    if(!stbi_info(inPath, &x, &y, &n)) return FILEEXTENSIONNOTSUPPORTED;
    
    image->img = stbi_load(inPath, &image->width, &image->height, &image->channels, STBI_default);
    if(image->img == NULL) return IMAGENOTLOADED;
    
    image->imageSize = image->width * image->height * image->channels;
    image->loaded=1;
    return 0;
}

int SaveImage(Image *image)
{
    if(!image->loaded) return IMAGENOTLOADED;

    if(image->imageType == IMAGE_TYPE_JPG)
        return SaveImage_as_jpg(*image);
    else if(image->imageType == IMAGE_TYPE_PNG)
        return SaveImage_as_png(*image);
}

/*
    Zapisuje zdjęcie jako png
*/
int SaveImage_as_png(Image image)
{
    char *path =image.outPath;
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
}

int CheckIfLoaded(Image image)
{
    return image.loaded;
}

int GrayScale(Image *image)
{
    if(!image->loaded) return IMAGENOTLOADED;

    Pixel pixel;
    for (size_t x = 0; x < image->width; x++)
    {
        for (size_t y = 0; y < image->height; y++)
        {
            GetPixel(image,x,y,&pixel);
            unsigned char valAvarage = (unsigned char)( pixel.red + pixel.green + pixel.blue )/3;
            pixel.red = valAvarage;
            pixel.green = valAvarage;
            pixel.blue = valAvarage;
            SetPixel(image,x,y,pixel);
        }
    }
    return OK;
}

int Inverse(Image *image)
{
    if(!image->loaded) return IMAGENOTLOADED;

    Pixel pixel;
    for (size_t x = 0; x < image->width; x++)
    {
        for (size_t y = 0; y < image->height; y++)
        {
            GetPixel(image,x,y,&pixel);
            pixel.red = PIXELMAXVALUE - pixel.red;
            pixel.green = PIXELMAXVALUE - pixel.green;
            pixel.blue = PIXELMAXVALUE - pixel.blue;
            SetPixel(image,x,y,pixel);
        }
    }
    return OK;
}

int UseFullScale(Image *image)
{
    if(!(image->loaded)) return IMAGENOTLOADED;
    Pixel min, max, pix;
    FindMaxMinValues(image,&max,&min);

    for (size_t x = 0; x < image->width; x++)
    {
        for (size_t y = 0; y < image->height; y++)
        {
            GetPixel(image,x,y,&pix);
            if(max.red-min.red) pix.red = (pix.red - min.red)* max.red/ (max.red - min.red);
            if(max.green-min.green) pix.green = (pix.green - min.green)* max.green/ (max.green - min.green);
            if(max.blue-min.blue) pix.blue = (pix.blue - min.blue)* max.blue/ (max.blue - min.blue); 
            SetPixel(image,x,y,pix);
        }   
    }

    //printf("--max> R%i  G%i   B%i\n", max.red,max.green,max.blue);
    //printf("--min> R%i  G%i   B%i\n", min.red,min.green,min.blue);

    return OK;
}

int FindMaxMinValues(Image *image, Pixel *pixelMax, Pixel *pixelMin)
{
    if(!image->loaded) return IMAGENOTLOADED;

    Pixel pixel;
    GetPixel(image,0,0,&pixel);
    CopyPixel(pixel,pixelMax);
    CopyPixel(pixel,pixelMin);

    for (size_t x = 0; x < image->width; x++)
    {
        for (size_t y = 0; y < image->height; y++)
        {
            GetPixel(image,x,y,&pixel);
            if(pixel.red > pixelMax->red) pixelMax->red=pixel.red;
            if(pixel.blue > pixelMax->blue) pixelMax->blue=pixel.blue;
            if(pixel.green > pixelMax->green) pixelMax->green=pixel.green;
    
            if(pixel.red < pixelMin->red) pixelMin->red=pixel.red;
            if(pixel.green < pixelMin->green) pixelMin->green=pixel.green;
            if(pixel.blue < pixelMin->blue) pixelMin->blue=pixel.blue;
        }
    }
    return OK;
}

void CopyPixel(Pixel source, Pixel *destintion)
{
    destintion->red=source.red;
    destintion->green=source.green;
    destintion->blue=source.blue;
}

void ZeroPixel(Pixel *pixel)
{
    pixel->red=0;
    pixel->green=0;
    pixel->blue=0;
}

int EdgingPhoto(Image *image, unsigned char edgeRed,unsigned char edgeGreen, unsigned char edgeBlue )
{   
    if(!image->loaded) return IMAGENOTLOADED;

    Pixel pixel;
    for (size_t x = 0; x < image->width; x++)
    {
        for (size_t y = 0; y < image->height; y++)
        {
            GetPixel(image,x,y,&pixel);
            if(pixel.red > edgeRed) pixel.red=PIXELMAXVALUE;
            else pixel.red = PIXELMINVALUE;
            if(pixel.green > edgeGreen) pixel.green=PIXELMAXVALUE;
            else pixel.green= PIXELMINVALUE;
            if(pixel.blue > edgeBlue) pixel.blue=PIXELMAXVALUE;
            else pixel.blue = PIXELMINVALUE;
            SetPixel(image,x,y,pixel);
        }   
    }
    return OK;
}

void SetPixel(Image *image,size_t x, size_t y, Pixel pixel)
{
    unsigned char *p = image->img;
    size_t index = x * image->channels + y * image->channels * image->width; 
    *(p + index) = pixel.red;
    *(p + index + 1) = pixel.green;
    *(p + index + 2) = pixel.blue;
}

void GetPixel(Image *image,size_t x, size_t y, Pixel *pixel)
{
    unsigned char *p = image->img;
    size_t index = x * image->channels + y * image->channels * image->width; 
    pixel->red = (uint8_t)*(p + index);
    pixel->green = (uint8_t)*(p + index + 1);
    pixel->blue = (uint8_t)*(p + index + 2);
}