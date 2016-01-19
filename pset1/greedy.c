#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    /* Constants */
    #define QUARTER 25;
    #define DIME    10;
    #define NICKEL  5;
    #define PENNY   1;
    
    /* Ask user for input */
    float input;

    do
    {
        printf("Hey! ");
        printf("How much change is owed: ");
        input = GetFloat();
    }
    while(input <= 0);
    
    /* Convert Float Input to Int Change*/
    int change = (int)round(input * 100);
    
    /* Calculate min coin change via subtraction/counter */
    int counter = 0;
    
    while (change >= 0)
    {
        if (change >= 25)
        {
            change -= QUARTER;
            counter++;
        }
        else if (change < 25 && change >= 10)
        {
            change -= DIME;
            counter++;
        }
        else if (change < 10 && change >= 5)
        {
            change -= NICKEL;
            counter++;
        }
        else if (change < 5 && change > 0)
        {
            change -= PENNY;
            counter++;
        }
        else
        {
            printf("%i\n", counter);
            return 0;
        }
    }
}