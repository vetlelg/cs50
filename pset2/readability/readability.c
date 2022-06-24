#include <stdio.h>
#include <cs50.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int calculate_index(int letters, int words, int sentences);
void print_grade(int index);

int main(void)
{
    // Get the text from the user
    string text = get_string("Text: ");
    
    // Count number of letters, words and sentences in the text
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    
    // Calculate the Coleman-Liau index
    int index = calculate_index(letters, words, sentences);
    
    // Print the grade level
    print_grade(index);
    
}

// Counting letters in the text
int count_letters(string text)
{
    // Looping through the text
    int count = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        // Adding 1 to count if the ASCII code of letter is 65-90 or 97-122
        int letter = (int) text[i];
        if ((letter >= (int) 'A' && letter <= (int) 'Z') || (letter >= (int) 'a' && letter <= (int) 'z'))
        {
            count++;
        }
    }
    return count;
}

// Looping through the text and adding 1 to count if the char is equal to ' '
int count_words(string text)
{
    int count = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
        {
            count++;
        }
    }
    return count + 1; // Accounts for the last word in the text
}

// Looping through the text and adding 1 to count if char is either . ? !
int count_sentences(string text)
{
    int count = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}

// Calculating average letters and sentences per 100 words. Then calculating Coleman-Liau index and rounding to nearest whole number
int calculate_index(int letters, int words, int sentences)
{
    float avg_letters = (float) letters / (float) words * 100;
    float avg_sentences = (float) sentences / (float) words * 100;
    return round(0.0588 * avg_letters - 0.296 * avg_sentences - 15.8);
}

// Printing the grade level
void print_grade(int index)
{
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}