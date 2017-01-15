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

typedef uint8_t BYTE;

int main(void)
{
    int jpgFound = 0;
    char filename [8];
    int filenum = 0;
    BYTE buf [512];
    FILE* img = NULL;
    int x = 0;
    
    FILE* file = fopen("card.raw", "r");
    
    if (file == NULL)
    {
        printf("Could not open %s.\n", "card.raw");
        return 1;
    }
    
    while (x == 0)
    {
        if ((fread (&buf, 1, 512, file)) != 512)
        {
            break;
        }
        
        if (buf [0] == 0xff &&
            buf [1] == 0xd8 &&
            buf [2] == 0xff &&
            (buf [3] & 0xf0) == 0xe0)
        {
            if (jpgFound == 1)
            {
                fclose(img);
            }
            
            jpgFound = 1;
            sprintf (filename, "%03i.jpg", filenum);
            filenum++;
            
            img = fopen(filename, "w");
            
            if (img == NULL)
            {
                printf("Could not open %s.\n", filename);
                return 1;
            }
            
            fwrite (&buf, sizeof(buf), 1, img);
            
        }
        else if (jpgFound == 1)
        {
            fwrite (&buf, sizeof(buf), 1, img);
        }
    }
}
