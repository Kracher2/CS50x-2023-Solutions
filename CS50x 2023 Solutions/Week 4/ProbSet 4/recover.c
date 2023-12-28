#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check for correct number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    }

    // Open the forensic image for reading
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file");
        return 1;
    }

    // Initialize variables
    BYTE buffer[BLOCK_SIZE];
    FILE *output = NULL;
    int count = 0;

    // Read forensic image input block by block
    while (fread(buffer, 1, BLOCK_SIZE, input) == BLOCK_SIZE)
    {
        // Check for start of new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close previous JPEG file if there is one
            if (output != NULL)
            {
                fclose(output);
            }

            // Create a new JPEG file
            char filename[8];
            sprintf(filename, "%03d.jpg", count++);
            output = fopen(filename, "w");

            // Check for creation success
            if (output == NULL)
            {
                printf("Could not create %s\n", filename);
                fclose(input);
                return 1;
            }
        }

        // Write current block to output if JPEG has been found
        if (output != NULL)
        {
            fwrite(buffer, 1, BLOCK_SIZE, output);
        }
    }

    // Close last JPEG file
    if (output != NULL)
    {
        fclose(output);
    }

    // Close input file
    fclose(input);

    return 0;
}
