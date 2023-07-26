#include <stdio.h>

/**
 * factorial - Calculates the factorial of a given number
 * @n: The number to calculate the factorial of
 *
 * Return: The factorial of n, or -1 if n is negative
 */
int factorial(int n)
{
    if (n < 0)
    {
        return (-1);
    }
    if (n == 0)
    {
        return (1);
    }
    return (n * factorial(n - 1));
}

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    int n = 5;
    int result = factorial(n);

    printf("%d! = %d\n", n, result);
    return (0);
}
