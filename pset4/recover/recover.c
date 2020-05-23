#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;


int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        FILE *file = fopen(argv[1], "r");
        BYTE *buffer = malloc(sizeof(BYTE) * 512);
        FILE *outputFile = NULL;

        if (file == NULL)
        {
            printf("Can't not open the %s \n", argv[1]);
            return 1;
        }
        else
        {
            int f = 0;
            int count = 0;
            char outputName[8];
            while (fread(buffer, sizeof(BYTE), 512, file) == 512)
            {
                // fread(buffer, sizeof(BYTE), 512, file);
                if (buffer[0] == 0xff  && buffer[1] == 0xd8  && buffer[2] == 0xff  && (buffer[3] & 0xf0) == 0xe0)
                {
                    if (count == 0)
                    {
                        sprintf(outputName, "%03d.jpg", count);
                        outputFile = fopen(outputName, "a");
                    }
                    else
                    {
                        fclose(outputFile);
                        sprintf(outputName, "%03d.jpg", count);
                        outputFile = fopen(outputName, "a");
                    }
                    fwrite(buffer, sizeof(BYTE), 512, outputFile);
                    f = 1;
                    count++;
                }
                else
                {
                    if (f == 1)
                    {
                        fwrite(buffer, sizeof(BYTE), 512, outputFile);
                    }
                }
                // printf("f: %i\n", f);
                // printf("count: %i\n", count);
                // printf("%i-%i-%i-%i\n", buffer[0],buffer[1],buffer[2],(buffer[3] & 240));
            }
            
            free(buffer);
            fclose(file);
            fclose(outputFile);
        }
    }
    else
    {
        printf("Usage: ./recover image");
        return 1;
    }
}
