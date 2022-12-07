

#ifndef IMAGEEDITORPLUS_H
#define IMAGEEDITORPLUS_H

typedef struct {
    unsigned char *img;
    int width, height, channels, loaded;
    size_t sizeIn, sizeOut;
    char *inPath, *outPath;

} Image;

int LoadImage(Image *image ,char *inPath, size_t sizeIn ,char *outPath, size_t sizeOut);
int SaveImage_as_png(Image image);
int SaveImage_as_jpg(Image image);
void FreeMemory(Image *image);


#endif