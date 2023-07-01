#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // prompt for name
    string answer = get_string("What's your name? ");

    // print name
    printf("hello, %s\n", answer);
}