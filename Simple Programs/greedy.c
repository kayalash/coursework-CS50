#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main (void)
{
    int coins = 0;
    float f;
    do
    {
        printf ("How much change is owed?\n");
        printf ("So how much change is actually owed?\n");
        f = GetFloat ();
    }
    while (f < 0);
    int cents = (int) round (f * 100);
    coins += floor (cents / 25);
    cents = cents % 25;
    coins += ceil (cents / 10);
    cents = cents % 10;
    coins += ceil (cents / 5);
    cents = cents % 5;
    coins += cents;
    printf ("%i\n", coins);
}