#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
const int BLOCK_SIZE = 512;
const int NJPG = 50;
 
int main(int argc, char *argv[])
{
    // Check that usage is correct (That argv contains 2 strings)
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    
    // Open input file and check if it was opened correctly
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open the file.\n");
        return 1;
    }
    
    // Create output FILE pointer.
    // Assign NULL in order to be able to check whether file has been opened already or not
    FILE *output = NULL;
    
    // Array holding a block from the image-file of size 512 bytes
    BYTE block[BLOCK_SIZE];
    
    // Array of strings holding the filenames
    // Using sprintf and looping through array to create the filenames
    char str[NJPG][8];
    int string_count = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int n = 0; n < 10; n++)
        {
            sprintf(str[string_count], "0%i%i.jpg", i, n);
            string_count++;
        }
    }
    
    // Count the number of JPEGs to create the filenames
    int count = 0;
    
    // Reading one block from the file at a time
    while (fread(block, BLOCK_SIZE, 1, input))
    {
        // If block holds a JPEG, write block to a new file with filename str[count]
        if (block[0] == 255 && block[1] == 216 && block[2] == 255 && block[3] >= 15)
        {
            char *filename = str[count];
            output = fopen(filename, "w");
            if (output == NULL)
            {
                printf("Could not open the file.\n");
                return 1;
            }
            fwrite(block, BLOCK_SIZE, 1, output);
            count++;
        }
        // Else if block has already been written to a file, continue writing to the same file
        else if (output != NULL)
        {
            fwrite(block, BLOCK_SIZE, 1, output);
        }
    }
    fclose(input);
    fclose(output);
}