#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through image
    for (int i = 0; i < height; i++)
    {
        for (int n = 0; n < width; n++)
        {
            // For each pixel, calculate average of red, green and blue. Cast to float before divinding by 3
            // Round to nearest integer
            BYTE average = round((float)(image[i][n].rgbtBlue + image[i][n].rgbtGreen + image[i][n].rgbtRed) / 3);
            image[i][n].rgbtBlue = average;
            image[i][n].rgbtGreen = average;
            image[i][n].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int n = 0; n < width / 2; n++)
        {
            // Loop through image and swap each pixel on the left side with pixel on right side of the image
            // Only loops through half of the image in the x direction
            RGBTRIPLE pixel = image[i][width - 1 - n];
            image[i][width - 1 - n] = image[i][n];
            image[i][n] = pixel;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurredImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int n = 0; n < width; n++)
        {
            int grid[3] = {-1, 0, 1}; // Array holding the indexes for the pixels in the grid around each pixel
            int count = 0; // Counting how many pixels are in the grid around each pixel. (To calculate average)
            float blueValue = 0;
            float greenValue = 0;
            float redValue = 0;
            // Looping through the grid and add red, green and blue values for each pixel in the grid
            for (int y = 0; y < 3; y++)
            {
                // Skip if the grid is outside the edge of the image
                if (i + grid[y] < 0 || i + grid[y] > height - 1)
                {
                    continue;
                }
                for (int x = 0; x < 3; x++)
                {
                    if (n + grid[x] < 0 || n + grid[x] > width - 1)
                    {
                        continue;
                    }
                    blueValue += image[i + grid[y]][n + grid[x]].rgbtBlue;
                    greenValue += image[i + grid[y]][n + grid[x]].rgbtGreen;
                    redValue += image[i + grid[y]][n + grid[x]].rgbtRed;
                    count++;
                }
            }
            // Calculate average and round to nearest integer
            blurredImage[i][n].rgbtBlue = round(blueValue / count);
            blurredImage[i][n].rgbtGreen = round(greenValue / count);
            blurredImage[i][n].rgbtRed = round(redValue / count);
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int n = 0; n < width; n++)
        {
            image[i][n] = blurredImage[i][n];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE edgeImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int n = 0; n < width; n++)
        {
            int grid[3] = {-1, 0, 1}; // Array representing the grid of pixels around each pixel in the image
            int xGrid[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}}; // Array representing gx grid
            int yGrid[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}}; // Array representing gy grid
            int gxRed = 0, gxBlue = 0, gxGreen = 0, gyRed = 0, gyBlue = 0, gyGreen = 0;
            
            // Looping through grid of pixels around each pixel in the image
            for (int y = 0; y < 3; y++)
            {
                // Skip in the pixel is outside edge of image
                if (i + grid[y] < 0 || i + grid[y] > height - 1)
                {
                    continue;
                }
                for (int x = 0; x < 3; x++)
                {
                    if (n + grid[x] < 0 || n + grid[x] > width - 1)
                    {
                        continue;
                    }
                    // Add red, green and blue values from each pixel in the grid divided by corresponding
                    // value in the gx and gy grid
                    gxBlue += (image[i + grid[y]][n + grid[x]].rgbtBlue * xGrid[1 + grid[y]][1 + grid[x]]);
                    gxGreen += (image[i + grid[y]][n + grid[x]].rgbtGreen * xGrid[1 + grid[y]][1 + grid[x]]);
                    gxRed += (image[i + grid[y]][n + grid[x]].rgbtRed * xGrid[1 + grid[y]][1 + grid[x]]);
                    gyBlue += (image[i + grid[y]][n + grid[x]].rgbtBlue * yGrid[1 + grid[y]][1 + grid[x]]);
                    gyGreen += (image[i + grid[y]][n + grid[x]].rgbtGreen * yGrid[1 + grid[y]][1 + grid[x]]);
                    gyRed += (image[i + grid[y]][n + grid[x]].rgbtRed * yGrid[1 + grid[y]][1 + grid[x]]);
                }
            }
            // Calculate hypotenuse
            // If value above 255, set to 255
            int blue = round(sqrt(pow(gxBlue, 2) + pow(gyBlue, 2)));
            int green = round(sqrt(pow(gxGreen, 2) + pow(gyGreen, 2)));
            int red = round(sqrt(pow(gxRed, 2) + pow(gyRed, 2)));
            if (blue > 255)
            {
                blue = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (red > 255)
            {
                red = 255;
            }
            edgeImage[i][n].rgbtBlue = blue;
            edgeImage[i][n].rgbtGreen = green;
            edgeImage[i][n].rgbtRed = red;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int n = 0; n < width; n++)
        {
            image[i][n] = edgeImage[i][n];
        }
    }
    return;
}
