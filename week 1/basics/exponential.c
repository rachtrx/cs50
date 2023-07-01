#include <cs50.h>
#include <stdio.h>

int exponentialfunction(int a, int b)
{
    int counter = b;
    int number = 1;
    while (counter > 0)
    {
        number = number * a;
        counter--;
        // printf("%i\n", number);
    }
    return number;
}

int main(void)
{
    int number = get_int("Enter number: ");
    int exponential = get_int("Enter exponential ");
    int result = exponentialfunction(number, exponential);
    printf("%i\n", result);
}

