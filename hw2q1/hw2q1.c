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
    int TaxBrackets [2*N + 2] = {0};
    for(int i = 2; i < 2*N + 2; i++)
    {
        if(scanf(" %d", &TaxBrackets[i]) != 1)
        {
            return 1;
        }
    }
    printf("Please, enter your ID and your last 12 salaries:\n");
    int ID;
    int Salaries[NumOfMonths] = {0};
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
        for(int k = 2; k < (2*N)+1 && Salary > 0; k += 2)
        {
            bool y = ((!CheckID(IDArray)) && (TaxSum += Salary) && (Salary = 0))
            || ((Salary <= (TaxBrackets[k] - TaxBrackets[k-2])) && (TaxSum += Salary * (TaxBrackets[k+1] / 100.0)))
            || ((k == 2*N) && (TaxSum += Salary * (TaxBrackets[k+1] / 100.0)))
            || (((TaxSum += (TaxBrackets[k] - TaxBrackets[k-2]) * (TaxBrackets[k+1] / 100.0))));
            y = ((Salary -= TaxBrackets[k] - TaxBrackets[k-2]));
            y = !y;
        }
    }
printf("Total tax:\t%d\n", (int)(TaxSum + 0.5));
  return 0;
}
