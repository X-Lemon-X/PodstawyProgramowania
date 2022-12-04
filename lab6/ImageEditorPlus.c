#include <stdio.h>
#include <stdlib.h>


#include "ImageEditorPlus.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"


int LoadImage(struct Image *image ,char *path){
    image->img = stbi_load("sky.jpg", &image->width, &image->height, &image->channels, 0);
    if(image->img == NULL) return 1;
    else return 0;
}

