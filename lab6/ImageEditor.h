
#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

struct Image{
    int *pixels;
    int *pixelsR;
    int *pixelsG;
    int *pixelsB;
    char *comment;
    unsigned int sizeW;
    unsigned int sizeH;
    int loaded;
    int maxWhiteValue;
};

void LoadImage(struct Image *photo, char *path);
int InverseImage(struct Image *photoIn);
int FixImageToUseFullScaleValues(struct Image *photoIn) ;
int EdgingImage(struct Image *photoIn, int edge);
int FindEdgeValuesImage(int *min, int *max, struct Image photo);
void AddComment(struct Image *photo, char *comment);

#endif