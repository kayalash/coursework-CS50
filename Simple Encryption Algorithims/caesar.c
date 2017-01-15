#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void encrypt (int k, string text);

int main (int argc, string argv [])
{
    if (argc != 2)
    {
        printf ("You did not enter a number/your number is invalid\n");
        return 1;
    }
    int k = atoi(argv[1]);
    if (k > 26)
    {
        k = k % 26;
    }
    string text = GetString ();
    encrypt (k, text);
    return 0;
}

void encrypt (int k, string text)
{
    for (int i = 0, n = strlen (text); i < n; i++)
    {
        if (((text [i] >= 'a') && (text [i] <= 'z')) || ((text [i] >= 'A') && (text [i] <= 'Z')))
        {
            int pos = text [i] + k;
            if (((text [i] < 'Z') && (pos > 'Z')) || ((text [i] > 'a') && (pos > 'z')))
            {
                pos -= 26;
            }
            text [i] = (char) pos;
        }
    }
    printf ("%s\n", text);
}