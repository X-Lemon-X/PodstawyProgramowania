
#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

#define PHOTO_MAX_SIZE_W 500
#define PHOTO_MAX_SIZE_H 500
#define PATH_SIZE 200
#define PHOTO_FILE_BUFF 1000


struct Photo{
    int pixels[PHOTO_MAX_SIZE_H][PHOTO_MAX_SIZE_W];
    char comment[PHOTO_FILE_BUFF];
    unsigned int sizeW;
    unsigned int sizeH;
    int loaded;
    int maxWhiteValue;
};


int Inverse(struct Photo *);
int FindEdgeValues(int *min, int *max, struct Photo photo);
int EdgingPhoto(struct Photo *photoIn, int edge);
int FixPhotoToUseFullScaleValues(struct Photo *photoIn);
int LoadPhoto(struct Photo *photo, char path[PATH_SIZE]);
int SavePhoto(struct Photo *photo, char path[PATH_SIZE]);
#endif