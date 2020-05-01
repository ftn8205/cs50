#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void encrypt(string plaintext, int key);

int main(int argc, string argv[])
{
    string plaintext;

    // validate the lenght of command-line argument are 2
    if (argc == 2)
    {
        //validate the command-line argument is digit
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            // argv[1][i] >= '0' && argv[1][i] <= '9'
            if (isdigit(argv[1][i]))
            {}
            else
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }

        plaintext = get_string("plaintext: ");
        encrypt(plaintext, atoi(argv[1]));
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

void encrypt(string plaintext, int key)
{
    printf("ciphertext: ");

    for (int i = 0; i < strlen(plaintext); i++)
    {
        if ('a' <= plaintext[i] && plaintext[i] <= 'z')
        {
            printf("%c", (plaintext[i] - 'a' + key) % 26 + 'a');
        }
        else if ('A' <= plaintext[i] && plaintext[i] <= 'Z')
        {
            printf("%c", (plaintext[i] - 'A' + key) % 26 + 'A');
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}