#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

/* DEFINEs*/
/* -------------------------------------------------------- */

/* MAX_EXPRESSION_LENGTH does not include the terminating null character */
#define MAX_EXPRESSION_LENGTH 255


/* FUNCTIONS */
/* -------------------------------------------------------- */


 int char2dig(char ch)
 {
     return ch - '0';
 }

 bool RecuriveCalcualteModular(unsigned int modulus, char* expression, unsigned int* expression_result)
 {
 unsigned long long LeftNumber = 0, RightNumber = 0;
    char Operand = ' ';
    bool OperandSeen = false;
    while(*expression)
    {
        if(!OperandSeen)
        {
            if(*expression > '0' && *expression < '9')
            {
                LeftNumber = LeftNumber * 10 + char2dig(*expression);
            }
            else if(*expression == '+' || *expression == '*')
            {
                Operand = *expression;
                OperandSeen = true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if(*expression > '0' && *expression < '9')
            {
                RightNumber = RightNumber * 10 + char2dig(*expression);
            }
            else
            {
                return false;
            }
        }
    }
    if(Operand == '+')
    {
        *expression_result = ((LeftNumber % modulus) + (RightNumber % modulus) % modulus);
    }
    else if(Operand == '*')
    {
        *expression_result = ((LeftNumber % modulus) * (RightNumber % modulus) % modulus);
    }
    return true;
 }
/*
   calculate_modular_expression - calculates a modular expression in the form
   (
*/
 bool calculate_modular_expression(unsigned int modulus, char* expression, unsigned int* expression_result)
 {

    return true;
 }


/*
   get_input - Gets program input (modulus, expression) from standard input.
   This function prints a message to the standard output and gets the input
   (modulus, expression) from standard input.
   This function does not validate the inputs other than basic validation.
   Inputs: modulus_ptr - pointer where the function stores the modulus.
           expression - pointer to an array of character where the function
           stores the expression string.
   Returns true if and only if the function gets the inputs successfully.
*/
 bool get_input(unsigned int* modulus_ptr, char* expression)
 {
    printf("Please enter the modulus and an expression (separated by a space).\n");
    return (scanf("%u%s", modulus_ptr, expression) == 2);
 }


/*
   validate_input - Validates program input (modulus).
   Returns true if and only if the input is valid.
*/
 bool validate_input(unsigned int modulus)
 {
    /* The modulus must be greater than 1 */
    return (modulus > 1);
 }


/*
   main function.
   Inputs: none.
   Returns 0 when the program run successfully.
   Any other value indicates an error.
*/
 int main()
 {
    unsigned int modulus; /* modulus */
    char expression[MAX_EXPRESSION_LENGTH+1];
    unsigned int expression_result;

    if (!get_input(&modulus, expression)) {
        printf("ERROR: could not get input\n");
        return 1;
    }

    if (!validate_input(modulus)) {
        printf("ERROR: modulus is out of range\n");
        return 2;
    }

    if (!calculate_modular_expression(modulus, expression, &expression_result)) {
        printf("ERROR: the modular expression is invalid\n");
        return 3;
    }

    printf("%u\n", expression_result);

    return 0;
 }
