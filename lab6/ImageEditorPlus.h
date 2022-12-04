

#ifndef IMAGEEDITORPLUS_H
#define IMAGEEDITORPLUS_H

struct Image{
unsigned char *img;
int width, height, channels;
};

int LoadImage(struct Image *image ,char *path);


#endif