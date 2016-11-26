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
#define GradeRange 100
#define MinGrade 0

/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
int GradeNum (int grades [])
{
    int count = 0;
    for(int i = 0; i < GradeRange+1; i++)
    {
        if(grades[i] > 0)
        {
            count += grades[i];
        }
    }
    return count;
}

int Max (int grades [])
{
    int max = 0;
    for (int i = 0; i < GradeRange+1; i++)
    {
        if(grades[i] > 0 && i > max)
        {
            max = i;
        }
    }
    return max;
}

int Min (int grades [])
{
    int min = 100;
    for(int i = GradeRange; i > -1; i--)
    {
        if(grades[i] > 0 && i < min)
        {
            min = i;
        }
    }
    return min;
}

int Median (int grades[])
{
    int median = -1, i =0;
    while(i <= GradeNum(grades) / 2)
    {
        ++median;
        i += grades[median];
    }
    return median;
}

int BiggerGrades (int grade, int grades [])
{
    int count = 0;
    for(int i = grade + 1; i < GradeRange+1; i++)
    {
        count += grades[i];
    }
    return count;
}

int SmallerGrades (int grade, int grades [])
{
    int count = 0;
    for(int i = grade - 1; i > -1; i--)
    {
        count += grades[i];
    }
    return count;
}

/*int Factor(int pass_grade, int percentage, int grades[])//WIP
{
    int i = 0, count = 0, relativeMedianIndex, relativeMedian, position = 0;
    for(;i < GradeRange; i++)
    {
        count += grades[i];
    }
   if(count % 2 == 0)
   {
        relativeMedianIndex = ((((double)percentage / GradeRange) * (count)) + ((((double)percentage / GradeRange) * (count)) +1))/2;
   }
   else
   {
        relativeMedianIndex = ((double)percentage / GradeRange) * (count+1);
   }
    for(int j = 0; j < GradeRange && position < relativeMedianIndex; j++)
    {
        if(grades[j] > 0)
        {
            position += grades[j];
        }
    }
    if(grades[j] < )
}
*/
int Average(int grades [])
{
    int sum = 0, count = 0, avg, temp, i;
    for(i = 0; i < GradeRange+1; i++)
    {
        temp = i * grades[i];
        if(temp != 0 || i == 0)
        {
            sum += temp;
            count += grades[i];
        }
    }
    avg = ((double)sum / count) + 0.5;
    return avg;
}
int main()
{
    int Grades[GradeRange+1] = {0};
    int x;
    scanf(" %d", &x);
    while(x != -1)
    {
        if(x <= GradeRange && x >= MinGrade)
        {
            Grades[x]++;
        }
        scanf(" %d", &x);
    }
    //printf("%d", Factor(3,50, Grades));
    char c;
    int Grade;
    while(true)
    {
        scanf(" %c", &c);
        switch(c)
        {
            case 'V' :
                printf("%d\n", Average(Grades));
                break;
            case 'X' :
                printf("%d\n", Max(Grades));
                break;
            case 'I' :
                printf("%d\n", Min(Grades));
                break;
            case 'M' :
                printf("%d\n", Median(Grades));
                break;
            case 'A' :
                scanf(" %d", &Grade);
                printf("%d\n", BiggerGrades(Grade, Grades));
                break;
            case 'B' :
                scanf(" %d", &Grade);
                printf("%d\n", SmallerGrades(Grade, Grades));
                break;
            /*case 'F' :
                scanf(" %d %d", &firstVal, &secondVal);
                printf("%d\n", Factor(firstVal, secondVal, Grades));
                break;*/
            default:
                printf("This command is not currently supported by the system.\n");
        }
    }
  return 0;
}
