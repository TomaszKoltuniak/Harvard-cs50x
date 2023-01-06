#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string str_tolower(string text);
string substitution(int key[], string plaintext);
bool if_repetition(string text);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("You must prompt one argument.\n");
        return 1;
    }
    if (strlen(argv[1]) != 26)
    {
        printf("Argument must contain 26 letters.\n");
        return 1;
    }
    string key_text = str_tolower((string) argv[1]);
    for (int i = 0; i < 26; i++)
    {
        if (key_text[i] < 'a' || 'z' < key_text[i])
        {
            printf("Argument must contain only letters.\n");
            return 1;
        }
    }
    if (if_repetition(key_text))
    {
        printf("Argument should not repeap any letter.\n");
        return 1;
    }
    string plaintext = get_string("plaintext:  ");

    int key_array[1];
    for (int i = 97; i < 123; i++)
    {
        key_array[i] = key_text[i - 97] - i;
    }
    string ciphertext = substitution(key_array, plaintext);
    printf("ciphertext: %s\n", ciphertext);
}

string substitution(int key[], string plaintext)
{
    string ciphertext;

    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isupper(plaintext[i]))
        {
            plaintext[i] = plaintext[i] + key[(int) plaintext[i] + 32];
        }
        else if (islower(plaintext[i]))
        {
            plaintext[i] = plaintext[i] + key[(int) plaintext[i]];
        }
    }
    ciphertext = plaintext;
    return ciphertext;
}

bool if_repetition(string text)
{
    for (int i = 0; i < strlen(text); i++)
    {
        for (int j = 0; j < strlen(text) && j != i; j++)
        {
            if (text[i] == text[j])
            {
                return true;
            }
        }
    }
    return false;
}

string str_tolower(string text)
{
    for (int i = 0; i < strlen(text); i++)
    {
        text[i] = tolower(text[i]);
    }
    return text;
}