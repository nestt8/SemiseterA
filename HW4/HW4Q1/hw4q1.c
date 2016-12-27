/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>



/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/
#define M 50


/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
void compute_integral_image(int image[][M], int n, int m,
                            int integral_image[][M])
 {
     int sumLeft = 0, sumUp = 0;
     for(int i = 0; i < n; i++)
     {
         for(int j = 0; j < m; j++)
         {
             if(i > 0)
             {
                 sumUp = integral_image[i-1][j];
             }
             if(i == 0 && j ==0)
             {
                 integral_image[i][j] = image[i][j];
                 sumLeft += image[i][j];
             }
             else
             {
                integral_image[i][j] = sumLeft + image[i][j] + sumUp;
                sumLeft += image[i][j];
             }
         }
         sumLeft = 0;
     }
 }

 int sum_rect(int integral_image[][M], int rect[4])
 {
     int sum = integral_image[rect[2]][rect[3]] -
     integral_image[rect[0] - 1][rect[3]] -
     integral_image[rect[2]][rect[1] - 1] +
     integral_image[rect[0] - 1][rect[1] - 1];
     return sum;
 }
void sliding_average(int image[][M], int n, int m, int h, int w,
                     int average[][M])
{
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {

        }
    }
}

int main()
{
    int Image[4][50] = {{1, 6, 8, 3},{0, 0, 3, 7}, {4, 7, 8, 8},
    {5, 0, 9, 9}};
    int IntegralImage[4][50];
    int Rect[4] = {1, 1, 3, 2};
    compute_integral_image(Image, 4, 4, IntegralImage);
    for(int i = 0; i < 4; i++)
     {
         for(int j = 0; j < 4; j++)
         {
             printf("%d ", IntegralImage[i][j]);
         }
         printf("\n");
     }
     printf("%d\n", sum_rect(IntegralImage, Rect));
  return 0;
}
