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

void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int totalRedX = 0, totalGreenX = 0, totalBlueX = 0;
            int totalRedY = 0, totalGreenY = 0, totalBlueY = 0;

            for (int k = -1; k <= 1; k++)
            {
                for (int m = -1; m <= 1; m++)
                {
                    if (i + k >= 0 && i + k < height && j + m >= 0 && j + m < width)
                    {
                        totalRedX += temp[i + k][j + m].rgbtRed * Gx[k + 1][m + 1];
                        totalGreenX += temp[i + k][j + m].rgbtGreen * Gx[k + 1][m + 1];
                        totalBlueX += temp[i + k][j + m].rgbtBlue * Gx[k + 1][m + 1];

                        totalRedY += temp[i + k][j + m].rgbtRed * Gy[k + 1][m + 1];
                        totalGreenY += temp[i + k][j + m].rgbtGreen * Gy[k + 1][m + 1];
                        totalBlueY += temp[i + k][j + m].rgbtBlue * Gy[k + 1][m + 1];
                    }
                }
            }

            int totalRed = round(sqrt(pow(totalRedX, 2) + pow(totalRedY, 2)));
            int totalGreen = round(sqrt(pow(totalGreenX, 2) + pow(totalGreenY, 2)));
            int totalBlue = round(sqrt(pow(totalBlueX, 2) + pow(totalBlueY, 2)));

            totalRed = (totalRed > 255) ? 255 : (totalRed < 0) ? 0 : totalRed;
            totalGreen = (totalGreen > 255) ? 255 : (totalGreen < 0) ? 0 : totalGreen;
            totalBlue = (totalBlue > 255) ? 255 : (totalBlue < 0) ? 0 : totalBlue;

            image[i][j].rgbtRed = totalRed;
            image[i][j].rgbtGreen = totalGreen;
            image[i][j].rgbtBlue = totalBlue;
        }
    }
}
