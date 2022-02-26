#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Input number by user
    int height;
    do
    {
        height = get_int("How tall is pyramid's height from 1 to 8: ");
    }
    while (height < 1 || height > 8);

    // Pyramid build
    for (int row = 0; row < height; row++)
    {
        for (int space = height - 1; space > row ; space--)
        {
            printf(" ");
        }
        for (int block = -1; block < row; block++)
        {
            printf("#");
        }
        printf("\n");
    }
}