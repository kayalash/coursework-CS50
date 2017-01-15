/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

bool binarySearch (int key, int values[], int min, int max);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
     return binarySearch (value, values, 0, n);
}

bool binarySearch(int key, int values[], int min, int max)
{
    int mid = ((max - min) / 2) + min;
    
    if (min > max)
    {
        return false;
    }
    else if (key > values [mid])
    {
        return binarySearch (key, values, (mid + 1), max);
    }
    else if (key < values [mid])
    {
        return binarySearch (key, values, min, (mid - 1));
    }
    else
    {
        return true;
    }
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int x = 0;
    bool sorted;
    do
    { 
        sorted = true;
        for (int i = 0; i < (n - 1); i++)
        {
            if (values [i] > values [i + 1])
            {
                x = values [i];
                values [i] = values [i + 1];
                values [i + 1] = x;
                sorted = false;
            }
        }
    } 
    while (sorted == false);
}
