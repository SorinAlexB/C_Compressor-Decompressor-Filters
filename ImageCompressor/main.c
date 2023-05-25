
#include "decompress.h"
#include "compress.h"
#include "filter.h" 

int main(int arc, char *argv[])
{
    compressBMP(argv[1], argv[2]);
    decompressBMP(argv[2], argv[3]);
    applyFilter(argv[1], argv[4], applyGrayscaleFilter);
    applyFilter(argv[1], argv[5], applyInvertFilter);
    applyFilter(argv[1], argv[6], applySepiaFilter);
}