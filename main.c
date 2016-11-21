#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main()
{
    GCD();
    SieveOfEratosthenes();
    return 0;
}

void swap( int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
    return;
}

void SieveOfEratosthenes()
{
    int k, n, count = 0;
    printf("Enter the number you want to find all prime numbers up to:\n");
    scanf(" %d", &n);
    int primes[n];
    int i, j;
    for (i = 0; i < n; i++)
    {
        primes[i] = 1; // we initialize the sieve list to all 1's (True)
    }
    primes[0] = 0, primes[1] = 0; // Set the first two numbers (0 and 1) to 0 (False)
    for (i = 2; i < sqrt(n); i++)
    {// loop through all the numbers up to the sqrt(n)
        for (j = i * i; j < n;j += i)
        {// mark off each factor of i by setting it to 0 (False)
            primes[j] = 0;
        }
    }
    for (k = 0; k < n; k++)
    {
        if (primes[k] == 1)
        {
            count++;
            printf("%d\n",k); // this just prints out each value if it's Prime
        }
    }
    printf("There are %d prime numbers up to %d\n", count, n);
}
void GCD()
{
    int x, y;
    printf("Enter number to get Greatest Common Divider:\n");
    scanf(" %d , %d", &x, &y);
    int result = EuclidAlgorithm(x,y);
    printf("%d\n", result);
}
int EuclidAlgorithm(int a, int b)
{
    if(b==0)
    {
        return a;
    }
    else
    {
        return EuclidAlgorithm(b,a%b);
    }
}
