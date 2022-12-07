#ifndef IMAGEEDITORPLUS_H
#define IMAGEEDITORPLUS_H


#ifndef STBI_NO_STDIO
#include <stdio.h>
#endif // STBI_NO_STDIO


typedef struct {
    unsigned char *img;
    int width, height, channels, loaded;
    size_t sizeIn, sizeOut, imageSize;
    char *inPath, *outPath;
    FILE *in;
    FILE *out;

} Image;

int LoadImage(Image *image ,char *inPath, size_t sizeIn ,char *outPath, size_t sizeOut);
int SaveImage_as_png(Image image);
int SaveImage_as_jpg(Image image);
void FreeMemory(Image *image);


#endif