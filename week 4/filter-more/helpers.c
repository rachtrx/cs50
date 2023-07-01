#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define RED 1
#define GREEN 2
#define BLUE 3

void averageColor(WORD totalRed, WORD totalBlue, WORD totalGreen, int divisor, int a, int b, RGBTRIPLE newImage[a][b]);

int calculations(int a, int b, int height, int width, int color, RGBTRIPLE newImage[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE red = image[i][j].rgbtRed;
            BYTE green = image[i][j].rgbtGreen;
            BYTE blue = image[i][j].rgbtBlue;
            WORD combined = red + green + blue;
            double average = (double) combined / 3;
            BYTE byteAverage = round(average);
            image[i][j].rgbtRed = byteAverage;
            image[i][j].rgbtGreen = byteAverage;
            image[i][j].rgbtBlue = byteAverage;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        RGBTRIPLE* tempRow = malloc(width * sizeof(RGBTRIPLE));
        for (int j = 0; j < width; j++)
        {
            tempRow[width - (j + 1)].rgbtRed = image[i][j].rgbtRed;
            tempRow[width - (j + 1)].rgbtGreen = image[i][j].rgbtGreen;
            tempRow[width - (j + 1)].rgbtBlue = image[i][j].rgbtBlue;
        }
        for (int a = 0; a < width; a++)
        {
            image[i][a] = tempRow[a];
        }
        free(tempRow);
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*newImage)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE topLeft = image[i - 1][j - 1];
            RGBTRIPLE topMiddle = image[i - 1][j];
            RGBTRIPLE topRight = image[i - 1][j + 1];
            RGBTRIPLE left = image[i][j - 1];
            RGBTRIPLE center = image[i][j];
            RGBTRIPLE right = image[i][j + 1];
            RGBTRIPLE bottomLeft = image[i + 1][j - 1];
            RGBTRIPLE bottomMiddle = image[i + 1][j];
            RGBTRIPLE bottomRight = image[i + 1][j + 1];
            WORD totalRed;
            WORD totalGreen;
            WORD totalBlue;
            double red;
            double green;
            double blue;
            if (i == 0 && j == 0)
            {
                totalRed = (WORD) center.rgbtRed + right.rgbtRed + bottomMiddle.rgbtRed + bottomRight.rgbtRed;
                totalBlue = (WORD) center.rgbtBlue + right.rgbtBlue + bottomMiddle.rgbtBlue + bottomRight.rgbtBlue;
                totalGreen = (WORD) center.rgbtGreen + right.rgbtGreen + bottomMiddle.rgbtGreen + bottomRight.rgbtGreen;
                red = round((double) totalRed / 4);
                blue = round((double) totalBlue / 4);
                green = round((double) totalGreen / 4);
                newImage[i][j].rgbtRed = red;
                newImage[i][j].rgbtGreen = green;
                newImage[i][j].rgbtBlue = blue;
            }
            else if (i == 0 && j == (width - 1))
            {
                totalRed = (WORD) center.rgbtRed + left.rgbtRed + bottomMiddle.rgbtRed + bottomLeft.rgbtRed;
                totalBlue = (WORD) center.rgbtBlue + left.rgbtBlue + bottomMiddle.rgbtBlue + bottomLeft.rgbtBlue;
                totalGreen = (WORD) center.rgbtGreen + left.rgbtGreen + bottomMiddle.rgbtGreen + bottomLeft.rgbtGreen;
                red = round((double) totalRed / 4);
                blue = round((double) totalBlue / 4);
                green = round((double) totalGreen / 4);
                newImage[i][j].rgbtRed = red;
                newImage[i][j].rgbtGreen = green;
                newImage[i][j].rgbtBlue = blue;
            }
            else if (i == (height - 1) && j == 0)
            {
                totalRed = (WORD) center.rgbtRed + topRight.rgbtRed + topMiddle.rgbtRed + right.rgbtRed;
                totalBlue = (WORD) center.rgbtBlue + topRight.rgbtBlue + topMiddle.rgbtBlue + right.rgbtBlue;
                totalGreen = (WORD) center.rgbtGreen + topRight.rgbtGreen + topMiddle.rgbtGreen + right.rgbtGreen;
                red = round((double) totalRed / 4);
                blue = round((double) totalBlue / 4);
                green = round((double) totalGreen / 4);
                newImage[i][j].rgbtRed = red;
                newImage[i][j].rgbtGreen = green;
                newImage[i][j].rgbtBlue = blue;
            }
            else if (i == (height - 1) && j == (width - 1))
            {
                totalRed = (WORD) center.rgbtRed + topLeft.rgbtRed + topMiddle.rgbtRed + left.rgbtRed;
                totalBlue = (WORD) center.rgbtBlue + topLeft.rgbtBlue + topMiddle.rgbtBlue + left.rgbtBlue;
                totalGreen = (WORD) center.rgbtGreen + topLeft.rgbtGreen + topMiddle.rgbtGreen + left.rgbtGreen;
                red = round((double) totalRed / 4);
                blue = round((double) totalBlue / 4);
                green = round((double) totalGreen / 4);
                newImage[i][j].rgbtRed = red;
                newImage[i][j].rgbtGreen = green;
                newImage[i][j].rgbtBlue = blue;
            }
            else if (i == 0)
            {
                totalRed = (WORD) left.rgbtRed + bottomLeft.rgbtRed + center.rgbtRed + bottomMiddle.rgbtRed + right.rgbtRed + bottomRight.rgbtRed;
                totalBlue = (WORD) left.rgbtBlue + bottomLeft.rgbtBlue + center.rgbtBlue + bottomMiddle.rgbtBlue + right.rgbtBlue + bottomRight.rgbtBlue;
                totalGreen = (WORD) left.rgbtGreen + bottomLeft.rgbtGreen + center.rgbtGreen + bottomMiddle.rgbtGreen + right.rgbtGreen + bottomRight.rgbtGreen;
                red = round((double) totalRed / 6);
                blue = round((double) totalBlue / 6);
                green = round((double) totalGreen / 6);
                newImage[i][j].rgbtRed = red;
                newImage[i][j].rgbtGreen = green;
                newImage[i][j].rgbtBlue = blue;
            }
            else if (i == (height - 1))
            {
                totalRed = (WORD) left.rgbtRed + topLeft.rgbtRed + center.rgbtRed + topMiddle.rgbtRed + right.rgbtRed + topRight.rgbtRed;
                totalBlue = (WORD) left.rgbtBlue + topLeft.rgbtBlue + center.rgbtBlue + topMiddle.rgbtBlue + right.rgbtBlue + topRight.rgbtBlue;
                totalGreen = (WORD) left.rgbtGreen + topLeft.rgbtGreen + center.rgbtGreen + topMiddle.rgbtGreen + right.rgbtGreen + topRight.rgbtGreen;
                red = round((double) totalRed / 6);
                blue = round((double) totalBlue / 6);
                green = round((double) totalGreen / 6);
                newImage[i][j].rgbtRed = red;
                newImage[i][j].rgbtGreen = green;
                newImage[i][j].rgbtBlue = blue;
            }
            else if (j == 0)
            {
                totalRed = (WORD) center.rgbtRed + topMiddle.rgbtRed + right.rgbtRed + topRight.rgbtRed + bottomMiddle.rgbtRed + bottomRight.rgbtRed;
                totalBlue = (WORD) center.rgbtBlue + topMiddle.rgbtBlue + right.rgbtBlue + topRight.rgbtBlue + bottomMiddle.rgbtBlue + bottomRight.rgbtBlue;
                totalGreen = (WORD) center.rgbtGreen + topMiddle.rgbtGreen + right.rgbtGreen + topRight.rgbtGreen + bottomMiddle.rgbtGreen + bottomRight.rgbtGreen;
                red = round((double) totalRed / 6);
                blue = round((double) totalBlue / 6);
                green = round((double) totalGreen / 6);
                newImage[i][j].rgbtRed = red;
                newImage[i][j].rgbtGreen = green;
                newImage[i][j].rgbtBlue = blue;
            }
            else if (j == (width - 1))
            {
                totalRed = (WORD) center.rgbtRed + topMiddle.rgbtRed + left.rgbtRed + topLeft.rgbtRed + bottomMiddle.rgbtRed + bottomLeft.rgbtRed;
                totalBlue = (WORD) center.rgbtBlue + topMiddle.rgbtBlue + left.rgbtBlue + topLeft.rgbtBlue + bottomMiddle.rgbtBlue + bottomLeft.rgbtBlue;
                totalGreen = (WORD) center.rgbtGreen + topMiddle.rgbtGreen + left.rgbtGreen + topLeft.rgbtGreen + bottomMiddle.rgbtGreen + bottomLeft.rgbtGreen;
                red = round((double) totalRed / 6);
                blue = round((double) totalBlue / 6);
                green = round((double) totalGreen / 6);
                newImage[i][j].rgbtRed = red;
                newImage[i][j].rgbtGreen = green;
                newImage[i][j].rgbtBlue = blue;
            }
            else
            {
                totalRed = (WORD) center.rgbtRed + topMiddle.rgbtRed + left.rgbtRed + topLeft.rgbtRed + bottomMiddle.rgbtRed + bottomLeft.rgbtRed + right.rgbtRed + topRight.rgbtRed + bottomRight.rgbtRed;
                totalBlue = (WORD) center.rgbtBlue + topMiddle.rgbtBlue + left.rgbtBlue + topLeft.rgbtBlue + bottomMiddle.rgbtBlue + bottomLeft.rgbtBlue + right.rgbtBlue + topRight.rgbtBlue + bottomRight.rgbtBlue;
                totalGreen = (WORD) center.rgbtGreen + topMiddle.rgbtGreen + left.rgbtGreen + topLeft.rgbtGreen + bottomMiddle.rgbtGreen + bottomLeft.rgbtGreen + right.rgbtGreen + topRight.rgbtGreen + bottomRight.rgbtGreen;
                red = round((double) totalRed / 9);
                blue = round((double) totalBlue / 9);
                green = round((double) totalGreen / 9);
                newImage[i][j].rgbtRed = red;
                newImage[i][j].rgbtGreen = green;
                newImage[i][j].rgbtBlue = blue;
            }
        }
    }
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            image[a][b].rgbtRed = newImage[a][b].rgbtRed;
            image[a][b].rgbtGreen = newImage[a][b].rgbtGreen;
            image[a][b].rgbtBlue = newImage[a][b].rgbtBlue;
        }
    }
}

