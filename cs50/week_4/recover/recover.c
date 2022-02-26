#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    //Declare types and sizes
    const int BLOCK_SIZE = 512;
    typedef uint8_t BYTE;
    BYTE buffer[BLOCK_SIZE];
    char filename[8];
    FILE *img;
    int c = 0;

    //Check if there are a command argument
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    //Open file
    FILE *file = fopen(argv[1], "r");

    //If file not open
    if (file == NULL)
    {
        fclose(file);
        printf("File could not be opened\n");
        return 1;
    }

    //Read memory card
    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        //Check if JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //Making the first JPG
            if (c == 0)
            {
                sprintf(filename, "%03i.jpg", c);
                img = fopen(filename, "w");
                if (img == NULL)
                {
                    fclose(img);
                    printf("img could not be opened\n");
                    return 1;
                }
                fwrite(buffer, 1, BLOCK_SIZE, img);
                c++;
            }
            //Making the others
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", c);
                img = fopen(filename, "w");
                if (img == NULL)
                {
                    fclose(img);
                    printf("img could not be opened\n");
                    return 1;
                }
                fwrite(buffer, 1, BLOCK_SIZE, img);
                c++;
            }
        }
        else
        {
            if (c > 0)
            {
                fwrite(buffer, 1, BLOCK_SIZE, img);
            }
        }
    }
    //Close files
    fclose(img);
    fclose(file);
    return 0;
}