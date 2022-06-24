#include <stdio.h>
#include <cs50.h>

int get_height();
void print_spaces();
void print_hashes();

int main(void)
{
    // Prompt user for height of pyramid
    int height = get_height();

    // Print each row of spaces and hashes
    for (int i = 0; i < height; i++)
    {
        print_spaces(height, i + 1); // Print spaces equal to pyramid row number minus 1
        print_hashes(height, i + 1); // Print hashes equal to pyramid row number
        printf("  ");            // Print two spaces
        print_hashes(height, i + 1); // Print hashes again
        printf("\n");            // New line
    }
}


int get_height()
{
    int height;
    do
    {
        height = get_int("Height (Number between 1 and 8): ");
    }
    while (height < 1 || height > 8);

    return height;
}

void print_spaces(int height, int i)
{
    for (int n = i; n < height; n++)
    {
        printf(" ");
    }
}

void print_hashes(int height, int i)
{
    for (int n = 0; n < i; n++)
    {
        printf("#");
    }
}