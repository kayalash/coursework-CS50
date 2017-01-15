#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void encrypt (string key, string text);

int main (int argc, string argv [])
{
    if (argc != 2)
    {
        printf ("You did not enter a number/your number is invalid\n");
        return 1;
    }
    char letter;
    for (int i = 0, n = strlen (argv [1]); i < n; i++)
    {
        letter = argv [1] [i];
        if ((letter < 'A')||((letter > 'Z') && (letter < 'a'))||(letter >'z'))
        {
            printf ("You did not enter a number/your number is invalid\n");
            return 1;
        }
    }
    for (int i = 0, n = strlen (argv [1]); i < n; i++)
    {
        argv [1] [i] = toupper (argv [1] [i]);
    }
    string key = argv [1];
    string text = GetString ();
    encrypt (key, text);
    return 0;
}

void encrypt (string key, string text)
{
    int x = 0;
    for (int i = 0, n = strlen (text); i < n; i++)
    {
        if (((text [i] >= 'a') && (text [i] <= 'z')) || ((text [i] >= 'A') && (text [i] <= 'Z')))
        {
            if (x == strlen (key))
            {
                x = 0;
            }
            int pos = text [i] + (key [x] - 65);
            if (((text [i] < 'Z') && (pos > 'Z')) || ((text [i] > 'a') && (pos > 'z')))
            {
                pos -= 26;
            }
            text [i] = (char) pos;
            x++;
        }
    }
    printf ("%s\n", text);
}