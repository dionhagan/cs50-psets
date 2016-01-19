/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(void)
{
    // open file
    FILE* file = fopen("card.raw", "r");
    if (file == NULL)
    {
        
        printf("File does not exist.\n");
        return 1;
    }
    
    // initialize buffer to hold 512 bytes at a time
    uint8_t buffer[512];
    
    // counter
    int jpg_iter = 0;
    int file_helper = 0;
    
    fread(buffer, 512, 1, file);
    
    FILE* jpg;
    
    // iterate through content of file until EOF
    // get 512 bytes at a time
    while (fread(buffer, 512, 1, file) > 0)
    {
        // check jpg signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff
            && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            char title[8];
            
            // write file according to title
            if (jpg_iter > 9)
            {
                sprintf(title, "0%d.jpg", jpg_iter);
            }
            else if (jpg_iter < 10)
            {
                sprintf(title, "00%d.jpg", jpg_iter);
            }
            else
            {
                
            }
            
            // write to file if first file (0) or if sequential (1)
            if (file_helper == 0)
            {
                jpg = fopen(title, "w");
                fwrite(buffer, sizeof(buffer), 1, jpg);
                file_helper = 1;
            }
            if (file_helper == 1)
            {
                fclose(jpg);
                jpg = fopen(title, "w");
                fwrite(buffer, sizeof(buffer), 1, jpg);
                jpg_iter++;
            }
        }
        else
        {
            // case: 
            if (file_helper == 1)
            {   
                fwrite(buffer, sizeof(buffer), 1, jpg);
            }
        }
    }
    fclose(file);
    return(0);
}
