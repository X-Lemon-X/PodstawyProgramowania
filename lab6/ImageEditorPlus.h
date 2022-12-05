

#ifndef IMAGEEDITORPLUS_H
#define IMAGEEDITORPLUS_H

typedef struct {
    unsigned char *img;
    int width, height, channels;
} Image;

int LoadImage(Image *image ,char *path);


#endif