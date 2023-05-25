#include <stdio.h>
#include <stdlib.h>
#include "filter.h"

void applyGrayscaleFilter(Pixel* pixels, int totalPixels) {
    for (int i = 0; i < totalPixels; i++) {
        unsigned char average = (pixels[i].blue + pixels[i].green + pixels[i].red) / 3;
        pixels[i].blue = average;
        pixels[i].green = average;
        pixels[i].red = average;
    }
}

void applyInvertFilter(Pixel* pixels, int totalPixels) {
    for (int i = 0; i < totalPixels; i++) {
        pixels[i].blue = 255 - pixels[i].blue;
        pixels[i].green = 255 - pixels[i].green;
        pixels[i].red = 255 - pixels[i].red;
    }
}

void applySepiaFilter(Pixel* pixels, int totalPixels) {
    for (int i = 0; i < totalPixels; i++) {
        unsigned char originalBlue = pixels[i].blue;
        unsigned char originalGreen = pixels[i].green;
        unsigned char originalRed = pixels[i].red;

        pixels[i].blue = (unsigned char)((originalRed * 0.131) + (originalGreen * 0.534) + (originalBlue * 0.272));
        pixels[i].green = (unsigned char)((originalRed * 0.168) + (originalGreen * 0.686) + (originalBlue * 0.349));
        pixels[i].red = (unsigned char)((originalRed * 0.189) + (originalGreen * 0.769) + (originalBlue * 0.393));
    }
}

void applyFilter(const char* inputFileName, const char* outputFileName, void (*filterFunction)(Pixel*, int)) {
    
    FILE* inputFile = fopen(inputFileName, "rb");
    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return;
    }

    
    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, inputFile);

    
    int width = *(int*)&header[18];
    int height = *(int*)&header[22];

    
    int totalPixels = width * height;

    
    Pixel* pixels = (Pixel*)malloc(sizeof(Pixel) * totalPixels);

    
    fread(pixels, sizeof(Pixel), totalPixels, inputFile);

    
    fclose(inputFile);

   
    filterFunction(pixels, totalPixels);

   
    FILE* outputFile = fopen(outputFileName, "wb");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        free(pixels);
        return;
    }

 
    fwrite(header, sizeof(unsigned char), 54, outputFile);

    
    fwrite(pixels, sizeof(Pixel), totalPixels, outputFile);

    
    fclose(outputFile);

    
    free(pixels);

    printf("Filter applied successfully.\n");
}