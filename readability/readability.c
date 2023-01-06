#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");

    int w = count_words(text);
    int l = count_letters(text);
    int s = count_sentences(text);

    if (!(l))
    {
        w = 0;
        s = 0;
    }

    float index = 0.0588 * l / w * 100 - 0.296 * s / w * 100 - 15.8;
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (15.5 <= index)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }
}

int count_letters(string text)
{
    int letters_counter = 0;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        char temp = tolower(text[i]);
        if (96 < temp && temp < 123)
        {
            letters_counter++;
        }
    }
    return letters_counter;
}

int count_words(string text)
{

    // remove starting spaces
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (!(text[i] == ' '))
        {
            break;
        }
        if (text[i] == ' ')
        {
            text[i] = '_';
        }

    }

    // remove ending spaces
    for (int length = strlen(text), i = length - 1; i > 0; i--)
    {
        if (!(text[i] == ' '))
        {
            break;
        }
        if (text[i] == ' ')
        {
            text[i] = '_';
        }

    }

    // remove multiple spaces
    bool mult_spaces_removed = false;
    while (!(mult_spaces_removed))
    {
        mult_spaces_removed = true;
        for (int i = 0, length = strlen(text); i < length; i++)
        {
            if (text[i] == ' ' && text[i + 1] == ' ')
            {
                text[i] = '_';
                mult_spaces_removed = false;
            }
        }
    }

    // typical counting words
    int words_counter = 1;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (text[i] == 32)
        {
            words_counter++;
        }
    }

    return words_counter;
}

int count_sentences(string text)
{
    int sentences_counter = 0;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences_counter++;
        }
    }
    return sentences_counter;
}