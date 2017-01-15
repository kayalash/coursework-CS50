#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main (void)
{
    string name = GetString ();
    int words = 1;
    for (int i = 0, n = strlen (name); i < n; i++)
    {
        if (name [i] == ' ')
        {
            words++;
        }
    }
    char initials [words];
    int count = 0;
    for (int i = 0, n = strlen (name); i < n; i++)
    {
        if (i == 0)
        {
            initials [count] = name [i];
            count++;
        }
        else if (name [i] == ' ')
        {
            initials [count] = name [i + 1];
            count++;
        }
    }
    for (int i = 0; i < words; i++)
    {
        printf ("%c", toupper (initials [i]));
    }
    printf ("\n");
}