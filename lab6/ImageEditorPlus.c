#include <stdio.h>
#include <stdlib.h>


#include "ImageEditorPlus.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

/*
    funkcja ladujaca zdjęcie kożystając z funkcji biblioteki stbi_load wiecej informacji nie bedę przepisywał są dostępne w stb_image.h linia 138
*/
int LoadImage(Image *image ,char *path){

    int x,y,n;
    if(!stbi_info(path, &x, &y, &n)) return -2;


    image->img = stbi_load(path, &image->width, &image->height, &image->channels, 0);
    if(image->img == NULL) return -1;
    else return 0;
}

