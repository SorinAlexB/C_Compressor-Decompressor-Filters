#ifndef FilterLib
#define FilterLib 
#include "structure.h"
void applyGrayscaleFilter(Pixel* pixels, int totalPixels);
void applyInvertFilter(Pixel* pixels, int totalPixels);
void applySepiaFilter(Pixel* pixels, int totalPixels);
void applyFilter(const char* inputFileName, const char* outputFileName, void (*filterFunction)(Pixel*, int));

#endif