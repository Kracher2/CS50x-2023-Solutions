#include "helpers.h"
#include <math.h>

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue =
                round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
        }
    }
}

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepia_red = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            int sepia_green = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            int sepia_blue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);

            sepia_red = (sepia_red > 255) ? 255 : sepia_red;
            sepia_green = (sepia_green > 255) ? 255 : sepia_green;
            sepia_blue = (sepia_blue > 255) ? 255 : sepia_blue;

            image[i][j].rgbtRed = sepia_red;
            image[i][j].rgbtGreen = sepia_green;
            image[i][j].rgbtBlue = sepia_blue;
        }
    }
}

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[width - j - 1] = image[i][j];
        }
        for (int k = 0; k < width; k++)
        {
            image[i][k] = temp[k];
        }
    }
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float totalRed = 0;
            float totalGreen = 0;
            float totalBlue = 0;
            float count = 0;

            for (int k = -1; k < 2; k++)
            {
                for (int m = -1; m < 2; m++)
                {
                    if (i + k < 0 || i + k >= height || j + m < 0 || j + m >= width)
                    {
                        continue;
                    }

                    totalRed += temp[i + k][j + m].rgbtRed;
                    totalGreen += temp[i + k][j + m].rgbtGreen;
                    totalBlue += temp[i + k][j + m].rgbtBlue;
                    count++;
                }
            }

            image[i][j].rgbtRed = round(totalRed / count);
            image[i][j].rgbtGreen = round(totalGreen / count);
            image[i][j].rgbtBlue = round(totalBlue / count);
        }
    }
}
