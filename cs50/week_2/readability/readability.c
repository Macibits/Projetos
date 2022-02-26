#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

//Functions to use
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int count_grade(string text);

//Main
int main(void)
{
    //Get a text from user
    string text = get_string("Text: ");

    //Get variables for Coleman-Liau index
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    int index = count_grade(text);

    //Print
    if (index <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 2 && index <= 15)
    {
        printf("Grade %i\n", index);
    }
    else
    {
        printf("Grade 16+\n");
    }
}

//To count letters
int count_letters(string text)
{
    int letters = 0;

    for (int l = 0, len = strlen(text); l < len; l++)
    {
        if (isalpha(text[l]))
        {
            letters += 1;
        }
    }
    return letters;
}

//To count words
int count_words(string text)
{
    int words = 1;

    for (int w = 0, len = strlen(text); w < len; w++)
    {
        if (text[w] == ' ')
        {
            words += 1;
        }
    }
    return words;
}

//To count sentences
int count_sentences(string text)
{
    int sentences = 0;

    for (int s = 0, len = strlen(text); s < len; s++)
    {
        if (text[s] == '.')
        {
            sentences += 1;
        }
        else if (text[s] == '!')
        {
            sentences += 1;
        }
        else if (text[s] == '?')
        {
            sentences += 1;
        }
    }
    return sentences;
}

//Index coleman-liau
int count_grade(string text)
{
    //get variables
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    //run index
    float L = (float) letters / (float) words * 100;
    float S = (float) sentences / (float) words * 100;
    float I = 0.0588 * L - 0.296 * S - 15.8;
    int index = round(I);
    return index;
}