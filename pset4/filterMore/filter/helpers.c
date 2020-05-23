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
            copyRGBTRIPLE[i][j].rgbtBlue = round(temp[0] / (float) count);
            copyRGBTRIPLE[i][j].rgbtGreen = round(temp[1] / (float) count);
            copyRGBTRIPLE[i][j].rgbtRed = round(temp[2] / (float) count);
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copyRGBTRIPLE[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int tempGx[3] = {0};
            int tempGy[3] = {0};
            int tempSum[3] = {0};
            int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
            int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if (k < 0 || l < 0 || k >= height || l >= width)
                    {
                        continue;
                    }
                    else
                    {
                        tempGx[0] = tempGx[0] + image[k][l].rgbtRed * Gx[k - i + 1][l - j + 1];
                        tempGx[1] = tempGx[1] + image[k][l].rgbtGreen * Gx[k - i + 1][l - j + 1];
                        tempGx[2] = tempGx[2] + image[k][l].rgbtBlue * Gx[k - i + 1][l - j + 1];
                        tempGy[0] = tempGy[0] + image[k][l].rgbtRed * Gy[k - i + 1][l - j + 1];
                        tempGy[1] = tempGy[1] + image[k][l].rgbtGreen * Gy[k - i + 1][l - j + 1];
                        tempGy[2] = tempGy[2] + image[k][l].rgbtBlue * Gy[k - i + 1][l - j + 1];
                        
                        // printf("Gx[%i][%i] %i * %i  %i\n",k,l,image[k][l].rgbtGreen,Gx[k-i+1][l-j+1],tempGx[1]);
                        // printf("Gy[%i][%i] %i * %i  %i\n",k,l,image[k][l].rgbtGreen,Gy[k-i+1][l-j+1],tempGy[1]);
                    }
                }
            }

            // smaller than 255
            tempSum[0] = round(sqrt(tempGx[0] * tempGx[0] + tempGy[0] * tempGy[0]));
            tempSum[1] = round(sqrt(tempGx[1] * tempGx[1] + tempGy[1] * tempGy[1]));
            tempSum[2] = round(sqrt(tempGx[2] * tempGx[2] + tempGy[2] * tempGy[2]));

            if (tempSum[0] > 255)
            {
                tempSum[0] = 255;
            }
            if (tempSum[1] > 255)
            {
                tempSum[1] = 255;
            }
            if (tempSum[2] > 255)
            {
                tempSum[2] = 255;
            }

            copyRGBTRIPLE[i][j].rgbtRed = tempSum[0];
            copyRGBTRIPLE[i][j].rgbtGreen = tempSum[1];
            copyRGBTRIPLE[i][j].rgbtBlue = tempSum[2];
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
