#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // printf("value of a is %p\n", "hello");
    // printf("value of a is %p\n", "hello");

    // char *s = "car";
    // printf("%p\n", &s);
    // printf("%p\n", s);

    // int arr[] = {0, 1, 2, 3};
    // int *i = arr;
    // i = arr;
    // printf ("%p\n", i);
    // printf ("%p\n", i + 1);

    // int goals[] = {85, 102, 66, 69, 67};
    // int (*pointerToGoals)[5] = &goals;
    // printf("address stored in pointerToGoals %p\n", pointerToGoals);
    // printf("dereferencing it, we get %p\n", *pointerToGoals);

    // int a[10];
    // int *pa = &a[0];

   int  var[] = {10, 100, 200};
   int i, *ptr[3];

    ptr[0] = &var[0];
    ptr[1] = &var[1];
    ptr[2] = &var[2];

   for ( i = 0; i < 3; i++) {
      printf("Value of var[%d] = %d\n", i, *ptr[i]);
   }

   return 0;
}