void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*newImage)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            newImage[a][b] = image[a][b];

        }
    }
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            BYTE redPixel = calculations(a, b, height, width, RED, newImage);
            BYTE greenPixel = calculations(a, b, height, width, GREEN, newImage);
            BYTE bluePixel = calculations(a, b, height, width, BLUE, newImage);
            image[a][b].rgbtRed = redPixel;
            image[a][b].rgbtGreen = greenPixel;
            image[a][b].rgbtBlue = bluePixel;
        }
    }
    return;
}

int calculations(int a, int b, int height, int width, int color, RGBTRIPLE newImage[height][width])
{
    int values[9];
    int Gx[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int Gy[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    int count = 0;
    for (int row = a - 1; row <= a + 1; row++)
    {
        for (int column = b - 1; column <= b + 1; column++)
        {
            if (row < 0 || row >= height || column < 0 || column >= width)
            {
                values[count] = 0;
            }
            else if (color == RED)
            {
                values[count] = newImage[row][column].rgbtRed;
            }
            else if (color == GREEN)
            {
                values[count] = newImage[row][column].rgbtGreen;
            }
            else if (color == BLUE)
            {
                values[count] = newImage[row][column].rgbtBlue;
                // if (a == 0 && b == 0)
                // {
                //     printf("%i'\n", newImage[row][column].rgbtBlue);
                // }
            }
            count++;
        }
    }

    int Gxsum = 0;
    int Gysum = 0;
    int finalSum;
    for (int c = 0; c < 9; c++)
    {
        Gx[c] *= values[c];
        Gxsum += Gx[c];
        Gy[c] *= values[c];
        Gysum += Gy[c];
    }
    finalSum = round(sqrt(Gxsum * Gxsum + Gysum * Gysum));
    if (finalSum > 255)
    {
        finalSum = 255;
    }
    return finalSum;
}