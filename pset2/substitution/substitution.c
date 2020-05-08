#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

void substitution(string plaintext, string key);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        int argvLength = strlen(argv[1]);
        for (int i = 0; i < argvLength; i++)
        {
            if (!isalpha(argv[1][i]))
            {
                printf("Usage: ./substitution key");
                return 1;
            }
        }
        if (argvLength == 26)
        {
            for (int i = 0; i < argvLength; i++)
            {
                for (int j = 0; j < argvLength; j++)
                {
                    if (i != j)
                    {
                        if (argv[1][i] == argv[1][j])
                        {
                            printf("Key can't repeat");
                            return 1;
                        }
                    }
                }
            }
            string plainText = get_string("plaintext: ");
            substitution(plainText, argv[1]);
        }
        else
        {
            printf("Key must contain 26 characters.");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./substitution key");
        return 1;
    }
}

void substitution(string plaintext, string key)
{
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]) && isupper(key[plaintext[i] - 'A']))
            {
                printf("%c", key[plaintext[i] - 'A']);
            }
            else if (isupper(plaintext[i]) && islower(key[plaintext[i] - 'A']))
            {
                printf("%c", key[plaintext[i] - 'A'] - 32);
            }
            else if (islower(plaintext[i]) && isupper(key[plaintext[i] - 'a']))
            {
                printf("%c", key[plaintext[i] - 'a'] + 32);
            }
            else
            {
                printf("%c", key[plaintext[i] - 'a']);
            }
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n%c", '\0');
}