#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// answer key: https://gist.github.com/ymeng979/9acff00badfdd4ae640f57919621950d

void averageColor(WORD totalRed, WORD totalBlue, WORD totalGreen, int divisor, int a, int b, RGBTRIPLE newImage[a][b]);

WORD calculations(BYTE* values);

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
            if (i == 0 && j == 0)
            {
                totalRed = (WORD) center.rgbtRed + right.rgbtRed + bottomMiddle.rgbtRed + bottomRight.rgbtRed;
                totalBlue = (WORD) center.rgbtBlue + right.rgbtBlue + bottomMiddle.rgbtBlue + bottomRight.rgbtBlue;
                totalGreen = (WORD) center.rgbtGreen + right.rgbtGreen + bottomMiddle.rgbtGreen + bottomRight.rgbtGreen;
                averageColor(totalRed, totalBlue, totalGreen, 4, i, j, newImage);
            }
            else if (i == 0 && j == (width - 1))
            {
                totalRed = (WORD) center.rgbtRed + left.rgbtRed + bottomMiddle.rgbtRed + bottomLeft.rgbtRed;
                totalBlue = (WORD) center.rgbtBlue + left.rgbtBlue + bottomMiddle.rgbtBlue + bottomLeft.rgbtBlue;
                totalGreen = (WORD) center.rgbtGreen + left.rgbtGreen + bottomMiddle.rgbtGreen + bottomLeft.rgbtGreen;
                averageColor(totalRed, totalBlue, totalGreen, 4, i, j, newImage);
            }
            else if (i == (height - 1) && j == 0)
            {
                totalRed = (WORD) center.rgbtRed + topRight.rgbtRed + topMiddle.rgbtRed + right.rgbtRed;
                totalBlue = (WORD) center.rgbtBlue + topRight.rgbtBlue + topMiddle.rgbtBlue + right.rgbtBlue;
                totalGreen = (WORD) center.rgbtGreen + topRight.rgbtGreen + topMiddle.rgbtGreen + right.rgbtGreen;
                averageColor(totalRed, totalBlue, totalGreen, 4, i, j, newImage);
            }
            else if (i == (height - 1) && j == (width - 1))
            {
                totalRed = (WORD) center.rgbtRed + topLeft.rgbtRed + topMiddle.rgbtRed + left.rgbtRed;
                totalBlue = (WORD) center.rgbtBlue + topLeft.rgbtBlue + topMiddle.rgbtBlue + left.rgbtBlue;
                totalGreen = (WORD) center.rgbtGreen + topLeft.rgbtGreen + topMiddle.rgbtGreen + left.rgbtGreen;
                averageColor(totalRed, totalBlue, totalGreen, 4, i, j, newImage);
            }
            else if (i == 0)
            {
                totalRed = (WORD) left.rgbtRed + bottomLeft.rgbtRed + center.rgbtRed + bottomMiddle.rgbtRed + right.rgbtRed + bottomRight.rgbtRed;
                totalBlue = (WORD) left.rgbtBlue + bottomLeft.rgbtBlue + center.rgbtBlue + bottomMiddle.rgbtBlue + right.rgbtBlue + bottomRight.rgbtBlue;
                totalGreen = (WORD) left.rgbtGreen + bottomLeft.rgbtGreen + center.rgbtGreen + bottomMiddle.rgbtGreen + right.rgbtGreen + bottomRight.rgbtGreen;
                averageColor(totalRed, totalBlue, totalGreen, 6, i, j, newImage);
            }
            else if (i == (height - 1))
            {
                totalRed = (WORD) left.rgbtRed + topLeft.rgbtRed + center.rgbtRed + topMiddle.rgbtRed + right.rgbtRed + topRight.rgbtRed;
                totalBlue = (WORD) left.rgbtBlue + topLeft.rgbtBlue + center.rgbtBlue + topMiddle.rgbtBlue + right.rgbtBlue + topRight.rgbtBlue;
                totalGreen = (WORD) left.rgbtGreen + topLeft.rgbtGreen + center.rgbtGreen + topMiddle.rgbtGreen + right.rgbtGreen + topRight.rgbtGreen;
                averageColor(totalRed, totalBlue, totalGreen, 6, i, j, newImage);
            }
            else if (j == 0)
            {
                totalRed = (WORD) center.rgbtRed + topMiddle.rgbtRed + right.rgbtRed + topRight.rgbtRed + bottomMiddle.rgbtRed + bottomRight.rgbtRed;
                totalBlue = (WORD) center.rgbtBlue + topMiddle.rgbtBlue + right.rgbtBlue + topRight.rgbtBlue + bottomMiddle.rgbtBlue + bottomRight.rgbtBlue;
                totalGreen = (WORD) center.rgbtGreen + topMiddle.rgbtGreen + right.rgbtGreen + topRight.rgbtGreen + bottomMiddle.rgbtGreen + bottomRight.rgbtGreen;
                averageColor(totalRed, totalBlue, totalGreen, 6, i, j, newImage);
            }
            else if (j == (width - 1))
            {
                totalRed = (WORD) center.rgbtRed + topMiddle.rgbtRed + left.rgbtRed + topLeft.rgbtRed + bottomMiddle.rgbtRed + bottomLeft.rgbtRed;
                totalBlue = (WORD) center.rgbtBlue + topMiddle.rgbtBlue + left.rgbtBlue + topLeft.rgbtBlue + bottomMiddle.rgbtBlue + bottomLeft.rgbtBlue;
                totalGreen = (WORD) center.rgbtGreen + topMiddle.rgbtGreen + left.rgbtGreen + topLeft.rgbtGreen + bottomMiddle.rgbtGreen + bottomLeft.rgbtGreen;
                averageColor(totalRed, totalBlue, totalGreen, 6, i, j, newImage);
            }
            else
            {
                totalRed = (WORD) center.rgbtRed + topMiddle.rgbtRed + left.rgbtRed + topLeft.rgbtRed + bottomMiddle.rgbtRed + bottomLeft.rgbtRed + right.rgbtRed + topRight.rgbtRed + bottomRight.rgbtRed;
                totalBlue = (WORD) center.rgbtBlue + topMiddle.rgbtBlue + left.rgbtBlue + topLeft.rgbtBlue + bottomMiddle.rgbtBlue + bottomLeft.rgbtBlue + right.rgbtBlue + topRight.rgbtBlue + bottomRight.rgbtBlue;
                totalGreen = (WORD) center.rgbtGreen + topMiddle.rgbtGreen + left.rgbtGreen + topLeft.rgbtGreen + bottomMiddle.rgbtGreen + bottomLeft.rgbtGreen + right.rgbtGreen + topRight.rgbtGreen + bottomRight.rgbtGreen;
                averageColor(totalRed, totalBlue, totalGreen, 9, i, j, newImage);
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

void averageColor(WORD totalRed, WORD totalBlue, WORD totalGreen, int divisor, int a, int b, RGBTRIPLE newImage[a][b])
{
    double red = round((double) totalRed / divisor);
    double blue = round((double) totalBlue / divisor);
    double green = round((double) totalGreen / divisor);

    newImage[a][b].rgbtRed = red;
    newImage[a][b].rgbtGreen = green;
    newImage[a][b].rgbtBlue = blue;
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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
            BYTE* redValues = malloc(9 * sizeof(BYTE));
            BYTE* greenValues = malloc(9 * sizeof(BYTE));
            BYTE* blueValues = malloc(9 * sizeof(BYTE));

            redValues[0] = topLeft.rgbtRed;
            redValues[1] = topMiddle.rgbtRed;
            redValues[2] = topRight.rgbtRed;
            redValues[3] = left.rgbtRed;
            redValues[4] = center.rgbtRed;
            redValues[5] = right.rgbtRed;
            redValues[6] = bottomLeft.rgbtRed;
            redValues[7] = bottomMiddle.rgbtRed;
            redValues[8] = bottomRight.rgbtRed;
            WORD redValue = calculations(redValues);

            greenValues[0] = topLeft.rgbtGreen;
            greenValues[1] = topMiddle.rgbtGreen;
            greenValues[2] = topRight.rgbtGreen;
            greenValues[3] = left.rgbtGreen;
            greenValues[4] = center.rgbtGreen;
            greenValues[5] = right.rgbtGreen;
            greenValues[6] = bottomLeft.rgbtGreen;
            greenValues[7] = bottomMiddle.rgbtGreen;
            greenValues[8] = bottomRight.rgbtGreen;
            WORD greenValue = calculations(greenValues);

            blueValues[0] = topLeft.rgbtBlue;
            blueValues[1] = topMiddle.rgbtBlue;
            blueValues[2] = topRight.rgbtBlue;
            blueValues[3] = left.rgbtBlue;
            blueValues[4] = center.rgbtBlue;
            blueValues[5] = right.rgbtBlue;
            blueValues[6] = bottomLeft.rgbtBlue;
            blueValues[7] = bottomMiddle.rgbtBlue;
            blueValues[8] = bottomRight.rgbtBlue;
            WORD blueValue = calculations(blueValues);

            newImage[i][j].rgbtRed = redValue;
            newImage[i][j].rgbtGreen = greenValue;
            newImage[i][j].rgbtBlue = blueValue;
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
    return;
}

WORD calculations(BYTE* values)
{
    int Gx[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int Gy[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    WORD Gxsum = 0;
    WORD Gysum = 0;
    WORD total = 0;
    for (int a = 0; a < 9; a++)
    {
        Gx[a] *= values[a];
        Gxsum += Gx[a];
        Gy[a] *= values[a];
        Gysum += Gy[a];
    }
    Gxsum *= Gxsum;
    Gysum *= Gysum;
    return round(sqrt(Gxsum + Gysum));
}


