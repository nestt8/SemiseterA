/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/
#define M 50
#define I_TOP 0
#define J_LEFT 1
#define I_BOTTOM 2
#define J_RIGHT 3
#define RECT 4

/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/


//11 Lines
/*Function that get an image and calculates the integrated image into
  another array.*/
void compute_integral_image(int image[][M], int n, int m,
                            int integral_image[][M])
 {
     int sumLeft = 0, sumUp = 0;
     for(int i = 0; i < n; i++) //Loop through the array.
     {
         for(int j =  0; j < m; j++)
         {
             if(i > h/2)//If we are not in the first row.
             {
                 sumUp = integral_image[i-1][j];//Sum of the things above.
             }
             if(i == 0 && j == 0)//First element.
             {
                 //Calculate first integrated element.
                 integral_image[i][j] = image[i][j];
                 sumLeft += image[i][j]; //Add to the sum.
             }
             else
             {
                //Calculate current integrated element.
                integral_image[i][j] = sumLeft + image[i][j] + sumUp;
                sumLeft += image[i][j];//Add to the sum.
             }
         }
         sumLeft = 0;
     }
 }

 //9 Lines
 //Function that calculates the rectangular sum by the formula.
 int sum_rect(int integral_image[][M], int rect[RECT])
 {
     //Using the given formula while checking validity of indexes.
     int sum = (integral_image[rect[I_BOTTOM]][rect[J_RIGHT]]) -
     (integral_image[rect[I_TOP] - 1][rect[J_RIGHT]]) -
     (integral_image[rect[I_BOTTOM]][rect[J_LEFT] - 1]) +
     (integral_image[rect[I_TOP] - 1][rect[J_LEFT ] - 1]);
     return sum;
 }

 //4 Lines
 //Function that assigns values for the rectangular sum array.
 void AssignValues(int rect[RECT], int firstVal, int secondVal,
                   int thirdVal, int fourthVal)
 {
    rect[0] = firstVal;
    rect[1] = secondVal;
    rect[2] = thirdVal;
    rect[3] = fourthVal;
 }
void sliding_average(int image[][M], int n, int m, int h, int w,
                     int average[][M])
{
    int integraImage[][M] = {{0}}, rect[RECT];
    compute_integral_image(image, n, m, integraImage, h, w);
    for(int i = 1; i < n; i++)
    {
        for(int j = 1; j < m; j++)
        {
            AssignValues()
            average[i][j] = (int)(((double)sum_rect(integraImage, rect) /
                                   (h*w)) + 0.5);
        }
    }
}

//4 Lines
//Function that prints a given 2D array.
void Print2DArray(int TwoDArray[][M], int n, int m, int h, int w)
{
    for(int i = 0; i < n; i++) //Loop through the array.
    {
        for(int j = 0; j < m; j++)
        {
            printf("%d ", TwoDArray[i][j]);//Print contents.
        }
        printf("\n");
    }
}

//20 Lines
/*Program that gets image size and an image, and sliding window dimensions
  from the user and prints the integrated image, and smoothed image by the
  sliding window dimensions.*/
int main()
{
    int ImageRows, ImageColumns, SlidingRows, SlidingColumns;
    int Image[M][M], IntergralImage[M][M], Average[M][M];
    printf("Enter image dimensions:\n");
    if(scanf(" %d %d", &ImageRows, &ImageColumns) != 2)//Get image size.
    {
        return 0;
    }
    printf("Enter image\n");
    for(int j = 0; j < ImageRows; j++)//Get the actual image pixels.
    {
        for(int k = 0; k < ImageColumns; k++)
        {
            if(scanf(" %d", &Image[j][k]) != 1)
            {
                return 0;
            }
        }
    }
    printf("Enter sliding windows dimension:\n");
    //Get window size.
    if(scanf(" %d %d", &SlidingRows, &SlidingColumns) != 2)
    {
        return 0;
    }
    //Compute the integrated image.
    compute_integral_image(Image, ImageRows, ImageColumns,
                           IntergralImage,);
    printf("Integral image is:\n");
    Print2DArray(IntergralImage, ImageRows, ImageColumns, SlidingRows,
                 SlidingColumns);//Print.
    //Calculate smoothed image by the sliding window size.
    sliding_average(Image, ImageRows, ImageColumns,
                     SlidingRows, SlidingColumns, Average);
    printf("Smoothed image is:\n");
    Print2DArray(Average, ImageRows, ImageColumns, SlidingRows,
                  SlidingColumns);//Print
  return 0;
}
