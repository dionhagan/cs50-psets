/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes an image based on dimension multiple
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    
    // multiple by which to resize image
    int n = atoi(argv[1]);
    if (n < 1 || n > 100)
    {
        printf("n must be between 1 and 100");
        return 1;
    }
    
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // initialize new header var
    BITMAPINFOHEADER outbi = bi;
    BITMAPFILEHEADER outbf = bf;
    
    // change dimensions
    outbi.biHeight = bi.biHeight * n;
    outbi.biWidth = bi.biWidth * n;
    
    // determine padding for scanlines
    int padding =  (4 - (abs(bi.biWidth) * sizeof(RGBTRIPLE)) % 4) % 4;
    int newpadding = (4 - (abs(outbi.biWidth) * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // change size
    outbi.biSizeImage = (abs(outbi.biWidth) * sizeof(RGBTRIPLE) + newpadding) * abs(outbi.biHeight);
    outbf.bfSize = outbi.biSizeImage + 54;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&outbf, sizeof(BITMAPFILEHEADER), 1, outptr);
    // write outfile's BITMAPINFOHEADER
    fwrite(&outbi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // write scanfile to outfile 'n' times
        for (int y = 0; y < n; y++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                // write RGB triple to outfile n times
                for (int x = 0; x < n; x++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            
            // add padding to the end of scanline
            for (int k = 0; k < newpadding; k++)
            {
                fputc(0x00, outptr);
            }
                
            /*  if y < (n-1): seek back to beginning of scanline and
                rewrite lines
            */
            if (y < (n - 1))
            {
                // seek back to beginning of line
                fseek(inptr, -1 * (bi.biWidth * sizeof(RGBTRIPLE)), SEEK_CUR);
            }
            else
            {
                // skip over padding, if any
                fseek(inptr, padding, SEEK_CUR);
            }
        }
        
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
