#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE* readptr = fopen(argv[1], "r");
    if (readptr == NULL)
    {
        printf("file in invalid!\n");
        return 1;
    }

    // Read header
    // TODO #3
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, readptr);
    // int endOfHeader = ftell(readptr);
    // printf("%i\n", endOfHeader);
    // printf("format: %s\n", header.format);

    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(header) != 1)
    {
        printf("wrong format");
        return 1;
    }

    // Open output file for writing
    // TODO #5
    FILE* writeptr = fopen(argv[2], "w");
    if (writeptr == NULL)
    {
        printf("file in invalid!\n");
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(&header, sizeof(WAVHEADER), 1, writeptr);


    // Use get_block_size to calculate size of block
    // TODO #7
    int blockSize = get_block_size(header);

    // Write reversed audio to file
    // TODO #8
    BYTE buffer[blockSize];
    fseek(readptr, blockSize, SEEK_END);
    while (ftell(readptr) - blockSize > sizeof(header))
    {
        if (fseek(readptr, - 2 * blockSize, SEEK_CUR))
        {
            return 1;
        }
        fread(buffer, blockSize, 1, readptr);
        fwrite(buffer, blockSize, 1, writeptr);
    }
    fclose(readptr);
    fclose(writeptr);
}

int check_format(WAVHEADER header)
    // TODO #4
{
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
    {
        return 1;
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    int blocksize = header.numChannels * header.bitsPerSample / 8;
    return blocksize;
}