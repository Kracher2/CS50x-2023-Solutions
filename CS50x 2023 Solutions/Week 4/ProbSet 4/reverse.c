#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open %s\n.", argv[1]);
        return 1;
    }

    // Read header
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, input);

    // Ensure WAV format
    if (check_format(header) == 0)
    {
        printf("Input is not a WAV file.\n");
        fclose(input);
        return 1;
    }

    // Open output file for writing
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open %s.\n", argv[2]);
        fclose(input);
        return 1;
    }

    // Write header to file
    fwrite(&header, sizeof(WAVHEADER), 1, output);

    // Calculate size of block
    BYTE BLOCKSIZE = get_block_size(header);

    // Set starting point
    if (fseek(input, BLOCKSIZE, SEEK_END))
    {
        return 1;
    }
    BYTE buffer[BLOCKSIZE];
    while (ftell(input) - BLOCKSIZE > sizeof(header))
    {
        // Seek to previous block position
        if (fseek(input, -2 * BLOCKSIZE, SEEK_CUR))
        {
            return 1;
        }
        // Read a block of data
        fread(buffer, BLOCKSIZE, 1, input);
        // Write the block of data in reverse order to the output file
        fwrite(buffer, BLOCKSIZE, 1, output);
    }

    // Close input and output files
    fclose(input);
    fclose(output);
    return 0;
}

// Function to check if input file has WAV format
int check_format(WAVHEADER header)
{
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
    {
        return 1;
    }
    return 0;
}

// Function to calculate size of data block based on WAV header information
int get_block_size(WAVHEADER header)
{
    int size = header.numChannels * (header.bitsPerSample / 8);
    return size;
}
