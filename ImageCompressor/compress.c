#include <stdio.h>
#include <stdlib.h>
#include "compress.h"
#include "structure.h"
void compressBMP(const char* inputFileName, const char* outputFileName) {
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

    FILE* outputFile = fopen(outputFileName, "wb");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        free(pixels);
        return;
    }

    fwrite(header, sizeof(unsigned char), 54, outputFile);

    int count = 1;
    for (int i = 1; i < totalPixels; i++) {
        if (pixels[i].blue == pixels[i - 1].blue && 
            pixels[i].green == pixels[i - 1].green &&
            pixels[i].red == pixels[i - 1].red) {
            count++;
        } else {
            fwrite(&count, sizeof(int), 1, outputFile);
            fwrite(&pixels[i - 1], sizeof(Pixel), 1, outputFile);
            count = 1;
        }
    }

    fwrite(&count, sizeof(int), 1, outputFile);
    fwrite(&pixels[totalPixels - 1], sizeof(Pixel), 1, outputFile);

    fclose(outputFile);

    free(pixels);

    printf("File compressed successfully.\n");
}

