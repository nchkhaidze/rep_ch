#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //check correct arguments
    if (argc != 2)
    {
        printf("Usage: ./recover file\n");
        return 1;
    }

    //file for reading is opened
    FILE *in_file = fopen(argv[1], "r");
    if (in_file == NULL)
    {
        printf("Could not open file for reading\n");
        return 1;
    }

    //initialize counter for jpeg images, open stream for writing
    int jpeg_count = 0;
    char jpeg[8];
    FILE *out_file;


    //create buffer for reading the raw file
    BYTE buffer[512];

    while (fread(&buffer, 1, 512, in_file) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xe0) == 0xe0))
        {

            if (jpeg_count)
            {
                fclose(out_file);
            }

            sprintf(jpeg, "%03i.jpg", jpeg_count);
            out_file = fopen(jpeg, "w");
            if (out_file == NULL)
            {
                fclose(in_file);
                printf("Could not open file for writing\n");
                return 1;
            }

            jpeg_count++;
        }
        if (jpeg_count)
        {
            fwrite(&buffer, sizeof(BYTE), 512, out_file);
        }
    }

    fclose(in_file);
    fclose(out_file);
}
