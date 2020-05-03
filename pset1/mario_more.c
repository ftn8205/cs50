#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    do 
    {
        height = get_int("Height: ");
    } 
    while (height <= 0 || height > 8);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < 2 * height + 2 ; j++)
        {
            if (j < height - i - 1)
            {
                printf(" ");
            }
            else if (j >= height - i - 1 && j < height)
            {
                printf("#");
            }
            else if (j == height || j == height + 1)
            {
                printf(" ");
            }
            else if (j > height + 1 && j <= height + 2 + i)
            {
                printf("#");
            }
            else
            {
                printf("");
            }
        }
        printf("\n");
    }
}
