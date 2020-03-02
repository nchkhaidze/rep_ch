#include "helpers.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

bool in_bounds(int h, int w, int height, int width);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float average = (image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / 3;
            image[h][w].rgbtBlue = average;
            image[h][w].rgbtGreen = average;
            image[h][w].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int sepiaRed, sepiaGreen, sepiaBlue;
            sepiaRed = round(image[h][w].rgbtRed * 0.393 + image[h][w].rgbtGreen * 0.769 + image[h][w].rgbtBlue * 0.189);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            sepiaGreen = round(image[h][w].rgbtRed * 0.349 + image[h][w].rgbtGreen * 0.686 + image[h][w].rgbtBlue * 0.168);
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            sepiaBlue = round(image[h][w].rgbtRed * 0.272 + image[h][w].rgbtGreen * 0.534 + image[h][w].rgbtBlue * 0.131);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[h][w].rgbtRed = sepiaRed;
            image[h][w].rgbtGreen = sepiaGreen;
            image[h][w].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < (width / 2); w++)
        {
            RGBTRIPLE first = image[h][w];
            image[h][w] = image[h][width - w];
            image[h][width - w] = first;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            RGBTRIPLE neighbors[9];
            int neighbor_count = 0;
            for (int hn = -1; hn < 2; hn++)
            {
                for (int wn = -1; wn < 2; wn++)
                if (in_bounds((h + hn),(w + wn), height, width))
                {
                    neighbors[neighbor_count].rgbtRed = image[h + hn][w + wn].rgbtRed;
                    neighbors[neighbor_count].rgbtGreen = image[h + hn][w + wn].rgbtGreen;
                    neighbors[neighbor_count].rgbtBlue = image[h + hn][w + wn].rgbtBlue;
                    neighbor_count++;
                }
            }
            int average[3] = {0, 0, 0};
            for (int i = 0; i < neighbor_count; i++)
            {
                average[0] = average[0] + neighbors[i].rgbtRed;
                average[1] = average[1] + neighbors[i].rgbtGreen;
                average[2] = average[2] + neighbors[i].rgbtBlue;
            }
            image[h][w].rgbtRed = average[0] / neighbor_count;
            image[h][w].rgbtGreen = average[1] / neighbor_count;
            image[h][w].rgbtBlue = average[2] / neighbor_count;
        }
    }

    return;
}

bool in_bounds(int h, int w, int height, int width)
{
    if (((h < 0) || (w < 0)) || ((h > height) || (w > width)))
    {
        printf("false\n ");
        return false;
    }
    return true;
}
