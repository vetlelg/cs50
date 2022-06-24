#include <stdio.h>
#include <cs50.h>
#include <string.h>

const int L = 26;

void encrypt(string plaintext, string cipher);

int main(int argc, string argv[])
{
    //If number of command-line arguments not equal to 2, print error message and return 1
    if (argc != 2)
    {
        printf("You must enter a single command-line argument.\n");
        return 1;
    }
    
    //Start iterating through the cipher
    int length = strlen(argv[1]);
    for (int i = 0; i < length; i++)
    {
        //If cipher does not contain 26 alphabetic characters, print error message and return 1
        int letter = (int) argv[1][i];
        if (letter < 65 || (letter > 90 && letter < 97) || letter > 122 || length != L)
        {
            printf("The cipher must contain 26 alphabetic characters, and contain each letter only once.\n");
            return 1;
        }
        
        //Iterate through cipher again and check if cipher contains any characters more than once. Print error message and return 1 if it does.
        for (int n = 0; n < (L - i - 1); n++) //Start iterating from argv[1][i+1] and only interate L-i-1 times
        {
            if (argv[1][i] == argv[1][n + i + 1]) //Start iterating from argv[1][i+1]
            {
                printf("The cipher must contain 26 alphabetic characters, and contain each letter only once.\n");
                return 1;
            }
        }
    }
    
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");
    encrypt(plaintext, argv[1]); //Encrypt plaintext and print ciphertext
    return 0;
}


/* 
 * Encrypt plaintext and print ciphertext.
 * First loop through plaintext and cipher.
 * Check char number of plaintext[i] in the alphabet and check if upper or lower case.
 * Check for corresponding char number in cipher, convert cipher[n] to upper/lower case and print cipher[n].
 * If plaintext[i] is not an alphabetic character, print plaintext[i].
 */
void encrypt(string plaintext, string cipher)
{
    int length = strlen(plaintext);
    for (int i = 0; i < length; i++) //start looping through plaintext
    {
        for (int n = 0; n < L; n++) //start looping through cipher
        {
            if ((int) plaintext[i] - 65 == n) //check if char is upper case and if char alphabet number is equal cipher char number
            {
                if ((int) cipher[n] < 97) //if cipher char is upper case, print char
                {
                    printf("%c", cipher[n]);
                }
                else //else convert to upper case and print
                {
                    printf("%c", (char)((int) cipher[n] - 32));
                }
            }
            else if ((int) plaintext[i] - 97 == n) //check if cipher char is lower case and alphabet number is equal to cipher char number
            {
                if ((int) cipher[n] < 97) //if cipher char is upper case, convert to lower case and print
                {
                    printf("%c", (char)((int) cipher[n] + 32));
                }
                else //else print char
                {
                    printf("%c", cipher[n]);
                }
            }
        }
        
        //if plaintext char is not an alphabetic character, print char
        int letter = (int) plaintext[i];
        if (letter < 65 || (letter > 90 && letter < 97) || letter > 122)
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}


