#include <cs50.h>
#include <stdio.h>

int main(void)
{
    
    /* User Input */
    int min = 0;
    
    while(min <= 0)
    {
        printf("What is your average shower time (in minutes) ?\n");  
        min = GetInt();
        if(min <=0)
        {
            printf("Please enter a positive number\n");
        }
    }
    
    /* Computation */
    int ounces  = 192 * min;
    int bottles = ounces / 16;
    
    /* Output */
    printf("minutes: %i\n", min);
    printf("bottles: %i\n", bottles);
}