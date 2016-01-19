#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    /* Check to see whether more than 
    2 command line args were input*/ 
    
    /* handle too many/few args */
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
        /* declare array of keys */
        string arg = argv[1];
        /* declare int key array of the size of the arg*/
        int key[strlen(arg)];
        
        /* convert string key arg to a key value from 0-25*/
        for (int i = 0; i < strlen(arg); i++)
        {
            /*  
                remind the user to enter only alphabetic chars
                for the key
            */
            if (isalpha(arg[i]) == false)
            {
                printf("Only alphabetic characters please!\n");
                return 1;    
            }
            else
            {
                key[i] = (int) tolower(arg[i]) - 97;
            }
        }
        
        /* user input of text to encode*/
        string input = GetString();
        string output = input;
        
        int charNum = 0;
        
        for (int i = 0, k = 0, n = strlen(input); i < n; i++, k++)
        {
           u /* modular key cycling */
            k = k % strlen(arg);
            
            /* encode uppercase/lowercase chars*/
            if (isupper(input[i]))
            {
                /* Add/Subtract 65 for Modulo purposes */
                charNum = (int) input[i] + key[k] - 65;
                charNum = (charNum % 26) + 65;
                output[i] = (char) charNum;
            }
            else if (islower(input[i]))
            {
                /* Add/Subtract 65 for Modulo purposes */
                charNum = (int) input[i] + key[k] - 97;
                charNum = (charNum % 26) + 97;
                output[i] = (char) charNum;
            }
            else
            {
                /* Leave character the same */
                output[i] = input[i];
                k--;
            }
            printf("%c", output[i]);
        }
        printf("\n");
    }
}