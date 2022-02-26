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

    // Pyramid build - row
    for (int row = 0; row < height; row++)
    {
        // Pyramid build - left space
        for (int space = height - 1; space > row ; space--)
        {
            printf(" ");
        }
        // Pyramid build - left block
        for (int lblock = -1; lblock < row; lblock++)
        {
            printf("#");
        }
        // Pyramid build - gap
        for (int gap = row; gap == row; gap++)
        {
            printf("  ");
        }
        //Pyramid build - right block
        for (int rblock = -1; rblock < row; rblock++)
        {
            printf("#");
        }
        printf("\n");
    }
}