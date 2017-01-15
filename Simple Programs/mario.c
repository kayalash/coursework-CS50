#include <stdio.h>
#include <cs50.h>

int main (void)
{
    int x, blank, hash;
    do
    {
        printf ("Height: ");
        x = GetInt ();
    }
    while ((x <= 0) || (x > 23));
    blank = x - 1;
    hash = 2;
    for (int i = 1; i <= x; i++)
    {
        for (int y = 1; y <= blank; y++)
        {
            printf (" ");
        }
        for (int z = 1; z <= hash; z++)
        {
            printf ("#");
        }
        printf ("\n");
        blank--;
        hash++;
    }
}