#include "helpers.h"
#include <math.h>
#include <stdio.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int temp[3];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp[0] = image[i][j].rgbtBlue;
            temp[1] = image[i][j].rgbtGreen;
            temp[2] = image[i][j].rgbtRed;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;

            image[i][width - 1 - j].rgbtBlue = temp[0];
            image[i][width - 1 - j].rgbtGreen = temp[1];
            image[i][width - 1 - j].rgbtRed = temp[2];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copyRGBTRIPLE[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copyRGBTRIPLE[i][j].rgbtRed = image[i][j].rgbtRed;
            copyRGBTRIPLE[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copyRGBTRIPLE[i][j].rgbtBlue = image[i][j].rgbtBlue;
            int count = 0;
            int temp[3] = {0};
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if (k < 0 || l < 0 || k >= height || l >= width)
                    {
                        temp[0] = temp[0];
                        temp[1] = temp[1];
                        temp[2] = temp[2];
                    }
                    else
                    {
                        temp[0] = temp[0] + image[k][l].rgbtBlue;
                        temp[1] = temp[1] + image[k][l].rgbtGreen;
                        temp[2] = temp[2] + image[k][l].rgbtRed;
                        count++;
                    }
                }
            }
            // printf("count:%d\n", count);
            // printf("R:%d G:%d B:%d \n",image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue);
            // printf("Copy: R:%d G:%d B:%d \n",copyRGBTRIPLE[i][j].rgbtRed, copyRGBTRIPLE[i][j].rgbtGreen, copyRGBTRIPLE[i][j].rgbtBlue);
            copyRGBTRIPLE[i][j].rgbtBlue = round(temp[0] / (float) count);
            copyRGBTRIPLE[i][j].rgbtGreen = round(temp[1] / (float) count);
            copyRGBTRIPLE[i][j].rgbtRed = round(temp[2] / (float) count);
            // printf("Later: R:%d G:%d B:%d \n",image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue);
            // printf("LaterCopy: R:%d G:%d B:%d \n",copyRGBTRIPLE[i][j].rgbtRed, copyRGBTRIPLE[i][j].rgbtGreen, copyRGBTRIPLE[i][j].rgbtBlue);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = copyRGBTRIPLE[i][j].rgbtRed;
            image[i][j].rgbtGreen = copyRGBTRIPLE[i][j].rgbtGreen;
            image[i][j].rgbtBlue = copyRGBTRIPLE[i][j].rgbtBlue;
        }
    }
    return;
}
