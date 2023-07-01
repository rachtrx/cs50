#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // TODO
    int num = 0;
    if (input[0] == '\0')
    {
        return num;
    }


    int i = 0;
    while (input[i + 1] != '\0')
    {
        i++;
    }
    num = input[i] - '0';
    input[i] = '\0';
    int value = num + 10 * convert(input);
    return value;
}