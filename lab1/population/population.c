#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int n;
    do
    {
        n = get_int("Enter start size: ");
    }
    while (n < 9);
    printf("Start size: %i\n", n);

    // TODO: Prompt for end size
    int i;
    do
    {
        i = get_int("Enter end size: ");
    }
    while (i < n);
    printf("End size: %i\n", i);

    // TODO: Calculate number of years until we reach threshold
    int count = 0;
    while (n < i)
    {
        n = n + (int) n / 3 - (int) n / 4;
        count++;
    }

    // TODO: Print number of years
    printf("Years: %i\n", count);
}