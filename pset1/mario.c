#include <cs50.h>
#include <stdio.h>

int main(void)
{
    /* User Input */
    int height;
    
    do
    {
        printf("Please enter a positive integer Height: ");
        height = GetInt();
        if(height == 0)
        {
            return 0;
        }
    }
    while (height < 1 || height > 23);
    
    /* For loop to iterate over each line */
    for(int i = 0; i < height; i++)
    {
        /* for loop to print spaces */
        for(int j = 0; j < height-i-1; j++)
        {
            printf("%s"," ");
        }
        
        /* for loop to print hashes*/
        for(int k = 0; k < i + 2; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}