#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j;
    double rgb;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            rgb =
                round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0f);
            image[i][j].rgbtBlue = image[i][j].rgbtRed = image[i][j].rgbtGreen = rgb;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image1[1][1];
    int i, j, k;
    for (i = 0; i < height; i++)
    {
        for (j = 0, k = 1; j < width / 2; j++, k++)
        {
            image1[0][0] = image[i][j];
            image[i][j] = image[i][width - k];
            image[i][width - k] = image1[0][0];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image2[height][width];
    int i, j, k, l;
    double RED, BLUE, GREEN;
    float c;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            c = 0.0;
            RED = BLUE = GREEN = 0.0;
            for (k = -1; k < 2; k++)
            {
                for (l = -1; l < 2; l++)
                {
                    int x = i + k, y = j + l;
                    if (x >= 0 && x < height && y >= 0 && y < width)
                    {
                        RED += image[x][y].rgbtRed;
                        BLUE += image[x][y].rgbtBlue;
                        GREEN += image[x][y].rgbtGreen;
                        c++;
                    }
                }
            }
            RED = round(RED / c);
            BLUE = round(BLUE / c);
            GREEN = round(GREEN / c);
            image2[i][j].rgbtRed = RED;
            image2[i][j].rgbtBlue = BLUE;
            image2[i][j].rgbtGreen = GREEN;
        }
    }
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            image[i][j] = image2[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j, k, l, r, c;
    RGBTRIPLE image3[height][width];
    int Gx_r, Gx_b, Gx_g, Gy_r, Gy_b, Gy_g;
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            Gx_r = Gx_b = Gx_g = Gy_r = Gy_b = Gy_g = 0;
            for (k = 0; k < 3; k++)
            {
                r = i + k - 1;
                for (l = 0; l < 3; l++)
                {
                    c = j + l - 1;
                    if (r >= 0 && c >= 0 && r < height && c < width)
                    {
                        Gx_r += image[r][c].rgbtRed * Gx[k][l];
                        Gx_b += image[r][c].rgbtBlue * Gx[k][l];
                        Gx_g += image[r][c].rgbtGreen * Gx[k][l];

                        Gy_r += image[r][c].rgbtRed * Gy[k][l];
                        Gy_b += image[r][c].rgbtBlue * Gy[k][l];
                        Gy_g += image[r][c].rgbtGreen * Gy[k][l];
                    }
                }
            }
            int red = round(sqrt(pow(Gx_r, 2) + pow(Gy_r, 2)));
            int green = round(sqrt(pow(Gx_g, 2) + pow(Gy_g, 2)));
            int blue = round(sqrt(pow(Gx_b, 2) + pow(Gy_b, 2)));
            if (red > 255)
                red = 255;
            if (green > 255)
                green = 255;
            if (blue > 255)
                blue = 255;

            image3[i][j].rgbtRed = red;
            image3[i][j].rgbtGreen = green;
            image3[i][j].rgbtBlue = blue;
        }
    }
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            image[i][j] = image3[i][j];
        }
    }
    return;
}
