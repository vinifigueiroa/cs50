#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{

    typedef uint8_t BYTE;

    // open memory card

    if (argc != 2)
    {
        printf("Usage instructions: Insert only the filename as an argument.");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // identify first jpeg

    BYTE *buffer = malloc(sizeof(BYTE) * 512);
    if (buffer == NULL)
    {
        printf("Could not allocate memory for file buffer.\n");
        return 2;
    }

    // initalize file counter
    int file_counter = 0;

    // initialize file name variable
    char *filename = malloc(sizeof(char) * 9);
    if (filename == NULL)
    {
        printf("Could not allocate memory for file name.\n");
        return 2;
    }

    // initialize image file
    FILE *image = NULL;

    while (fread(buffer, sizeof(BYTE), 512, card) == 512)
    {
        // check if it's the begining of a jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // close the previous one if it is not the first jpeg found
            if (file_counter != 0)
            {
                fclose(image);
            }

            // update filename, open new file and update counter
            sprintf(filename, "%03i.jpg", file_counter);
            image = fopen(filename, "w");
            fwrite(buffer, sizeof(BYTE), 512, image);
            file_counter++;

        }
        else
        {
            // if there is already a file being written, continue writing
            if (file_counter > 0)
            {
                fwrite(buffer, sizeof(BYTE), 512, image);
            }
        }
    }

    free(buffer);
    free(filename);
    fclose(image);
    fclose(card);

    return 0;

}