

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


typedef struct {
    unsigned char *img;
    int width, height, channels, loaded, imageType;
    size_t sizeIn, sizeOut, imageSize;
    char *inPath, *outPath;
} Image;

typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} Pixel;

int LoadImage(Image *image ,char *inPath, size_t sizeIn ,char *outPath, size_t sizeOut, int saveAsImageType);
int SaveImage(Image *image);
int Inverse(Image *image);
int UseFullScale(Image * image);
void FreeMemory(Image *image);
int EdgingPhoto(Image *image, unsigned char edgeRed,unsigned char edgeGreen, unsigned char edgeBlue);
int GrayScale(Image *image);

#endif