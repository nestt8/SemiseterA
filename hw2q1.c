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
#define N 5
#define NumOfMonths 12
#define IDLength 9

/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/

void IDArrayInit(int Id, int IdArray [IDLength])
{
    for(int i = IDLength-1; i > -1; i--)
    {
        IdArray[i] = Id % 10;
        Id /= 10;
    }
    return;
}

bool CheckID (int IdArray [IDLength])
{
    int sum = 0;
    for(int i = 0; i < 4; i++)
    {
        sum += (IdArray[i] + IdArray[i+4]) % (4 + i);
    }
    while(IdArray[IDLength-1] != sum % 10)
    {
        return false;
    }
    return true;
}

int main()
{
    int TaxBrackets [2*N];
    for(int i = 0; i < 2*N; i++)
    {
        if(scanf(" %d", &TaxBrackets[i]) != 1)
        {
            return 1;
        }
    }
    printf("Please, enter your ID and your last 12 salaries:\n");
    int ID;
    int Salaries[NumOfMonths];
    scanf(" %d", &ID);
    for(int j = 0; j < NumOfMonths; j++)
    {
        if(scanf(" %d", &Salaries[j]) != 1)
        {
            return 1;
        }
    }
    int IDArray [IDLength] = {0};
    IDArrayInit(ID, IDArray);
    double TaxSum = 0.0;
    int Salary = 0;
    for(int l = 0; l < NumOfMonths; l++)
    {
        Salary = Salaries[l];
        /*bool x = ((!CheckID(IDArray) == true) && (TaxSum += Salaries[l]))
        || ((CheckID(IDArray) == true) && (Salaries[l] <= TaxBrackets[0]) && (Salaries[l] > 0) && (TaxSum += Salaries[l] * (TaxBrackets[1] / 100.0)))
        || ((CheckID(IDArray) == true) && (Salaries[l] > TaxBrackets[0]) && (Salaries[l] <= TaxBrackets[2]) && (TaxSum += (TaxBrackets[0] * (TaxBrackets[1] / 100.0) +
            (Salaries[l] - TaxBrackets[0]) * (TaxBrackets[3] / 100.0))))
        || ((CheckID(IDArray) == true) && (Salaries[l] > TaxBrackets[2]) && (Salaries[l] <= TaxBrackets[4]) && (TaxSum += (TaxBrackets[0] * (TaxBrackets[1] / 100.0)) +
            ((TaxBrackets[2] - TaxBrackets[0]) * (TaxBrackets[3] / 100.0)) + (Salaries[l] - TaxBrackets[2]) * (TaxBrackets[5] / 100.0)))
        || ((CheckID(IDArray) == true) && (Salaries[l] > TaxBrackets[4]) && (Salaries[l] <= TaxBrackets[6]) && (TaxSum += (TaxBrackets[0] * (TaxBrackets[1] / 100.0)) +
            ((TaxBrackets[2] - TaxBrackets[0]) * (TaxBrackets[3] / 100.0)) + ((TaxBrackets[4]-TaxBrackets[2]) * (TaxBrackets[5] / 100.0)) + (Salaries[l] - TaxBrackets[4]) * (TaxBrackets[7] / 100.0)))
        || ((CheckID(IDArray) == true) && (Salaries[l] > TaxBrackets[6]) && (TaxSum += (TaxBrackets[0] * (TaxBrackets[1] / 100.0)) +
            ((TaxBrackets[2] - TaxBrackets[0]) * (TaxBrackets[3] / 100.0)) + ((TaxBrackets[4] - TaxBrackets[2]) * (TaxBrackets[5] / 100.0)) + ((TaxBrackets[6] - TaxBrackets[4]) * (TaxBrackets[7] / 100.0)) +
            (Salaries[l] - TaxBrackets[6]) * (TaxBrackets[9] / 100.0)));
        x = !x;*/
        for(int k = 0; k < (2*N)-1 && Salary > 0; k += 2)
        {
            bool y = ((!CheckID(IDArray) == true) && (TaxSum += Salaries[l]) && (Salary = 0))
            || (((k == 0) && (Salary - TaxBrackets[k]) <= 0) && (TaxSum += Salary * (TaxBrackets[k+1] / 100.0)))
            || (((k == 0) && (Salary - TaxBrackets[k]) > 0) && (TaxSum += TaxBrackets[k] * (TaxBrackets[k+1] / 100.0)))
            || (((k != 0) && (Salary - (TaxBrackets[k] - TaxBrackets[k-2]) <= 0) && (TaxSum += Salary * (TaxBrackets[k+1] / 100.0))))
            || (((k != 0) && (Salary - (TaxBrackets[k] - TaxBrackets[k-2]) > 0) && (TaxSum += Salary - (Salary - (TaxBrackets[k] - TaxBrackets[k-2]) * (TaxBrackets[k+1] / 100.0)))));
            y = ((k == 0) && (Salary -= TaxBrackets[k])) || ((Salary -= TaxBrackets[k] - TaxBrackets[k-2]));
            y = !y;
        }
    }
printf("Total tax:\t%d\n", (int)(TaxSum + 0.5));
  return 0;
}
