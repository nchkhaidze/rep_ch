#include "helpers.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool in_bounds(int h, int w, int height, int width);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float average = round(((float)image[h][w].rgbtBlue + (float)image[h][w].rgbtGreen + (float)image[h][w].rgbtRed) / 3);
            image[h][w].rgbtBlue = average;
            image[h][w].rgbtGreen = average;
            image[h][w].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        int halfwidth = round((float)0.5 * width);
        for (int w = 0; w < halfwidth; w++)
        {
            RGBTRIPLE first = image[h][w];
            image[h][w] = image[h][width - 1 - w];
            image[h][width - 1 - w] = first;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //create a copy of the original image so that already filtered pixels do not affect the unfiltered ones
    RGBTRIPLE(*original)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (original == NULL)
    {
        fprintf(stderr, "Not enough memory to store image\n");
        return;
    }
    memcpy(original, image, (height * width * sizeof(RGBTRIPLE)));

    //scroll through every pixel
    const int max_neighbors = 9;
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //find neighbors of a pixel and put them into array
            int neighbor_count = 0;
            RGBTRIPLE neighbors[max_neighbors];
            for (int hn = -1; hn < 2; hn++)
            {
                for (int wn = -1; wn < 2; wn++)
                {
                    //check if the neighbor pixels are within bounds
                    if (in_bounds((h + hn), (w + wn), height, width))
                    {
                        neighbors[neighbor_count] = original[h + hn][w + wn];
                        neighbor_count++;
                    }
                }
            }

            //calculate rgb values based on neighbors
            float average[3] = {0, 0, 0};
            for (int i = 0; i < neighbor_count; i++)
            {
                average[0] = average[0] + neighbors[i].rgbtRed;
                average[1] = average[1] + neighbors[i].rgbtGreen;
                average[2] = average[2] + neighbors[i].rgbtBlue;
            }
            image[h][w].rgbtRed = round(average[0] / (float)neighbor_count);
            image[h][w].rgbtGreen = round(average[1] / (float)neighbor_count);
            image[h][w].rgbtBlue = round(average[2] / (float)neighbor_count);
        }
    }
    free(*original);

    return;
}

//check if the neighbor pixel is in bounds
bool in_bounds(int h, int w, int height, int width)
{
    if (((h < 0) || (w < 0)) || ((h > height - 1) || (w > width - 1)))
    {
        return false;
    }
    return true;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //create a copy of the original image so that already filtered pixels do not affect the unfiltered ones
    RGBTRIPLE(*original)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (original == NULL)
    {
        fprintf(stderr, "Not enough memory to store image\n");
        return;
    }
    memcpy(original, image, (height * width * sizeof(RGBTRIPLE)));

    //scroll through every pixel
    int Gx_kernel[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int Gy_kernel[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int kernel_count = 0;
            int Gx[3] = {0, 0, 0};
            int Gy[3] = {0, 0, 0};
            for (int hn = -1; hn < 2; hn++)
            {
                for (int wn = -1; wn < 2; wn++)
                {
                    if (!in_bounds(h + hn, w + wn, height, width))
                    {
                        break;
                    }
                    Gx[0] = Gx[0] + (original[h + hn][w + wn].rgbtRed * Gx_kernel[kernel_count]);
                    Gx[1] = Gx[1] + (original[h + hn][w + wn].rgbtGreen * Gx_kernel[kernel_count]);
                    Gx[2] = Gx[2] + (original[h + hn][w + wn].rgbtBlue * Gx_kernel[kernel_count]);

                    Gy[0] = Gy[0] + (original[h + hn][w + wn].rgbtRed * Gy_kernel[kernel_count]);
                    Gy[1] = Gy[1] + (original[h + hn][w + wn].rgbtGreen * Gy_kernel[kernel_count]);
                    Gy[2] = Gy[2] + (original[h + hn][w + wn].rgbtBlue * Gy_kernel[kernel_count]);

                    kernel_count++;
                }
            }
            double check_cap = sqrt(pow(Gx[0], 2) + pow(Gy[0], 2));
            if (check_cap > 255)
            {
                check_cap = 255;
            }
            image[h][w].rgbtRed = (int)sqrt(pow(Gx[0], 2) + pow(Gy[0], 2));

            check_cap = sqrt(pow(Gx[1], 2) + pow(Gy[1], 2));
            if (check_cap > 255)
            {
                check_cap = 255;
            }
            image[h][w].rgbtGreen = (int)sqrt(pow(Gx[1], 2) + pow(Gy[1], 2));

            check_cap = sqrt(pow(Gx[2], 2) + pow(Gy[2], 2));
            if (check_cap > 255)
            {
                check_cap = 255;
            }
            image[h][w].rgbtBlue = (int)sqrt(pow(Gx[2], 2) + pow(Gy[2], 2));
        }
    }
}
