#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "ImageEditorPlus.h"

//#define STBI_NO_STDIO

#define DEFAULT_IMAGE_OUTPUT_FILE_NAME_PNG "out.png"
#define DEFAULT_IMAGE_OUTPUT_FILE_NAME_JPG "out.jpg"
#define BUFFSIZE 256

#define true 1
#define false 0

typedef unsigned char uint8_t;

int SaveImage(Image *image);
int SaveImage_as_png(Image image);
int SaveImage_as_jpg(Image image);
void Clear(Image *image);
int CheckIfLoaded(Image image);
void SetPixel(Image *image,size_t x, size_t y, Pixel pixel);
void GetPixel(Image *image,size_t x, size_t y, Pixel *pixel);
void CopyChar(char *source, char **dest);

/*
int main()
{
   Image image;
  char *pathIn =  "C:/Users/patdu/Desktop/IT/pwr/PodstawyProgramowania/lab6/stb_image/cube.png";
  char *pathOut =  "C:/Users/patdu/Desktop/IT/pwr/PodstawyProgramowania/lab6/stb_image/cube2.png";
  int i =LoadImage(&image,pathIn,pathOut,IMAGE_TYPE_PNG);
  printf("-->%i\n",i);
  i = Inverse(&image);
  printf("-->%i\n",i);
  i = SaveImage(&image);
  printf("-->%i\n",i);
    FreeMemory(&image);
}
*/

/*
    sprawdza czy podana zotala ścieżka do pliku dla wyjścia i wejścia 
    funkcja ladujaca zdjęcie kożystając z funkcji biblioteki stbi_load 
    wiecej informacji nie bedę przepisywał są dostępne w stb_image.h linia 138
*/
int LoadImage(Image *image ,char *inPath, char *outPath, int saveAsImageType){
    
    Clear(image);
    if(saveAsImageType!= IMAGE_TYPE_JPG && saveAsImageType!=IMAGE_TYPE_PNG) return ERROR_IMAGETYPE;
    if(inPath == NULL) return NOINPUTFILE;

    if(outPath == NULL) image->outPath = NULL;
    else CopyChar(outPath,&(image->outPath)); 

    CopyChar(inPath,&(image->inPath));

    image->imageType=saveAsImageType;
    int x,y,nChanels;
    if(!stbi_info(inPath, &x, &y, &nChanels)) return FILEEXTENSIONNOTSUPPORTED;
    
    image->img = stbi_load(inPath, &image->width, &image->height, &image->channels, STBI_default);
    if(image->img == NULL) return IMAGENOTLOADED;
    
    image->imageSize = image->width * image->height * image->channels;
    image->loaded=1;
    return 0;
}

void CopyChar(char *source, char **dest)
{
    *dest = (char*)calloc(strlen(source)+1,sizeof(char));
    strcpy(*dest,source);
}

/*
FUNCKJA ZAPISUJĄCA ZDJECIE NA PODSTAWIE USTAWIEŃ
*/
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
    return stbi_write_png(path, image.width, image.height, image.channels, image.img, image.width * image.channels)? 0 : ERROR_IMAGE_DIDNT_SAVE;    
}

/*
    Zapisuje zdjęcie jako jpg
*/
int SaveImage_as_jpg(Image image)
{
    char *path =image.outPath ;
    if(path == NULL) path=DEFAULT_IMAGE_OUTPUT_FILE_NAME_JPG;
    return stbi_write_jpg(path,image.width, image.height, image.channels, image.img, 100)? 0 : ERROR_IMAGE_DIDNT_SAVE;
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

/*
Funckja zeruje wartości obrazu
*/
void Clear(Image *image)
{   
    image->imageSize=0;
    image->height=0;
    image->width=0;
    image->channels=0;
    image->inPath=NULL;
    image->outPath=NULL;
}

/*
Sprawdza czy zdjęcie zostało poprawnie załadowane
*/
int CheckIfLoaded(Image image)
{
    return image.loaded;
}

/*
Zmienia kolor na uśredniony szary
*/
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

/*
odwraca zdjęcie
*/
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

/*
rozciągnięcie histogramu
*/
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

/*
kopiuje pixel
*/
void CopyPixel(Pixel source, Pixel *destintion)
{
    destintion->red=source.red;
    destintion->green=source.green;
    destintion->blue=source.blue;
}

/*
zeruje wartość pixela
*/
void ZeroPixel(Pixel *pixel)
{
    pixel->red=0;
    pixel->green=0;
    pixel->blue=0;
}

/*
proguje zdjęcie
*/
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

/*
ustawia pixel[x][y] w zdjeciu na dany pixel
*/
void SetPixel(Image *image,size_t x, size_t y, Pixel pixel)
{
    size_t index = x * image->channels + y * image->channels * image->width; 
    *(image->img + index) = pixel.red;
    *(image->img + index + 1) = pixel.green;
    *(image->img + index + 2) = pixel.blue;
}

/*
pobiera wartość pixel[x][y] ze zdjeciu
*/
void GetPixel(Image *image,size_t x, size_t y, Pixel *pixel)
{
    size_t index = x * image->channels + y * image->channels * image->width; 
    pixel->red = (uint8_t)*(image->img + index);
    pixel->green = (uint8_t)*(image->img + index + 1);
    pixel->blue = (uint8_t)*(image->img + index + 2);
}