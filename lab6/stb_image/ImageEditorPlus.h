

#ifndef IMAGEEDITORPLUS_H
#define IMAGEEDITORPLUS_H

#define PIXELMAXVALUE 255
#define PIXELMINVALUE 0

#define IMAGENOTLOADED -1
#define FILEEXTENSIONNOTSUPPORTED -2
#define NOINPUTFILE -3
#define ERROR_IMAGETYPE -7

#define OK 0

#define IMAGE_TYPE_JPG 1
#define IMAGE_TYPE_PNG 2
/**
 * -----------------------------------INFORMACJE---------------------------------------------------------------
 * 
 * 
 *  struktura obrazu w Image.img jest następująca:
 *  jest to tablica jedno wymiarowa która ma n =(width * height * chanels) elementów
 *  w takiej kolejności [ {red, green, blue, alfa ...} , {red green ... }  ] 
 *  rzeby odzyskać  pixel[x][y] należy pobrać wartość    
 *  unsigned char *p = Image.img + (x * width * chanels +  y * height * chanels)
 *  red = *p
 *  blue = *(p + 1)
 *  green = *(p + 2)
 * 
 * wartosć pixeli są w granicy 0..255
 * obrazy pgm i pmm są więć żutowane z ich rozdzielczości na  0..255
 * obrazy typu ppm i pgm są możliwe do odczytu tylko w ich formie binarnej forma ASCI nie jest obsługiwany  
 * 
 *  Obsługiwane formaty:
 *      JPEG baseline & progressive (12 bpc/arithmetic not supported, same as stock IJG lib)
 *      PNG 1/2/4/8/16-bit-per-channel
 *
 *      TGA (not sure what subset, if a subset)
 *      BMP non-1bpp, non-RLE
 *      PSD (composited view only, no extra channels, 8/16 bit-per-channel)
 *
 *      GIF (*comp always reports as 4-channel)
 *      HDR (radiance rgbE format)
 *      PIC (Softimage PIC)
 *      PNM (PPM and PGM binary only)
 * 
 * */

typedef struct {
    unsigned char *img;
    int width, height, channels, loaded, imageType;
    size_t imageSize;
    char *inPath, *outPath;
} Image;

/*
Struktura trzymająca wartości pixela
*/
typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} Pixel;

int LoadImage(Image *image ,char *inPath, char *outPath, int saveAsImageType);
int SaveImage(Image *image);
int Inverse(Image *image);
int UseFullScale(Image * image);
void FreeMemory(Image *image);
int EdgingPhoto(Image *image, unsigned char edgeRed,unsigned char edgeGreen, unsigned char edgeBlue);
int GrayScale(Image *image);

#endif