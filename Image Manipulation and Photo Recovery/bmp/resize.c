/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4 || atoi(argv[1]) > 100 || atoi (argv[1]) < 0)
    {
        printf("Usage: ./resize [1 - 100] infile outfile\n");
        return 1;
    }

    // remember resize factor 
    int factor = atoi (argv[1]);
    
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

    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // adjusts BITMAPFILEHEADER
    int newPadding =  (4 - ((bi.biWidth * factor) * sizeof(RGBTRIPLE)) % 4) % 4;
    
    bf.bfSize = 14 + 40 + (newPadding * abs(bi.biHeight) * factor) + (3 * (bi.biWidth * factor) * abs(bi.biHeight) * factor);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // adjusts BITMAPINFOHEADER 
    int old_biWidth = bi.biWidth;
    int old_biHeight = bi.biHeight;
    bi.biWidth *= factor;
    bi.biHeight *= factor;
    bi.biSizeImage = newPadding * abs (bi.biHeight) + 3 * bi.biWidth * abs(bi.biHeight);
    
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    newPadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(old_biHeight); i < biHeight; i++)
    {
        
        for (int h = 0; h < factor; h++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < old_biWidth; j++)
            {
                    // temporary storage
                    RGBTRIPLE triple;
                    
                    // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                    // write RGB triple to outfile
                    for (int k = 0; k < factor; k++)
                    {
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
            }
            
            for (int k = 0; k < newPadding; k++)
            {
                fputc(0x00, outptr);
            }
            
            fseek(inptr, -3 * old_biWidth, SEEK_CUR);
        }
        fseek(inptr, 3 * old_biWidth + padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
