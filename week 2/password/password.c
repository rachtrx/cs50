// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    int upper = 0;
    int lower = 0;
    int number = 0;
    int symbol = 0;
    int i = 0;
    while (password[i] != '\0')
    {
        char x = password[i];
        if (x >= 65 && x <= 90)
        {
            upper += 1;
            printf("%c is upper\n", x);
        }
        else if (x >= 97 && x <= 122)
        {
            lower += 1;
            printf("%c is lower\n", x);
        }
        else if (x >= 48 && x <= 57)
        {
            number += 1;
            printf("%c is number\n", x);
        }
        else
        {
            symbol += 1;
            printf("%c is symbol\n", x);
        }
    i++;
    }

    if (upper > 0 && lower > 0 && number > 0 && symbol > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
