#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{   
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            int average = round((float)(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    
    return;
}


// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{   
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            int sepiaRed = round((float)(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen +  0.189 * image[i][j].rgbtBlue));
            int sepiaGreen = round((float)(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen +  0.168 * image[i][j].rgbtBlue));
            int sepiaBlue = round((float)(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen +  0.131 * image[i][j].rgbtBlue));
            
            image[i][j].rgbtRed = sepiaRed > 255 ? 255 : sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue > 255 ? 255 : sepiaBlue;
        }
    }
    return;
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0 ; i < height ; i++)
    {   
        int counter = 0;
        for (int j = (width - 1) ; counter < j ; j--)
        {   
            RGBTRIPLE holder = image[i][counter];
            image[i][counter] = image[i][j];
            image[i][j] = holder;
            counter++;
        }
    }
    
    return;
}





// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imgCopy[height][width];
    float averageRed;
    float averageGreen;
    float averageBlue;

    //Copy the image to imgCopy, not doing so would alter the colors before we blur them;
	for (int row = 0; row < height; row++)
	{
		for (int w = 0; w < width; w++)
		{
			imgCopy[row][w].rgbtRed = image[row][w].rgbtRed;
			imgCopy[row][w].rgbtGreen = image[row][w].rgbtGreen;
			imgCopy[row][w].rgbtBlue = image[row][w].rgbtBlue;


		}
	}

	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{   
            // Corner
			// Top Left
			if (w == 0 && h == 0)
			{
				averageRed = (float)(imgCopy[h][w].rgbtRed + imgCopy[h][w + 1].rgbtRed + imgCopy[h + 1][w].rgbtRed + imgCopy[h + 1][w + 1].rgbtRed) / 4;

				averageGreen = (float)(imgCopy[h][w].rgbtGreen + imgCopy[h][w + 1].rgbtGreen + imgCopy[h + 1][w].rgbtGreen + imgCopy[h + 1][w + 1].rgbtGreen) / 4;

				averageBlue = (float)(imgCopy[h][w].rgbtBlue + imgCopy[h][w + 1].rgbtBlue + imgCopy[h + 1][w].rgbtBlue + imgCopy[h + 1][w + 1].rgbtBlue) / 4;
				averageRed = round(averageRed);
				averageBlue = round(averageBlue);
				averageGreen = round(averageGreen);

				image[h][w].rgbtRed = averageRed;
				image[h][w].rgbtGreen = averageGreen;
				image[h][w].rgbtBlue = averageBlue;
			}
            
			//Lower Left
			else if (w == 0 && h == (height - 1))
			{
				averageRed =(float)(imgCopy[h - 1][w].rgbtRed + imgCopy[h - 1][w + 1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h][w + 1].rgbtRed) / 4;
				averageGreen = (float)(imgCopy[h - 1][w].rgbtGreen + imgCopy[h - 1][w + 1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h][w + 1].rgbtGreen) / 4;
				averageBlue = (float)(imgCopy[h - 1][w].rgbtBlue + imgCopy[h - 1][w + 1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h][w + 1].rgbtBlue) / 4;
				averageRed = round(averageRed);
				averageGreen = round(averageGreen);
				averageBlue = round(averageBlue);

				image[h][w].rgbtRed = averageRed;
				image[h][w].rgbtGreen = averageGreen;
                image[h][w].rgbtBlue = averageBlue;
			}

			//Top Right
			else if (h == 0 && w == (width - 1))
			{
				averageRed = (float)(imgCopy[h][w - 1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h + 1][w - 1].rgbtRed + imgCopy[h + 1][w].rgbtRed)/ 4;

				averageGreen = (float)(imgCopy[h][w - 1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h + 1][w - 1].rgbtGreen + imgCopy[h + 1][w].rgbtGreen) / 4;

				averageBlue = (float)(imgCopy[h][w - 1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h + 1][w - 1].rgbtBlue + imgCopy[h + 1][w].rgbtBlue) / 4;

				averageRed = round(averageRed);
				averageGreen = round(averageGreen);
				averageBlue = round(averageBlue);

				image[h][w].rgbtRed = averageRed;
				image[h][w].rgbtGreen = averageGreen;
                image[h][w].rgbtBlue = averageBlue;
			}

			//Lower Right
			else if(h == (height - 1) && w == (width - 1))
			{
				averageRed = (float)(imgCopy[h - 1][w - 1].rgbtRed + imgCopy[h - 1][w].rgbtRed + imgCopy[h][w - 1].rgbtRed + imgCopy[h][w].rgbtRed) / 4;

		 		averageBlue = (float)(imgCopy[h - 1][w - 1].rgbtBlue + imgCopy[h - 1][w].rgbtBlue + imgCopy[h][w - 1].rgbtBlue + imgCopy[h][w].rgbtBlue) / 4;

				averageGreen = (float)(imgCopy[h - 1][w - 1].rgbtGreen + imgCopy[h - 1][w].rgbtGreen + imgCopy[h][w - 1].rgbtGreen + imgCopy[h][w].rgbtGreen) / 4;

				averageRed = round(averageRed);
				averageGreen = round(averageGreen);
				averageBlue = round(averageBlue);

				image[h][w].rgbtRed = averageRed;
				image[h][w].rgbtGreen = averageGreen;
                image[h][w].rgbtBlue = averageBlue;
			}


            //Edges
            //Left
			else if (w == 0 && (h > 0 && h < height - 1))
			{
				averageRed = (float)(imgCopy[h - 1][w].rgbtRed + imgCopy[h - 1][w + 1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h][w + 1].rgbtRed + imgCopy[h + 1][w].rgbtRed + imgCopy[h + 1][w + 1].rgbtRed) / 6;

				averageGreen = (float)(imgCopy[h - 1][w].rgbtGreen + imgCopy[h - 1][w + 1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h][w + 1].rgbtGreen + imgCopy[h + 1][w].rgbtGreen + imgCopy[h + 1][w + 1].rgbtGreen) / 6;

				averageBlue = (float)(imgCopy[h - 1][w].rgbtBlue + imgCopy[h - 1][w + 1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h][w + 1].rgbtBlue + imgCopy[h + 1][w].rgbtBlue + imgCopy[h + 1][w + 1].rgbtBlue) / 6;

				averageRed = round(averageRed);
				averageGreen = round(averageGreen);
				averageBlue = round(averageBlue);

				image[h][w].rgbtRed = averageRed;
				image[h][w].rgbtGreen = averageGreen;
				image[h][w].rgbtBlue = averageBlue;
			}


            //Right
			else if (w == (width - 1) && (h > 0 && h < height - 1))
			{
				averageRed = (float)(imgCopy[h - 1][w - 1].rgbtRed + imgCopy[h - 1][w].rgbtRed + imgCopy[h][w - 1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h + 1][w - 1].rgbtRed + imgCopy[h + 1][w].rgbtRed) / 6;

				averageGreen = (float)(imgCopy[h - 1][w - 1].rgbtGreen + imgCopy[h - 1][w].rgbtGreen + imgCopy[h][w - 1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h + 1][w - 1].rgbtGreen + imgCopy[h + 1][w].rgbtGreen) / 6;

				averageBlue = (float)(imgCopy[h - 1][w - 1].rgbtBlue + imgCopy[h - 1][w].rgbtBlue + imgCopy[h][w - 1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h + 1][w - 1].rgbtBlue + imgCopy[h + 1][w].rgbtBlue) / 6;

				averageRed = round(averageRed);
				averageGreen = round(averageGreen);
				averageBlue = round(averageBlue);

				image[h][w].rgbtRed = averageRed;
                image[h][w].rgbtGreen = averageGreen;
				image[h][w].rgbtBlue = averageBlue;
			}

            //Top
			else if (h == 0 && (w > 0 &&  w < width - 1))
			{
				averageRed = (float)(imgCopy[h][w - 1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h][w + 1].rgbtRed + imgCopy[h + 1][w - 1].rgbtRed + imgCopy[h + 1][w].rgbtRed + imgCopy[h + 1][w + 1].rgbtRed) / 6;

				averageGreen = (float)(imgCopy[h][w - 1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h][w + 1].rgbtGreen + imgCopy[h + 1][w - 1].rgbtGreen + imgCopy[h + 1][w].rgbtGreen + imgCopy[h + 1][w + 1].rgbtGreen) / 6;

				averageBlue = (float)(imgCopy[h][w - 1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h][w + 1].rgbtBlue + imgCopy[h + 1][w - 1].rgbtBlue + imgCopy[h + 1][w].rgbtBlue + imgCopy[h + 1][w + 1].rgbtBlue) / 6;

				averageRed = round(averageRed);
				averageGreen = round(averageGreen);
				averageBlue = round(averageBlue);

				image[h][w].rgbtRed = averageRed;
				image[h][w].rgbtGreen = averageGreen;
				image[h][w].rgbtBlue = averageBlue;
			}

            //Bottom
			else if  (h == height - 1 && (w > 0 && w < width - 1))
			{
				averageRed = (float)(imgCopy[h - 1][w - 1].rgbtRed + imgCopy[h - 1][w].rgbtRed + imgCopy[h - 1][w + 1].rgbtRed + imgCopy[h][w - 1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h][w + 1].rgbtRed) / 6;
				averageGreen = (float)(imgCopy[h - 1][w - 1].rgbtGreen + imgCopy[h - 1][w].rgbtGreen + imgCopy[h - 1][w + 1].rgbtGreen + imgCopy[h][w - 1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h][w + 1].rgbtGreen) / 6;
				averageBlue = (float)(imgCopy[h - 1][w - 1].rgbtBlue + imgCopy[h - 1][w].rgbtBlue + imgCopy[h - 1][w + 1].rgbtBlue + imgCopy[h][w - 1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h][w + 1].rgbtBlue) / 6;

				averageRed = round(averageRed);
				averageGreen = round(averageGreen);
				averageBlue = round(averageBlue);

				image[h][w].rgbtRed = averageRed;
				image[h][w].rgbtGreen = averageGreen;
				image[h][w].rgbtBlue = averageBlue;
			}

            //Middle
			else
			{
				averageRed = (float)(imgCopy[h - 1][w - 1].rgbtRed + imgCopy[h - 1][w].rgbtRed + imgCopy[h - 1][w + 1].rgbtRed + imgCopy[h][w - 1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h][w + 1].rgbtRed + imgCopy[h + 1][w - 1].rgbtRed + imgCopy[h + 1][w].rgbtRed + imgCopy[h + 1][w + 1].rgbtRed) / 9;
				averageGreen = (float)(imgCopy[h - 1][w - 1].rgbtGreen + imgCopy[h - 1][w].rgbtGreen + imgCopy[h - 1][w + 1].rgbtGreen + imgCopy[h][w - 1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h][w + 1].rgbtGreen + imgCopy[h + 1][w - 1].rgbtGreen + imgCopy[h + 1][w].rgbtGreen + imgCopy[h + 1][w + 1].rgbtGreen) / 9;
                averageBlue = (float)(imgCopy[h - 1][w - 1].rgbtBlue + imgCopy[h - 1][w].rgbtBlue + imgCopy[h - 1][w + 1].rgbtBlue + imgCopy[h][w - 1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h][w + 1].rgbtBlue + imgCopy[h + 1][w - 1].rgbtBlue + imgCopy[h + 1][w].rgbtBlue + imgCopy[h + 1][w + 1].rgbtBlue) / 9;

				averageRed = round(averageRed);
				averageGreen = round(averageGreen);
				averageBlue = round(averageBlue);

				image[h][w].rgbtRed = averageRed;
				image[h][w].rgbtGreen = averageGreen;
				image[h][w].rgbtBlue = averageBlue;
			}

		}
	}
    return;
}