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
int GradeNum (int grades []) //Function that finds the actual number of grades entered.
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

int Max (int grades []) //Function that finds the highest grade, if there are no grades returns 0.
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

int Min (int grades []) //Function that finds the lowest grade, if there are no grades returns 100.
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

int Median (int grades[]) //Function that finds the median.
{
    int median = -1, i =0;
    while(i <= GradeNum(grades) / 2)
    {
        ++median;
        i += grades[median];
    }
    return median;
}

int BiggerGrades (int grade, int grades []) //Function that finds the number of grades higher than a given grade.
{
    int count = 0;
    for(int i = 0; i < GradeRange+1; i++)
    {
        if(i > grade)
        {
            count += grades[i];
        }
    }
    return count;
}

int SmallerGrades (int grade, int grades []) //Function that finds the number of grades lower than a given grade.
{
    int count = 0;
    for(int i = 100; i > -1; i--)
    {
        if(i < grade)
        {
            count += grades[i];
        }
    }
    return count;
}

int Factor(int passgrade, int percentage, int grades []) //Function that gets a passing grade and percentage and returns what factor is needed so the given percentage of students
{
    int relativeMedian = 101, i = 0, gradeNum = GradeNum(grades);
    if (passgrade > 100 || passgrade < 0 || percentage > 100 || percentage < 0 )
    {
        return 0;
    }
    while(i < (gradeNum * ((double)percentage / 100)))
    {
        --relativeMedian;
        i += grades[relativeMedian];
    }
    if (relativeMedian >= passgrade)
    {
        return 0;
    }
    else
    {
        return (passgrade - relativeMedian);
    }

}

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
    while(x != -1) //Loop to receive the grades and add them to the array.
    {
        if(x <= GradeRange && x >= MinGrade)
        {
            Grades[x]++;
        }
        scanf(" %d", &x);
    }
    char c;
    int Grade, passGrade, Percentage;
    while(true) //Infinite loop to receive commands from user and run the corresponding functions.
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
                if(scanf(" %d", &Grade) == 1)
                {
                    printf("%d\n", BiggerGrades(Grade, Grades));
                }
                break;
            case 'B' :
                if(scanf(" %d", &Grade) == 1)
                {
                    printf("%d\n", SmallerGrades(Grade, Grades));
                }
                break;
            case 'F' :
                if(scanf(" %d %d", &passGrade, &Percentage) == 2)
                {
                    printf("%d\n", Factor(passGrade, Percentage, Grades));
                }
                break;
            default:
                printf("This command is not currently supported by the system.\n");
        }
    }
  return 0;
}
