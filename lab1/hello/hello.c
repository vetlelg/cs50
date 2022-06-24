#include <stdio.h>
#include <cs50.h>


// Gets a string from the user and saves it in a string variable called name
// Prints "hello, " and then the name that the user typed in
int main(void)
{
    string name = get_string("What is your name?\n");
    printf("hello, %s\n", name);
}