#include <cs50.h>
#include <stdio.h>

void print_spaces(int a);
void print_hashes(int b);

int main(void)
{
// enter number of rows
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

// print the rows 1 by 1
    for (int i = 1; i <= height; i++)
    {
        print_spaces(height - i);
        print_hashes(i);
        printf("  ");
        print_hashes(i);
        printf("\n");
    }
}

// create function to print "space" a times
void print_spaces(int a)
{
    for (int i = 0; i < a ; i++)
    {
        printf(" ");
    }
}

// create function to print "#" b times
void print_hashes(int b)
{
    for (int j = 0; j < b; j++)
    {
        printf("#");
    }
}