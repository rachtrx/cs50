#include <cs50.h>
#include <stdio.h>

int lengthOfNumber(long a);

int main(void)
{
    // prompt for number
    long number = get_long("Number: ");

    // get length of number
    int length = lengthOfNumber(number);

    // get the product of every other digit
    long remainder = 0;
    int sum;
    const int quotient = 10;
    int startingNumbers;
    for (int i = 0; i < length; i++)
    {
        // printf("Number: %li\n", number);
        remainder = number % quotient;
        // printf("Remainder: %li\n", remainder);
        if (i == length - 2)
        {
            startingNumbers = remainder;
        }
        if (i == length - 1)
        {
            startingNumbers = startingNumbers + remainder * quotient;
        }

        if (i % 2 != 0)
        {
            remainder *= 2;
            // printf("double remainder: %li\n", remainder);
            int firstDigit = remainder / quotient;
            // printf("first digit: %i\n", firstDigit);
            int secondDigit = remainder % quotient;
            // printf("second digit: %i\n", secondDigit);
            sum = sum + firstDigit + secondDigit;
            // printf("sum: %i\n", sum);
        }
        else
        {
            sum = sum + remainder;
            // printf("sum: %i\n", sum);
        }
        number = number / quotient;
        // printf("starting numbers: %i\n", startingNumbers);
    }

    // check for validity
    if (sum % quotient == 0)
    {
        if (startingNumbers > 39 && startingNumbers < 50 && (length == 13 || length == 16))
        {
            printf("VISA\n");
        }
        else if ((startingNumbers == 34 || startingNumbers == 37) && (length == 15))
        {
            printf("AMEX\n");
        }
        else if (startingNumbers > 50 && startingNumbers < 56 && length == 16)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
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