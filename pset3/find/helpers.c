/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    
    // def vars for first, middle, last elements in array
    // set target for search to find
    int first = 0;
    int last = n-1;
    int middle = (first + last)/2;
    int target = value;
    
    // iterate over values while sorted array has
    // first element smaller than last element
    // and while target has not been foun
    
    if (values[last] == target)
    {
        return true;
    }
    else
    {
        while (first <=  last)
        {
            if (values[middle] < target)
            {
                // Case 1: middle value is less than target
                // Do: filter to the second half of the array
                first = middle + 1;
            }
            else if (values[middle] == target)
            {
                // Case 2: middle value is equal to target
                // Do: print target found, return true
                printf("found at index: %i\n", middle);
                return true;
            }
            else
            {
                // Case 3: middle value is greater than target
                // Do: search first half of the array
                last = middle - 1;
            }
            middle = (first + last)/2;
        }
    }
    
        // return result    
        return false;
        
}

/**
 * Sorts array of n values. 
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    bool didSwap;
    int temp;

    do
    {
        // default set didSwap to false before every 
        // sorting run through
        didSwap = false;
        
        for (int i=0; i < n; i++)
        {
            if (values[i] > values[i+1])
            {
                temp = values[i];
                values[i] = values[i+1];
                values[i + 1] = temp;
                didSwap = true;
            }
            else
            {
                //do nothing
            }
        }
        //end of for loop
    } while (didSwap == true);
}