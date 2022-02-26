#include "helpers.h"
#include "math.h"
#include "stdlib.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Two loops for height and width
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //condition to run only if is not a grayscale color
            if (image[i][j].rgbtBlue != image[i][j].rgbtGreen || image[i][j].rgbtGreen != image[i][j].rgbtRed ||
                image[i][j].rgbtBlue != image[i][j].rgbtRed)
            {
                //convert
                float av = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
                int avg = round(av);
                image[i][j].rgbtBlue = avg;
                image[i][j].rgbtGreen = avg;
                image[i][j].rgbtRed = avg;
            }
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //Two loos for height and width
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Get new sepia colors by formula
            float nr = 0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue;
            float ng = 0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue;
            float nb = 0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue;

            //Round values
            int sr = round(nr);
            int sg = round(ng);
            int sb = round(nb);

            //Cap if > 255
            if (sr > 255)
            {
                sr = 255;
            }
            if (sg > 255)
            {
                sg = 255;
            }
            if (sb > 255)
            {
                sb = 255;
            }
            //Give new color values
            image[i][j].rgbtRed = sr;
            image[i][j].rgbtGreen = sg;
            image[i][j].rgbtBlue = sb;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Declare a copy image 2d array
    RGBTRIPLE **copy;
    copy = (RGBTRIPLE **)calloc(height, sizeof(RGBTRIPLE *));
    for (int i = 0; i < height; i++)
    {
        copy[i] = (RGBTRIPLE *)calloc(width, sizeof(RGBTRIPLE));
    }

    //Nested loops
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Blur top left corner
            if (i == 0 && j == 0)
            {
                float r = (image[i][j].rgbtRed + image [i][j + 1].rgbtRed + image [i + 1][j].rgbtRed +
                           image [i + 1][j + 1].rgbtRed) / 4.0;
                float g = (image[i][j].rgbtGreen + image [i][j + 1].rgbtGreen + image [i + 1][j].rgbtGreen +
                           image [i + 1][j + 1].rgbtGreen) / 4.0;
                float b = (image[i][j].rgbtBlue + image [i][j + 1].rgbtBlue + image [i + 1][j].rgbtBlue +
                           image [i + 1][j + 1].rgbtBlue) / 4.0;
                copy[i][j].rgbtRed = round(r);
                copy[i][j].rgbtGreen = round(g);
                copy[i][j].rgbtBlue = round(b);
            }
            //Blur top right corner
            else if (i == 0 && j == width - 1)
            {
                float r = (image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i + 1][j - 1].rgbtRed +
                           image[i + 1][j].rgbtRed) / 4.0;
                float g = (image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                           image[i + 1][j].rgbtGreen) / 4.0;
                float b = (image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                           image[i + 1][j].rgbtBlue) / 4.0;
                copy[i][j].rgbtRed = round(r);
                copy[i][j].rgbtGreen = round(g);
                copy[i][j].rgbtBlue = round(b);
            }
            //Blur bottom left corner
            else if (i == height - 1 && j == 0)
            {
                float r = (image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j].rgbtRed +
                           image[i][j + 1].rgbtRed) / 4.0;
                float g = (image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j].rgbtGreen +
                           image[i][j + 1].rgbtGreen) / 4.0;
                float b = (image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j].rgbtBlue +
                           image[i][j + 1].rgbtBlue) / 4.0;
                copy[i][j].rgbtRed = round(r);
                copy[i][j].rgbtGreen = round(g);
                copy[i][j].rgbtBlue = round(b);
            }
            //Blur bottom right corner
            else if (i == height - 1 && j == width - 1)
            {
                float r = (image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed +
                           image [i][j].rgbtRed) / 4.0;
                float g = (image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen +
                           image [i][j].rgbtGreen) / 4.0;
                float b = (image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue +
                           image [i][j].rgbtBlue) / 4.0;
                copy[i][j].rgbtRed = round(r);
                copy[i][j].rgbtGreen = round(g);
                copy[i][j].rgbtBlue = round(b);
            }
            //Blur first line edge
            else if (i == 0 && j != 0 && j != width - 1)
            {
                float r = (image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                           image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6.0;
                float g = (image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                           image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6.0;
                float b = (image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                           image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6.0;
                copy[i][j].rgbtRed = round(r);
                copy[i][j].rgbtGreen = round(g);
                copy[i][j].rgbtBlue = round(b);
            }
            //Blur last line edge
            else if (i == height - 1 && j != 0 && j != width - 1)
            {
                float r = (image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                           image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed) / 6.0;
                float g = (image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                           image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen) / 6.0;
                float b = (image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                           image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue) / 6.0;
                copy[i][j].rgbtRed = round(r);
                copy[i][j].rgbtGreen = round(g);
                copy[i][j].rgbtBlue = round(b);
            }
            //Blur first column edge
            else if (j == 0 && i != 0 && i != height - 1)
            {
                float r = (image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j].rgbtRed +
                           image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6.0;
                float g = (image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j].rgbtGreen +
                           image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6.0;
                float b = (image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j].rgbtBlue +
                           image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6.0;
                copy[i][j].rgbtRed = round(r);
                copy[i][j].rgbtGreen = round(g);
                copy[i][j].rgbtBlue = round(b);
            }
            //Blur last column edge
            else if (j == width - 1 && i != 0 && i != height - 1)
            {
                float r = (image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed +
                           image [i][j].rgbtRed + image [i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed) / 6.0;
                float g = (image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen +
                           image [i][j].rgbtGreen + image [i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen) / 6.0;
                float b = (image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue +
                           image [i][j].rgbtBlue + image [i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue) / 6.0;
                copy[i][j].rgbtRed = round(r);
                copy[i][j].rgbtGreen = round(g);
                copy[i][j].rgbtBlue = round(b);
            }
            //Blur the middle
            else
            {
                float r = (image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                           image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                           image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 9.0;
                float g = (image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                           image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                           image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 9.0;
                float b = (image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                           image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                           image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 9.0;
                copy[i][j].rgbtRed = round(r);
                copy[i][j].rgbtGreen = round(g);
                copy[i][j].rgbtBlue = round(b);
            }
        }
    }

    //Paste copy to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
        }
    }

    //free copy
    for (int i = 0; i < height; i++)
    {
        free(copy[i]);
    }
    free(copy);
    return;
}
