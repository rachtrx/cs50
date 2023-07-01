#include <cs50.h>
#include <stdio.h>

int lengthOfNumber(long a);
long exponentialfunction(int a, int b);
int getFirstDigit(int remainderLength, long remainder);

int main(void)
{
    // prompt for number
    long number = get_long("Number: ");

    // get length of number
    int length = lengthOfNumber(number);
    printf("%i\n", length);

    // get the product of every other digit
    int remainderLength;

    if (length % 2 != 0)
    {
        remainderLength = length - 1;
    }
    else
    {
        remainderLength = length;
    }
    int totalDigit = 0;

    while (remainderLength > 0)
    {
        long firstQuotient = exponentialfunction(10, remainderLength);
        long remainder = number % firstQuotient;
        printf("Number: %li, First quotient: %li, Remainder: %li, Remainder Length: %i\n", number, firstQuotient, remainder, remainderLength);
        if (remainderLength > 1)
        {
            int digit = getFirstDigit(remainderLength, remainder);
            int doubleDigit = 2 * digit;
            int firstDigit = doubleDigit / 10
            int secondDigit = doubleDigit % 10
            }
            totalDigit = totalDigit + firstDigit + secondDigit;
        }
        remainderLength -= 2;
    }
    printf("Total digits: %i\n", totalDigit);

    // add the other digits

    // check for validity

    // check for type of card if valid
}

int lengthOfNumber(long number)
{
    int length = 0;
    do
    {
        number = number / 10;
        length++;
    }
    while (number != 0);
    return length;
}

long exponentialfunction(int a, int b)
{
    int counter = b;
    long number = 1;
    while (counter > 0)
    {
        number = number * a;
        counter--;
        // printf("%i\n", number);
    }
    return number;
}

int getFirstDigit(int remainderLength, long remainder)
{
    int excessLength = remainderLength - 1;
    int digit = 0;
    long secondQuotient = exponentialfunction(10, excessLength);
    digit = remainder / secondQuotient;
    printf("Second Quotient: %li, Digit: %i\n", secondQuotient, digit);
    return digit;
}