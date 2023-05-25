#include <stdio.h>
#include <stdlib.h>
#include "decompress.h"
#include "structure.h"
void decompressBMP(const char* inputFileName, const char* outputFileName) {
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

    FILE* outputFile = fopen(outputFileName, "wb");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        free(pixels);
        return;
    }

    fwrite(header, sizeof(unsigned char), 54, outputFile);

    // Read compressed data from input file
    int count;
    fread(&count, sizeof(int), 1, inputFile);

    for (int i = 0; i < totalPixels; i++) {
        fread(&pixels[i], sizeof(Pixel), 1, inputFile);

        // Write pixel 'count' number of times to the output file
        for (int j = 0; j < count; j++) {
            fwrite(&pixels[i], sizeof(Pixel), 1, outputFile);
        }

        // Read the next 'count' value
        if (i < totalPixels - 1) {
            fread(&count, sizeof(int), 1, inputFile);
        }
    }

    fclose(inputFile);
    fclose(outputFile);
    free(pixels);

    printf("File decompressed successfully.\n");
}


