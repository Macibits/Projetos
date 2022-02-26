#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(int count, string input[])
{
    //Check if command has 2 arguments
    if (count == 2)
    {
        //Check if input is digit
        for (int i = 0, l = strlen(input[1]); i < l; i++)
        {
            if isdigit(input[1][i])
            {
            }
            else
            {
                printf("Key must be a positive number\n");
                return 1;
                exit(1);
            }
        }

        //Turn in intenger
        int key = atoi(input[1]);

        //Get Plain text
        string plain = get_string("Plain text: ");

        //Conversion
        printf("Ciphertext: ");
        for (int c = 0, len = strlen(plain); c < len; c++)
        {
            if (isupper(plain[c]))
            {
                plain[c] = ((plain[c] - 65) + key) % 26;
                printf("%c", plain[c] + 65);
            }
            else if (islower(plain[c]))
            {
                plain[c] = ((plain[c] - 97) + key) % 26;
                printf("%c", plain[c] + 97);
            }
            else
            {
                printf("%c", plain[c]);
            }
        }
        printf("\n");
        return 0;
    }
    else
    {
        //Check if key exist
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

