#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    /* int var to hold string key after conversion */
    int key = 0;
    
    /* handle too many/too few arguments */
    if (argc > 2)
    {
        printf("Too many arguments\n");
        return 1;
    }
    else if (argc < 2)
    {
        printf("Not enough arguments (include key as argument)\n");
        return 1;
    }
    else
    {
        /* convert key from string to int */
        key = atoi(argv[1]);
        
        /* user input */
        string input = GetString();
        string output = input;
        
        /* helper var to carry out numeric operations */
        int charNum = 0;
        
        for(int i = 0, n = strlen(input); i < n; i++)
        {
            /* cases to encode uppercase/lowercase chars*/
            if (isupper(input[i]))
            {
                /* Add/Subtract 65 for Modulo purposes */
                charNum = (int) input[i] + key - 65;
                charNum = (charNum % 26) + 65;
                output[i] = (char) charNum;
            }
            else if (islower(input[i])) 
            {
                /* Add/Subtract 65 for Modulo purposes */
                charNum = (int) input[i] + key - 97;
                charNum = (charNum % 26) + 97;
                output[i] = (char) charNum;
            }
            else
            {
                /* Leave character the same */
                output[i] = input[i];
            }
            printf("%c", output[i]);
        }
        printf("\n");
    }
}