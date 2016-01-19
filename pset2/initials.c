/* Referred to Reference50 and 
   http://www.cs.ucsb.edu/~buoni/cs24/tutorials/howtousestrtok.txt 
   for documentation on splitting strings & pointers with strtok() function*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>

/* capitalize all characters in a string*/
string capitalize(string str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] = str[i] - ('a' - 'A');
        }
        else
        {
            /* Do Nothing - Already Capitalized*/
        }
    }
    
    return(str);
}

int main(void)
{
    string input = "";
    
    /* user input */
    do
    {
        input = GetString();
    }
    while (strlen(input) == 0);
    
    /* handle uncapitalized input*/
    input = capitalize(input);
    
    /*  
        divide input into substring tokens - delimited by
        the space character
    */
    char * tok = strtok(input, " ");
    
    /* while loop to access all string tokens*/
    while (tok != NULL)
    {
        printf("%c", tok[0]);
        /* 
            strtok(NULL, "") sets tok equal to next token
            from the original sequence
        */
        tok = strtok(NULL, " ");
        if (tok == NULL)
        {
            printf("\n");
        }
    }
    
}