// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// CAN CHANGE
// Number of buckets in hash table
const unsigned int N = 300;

// Hash table
node *table[N];

int count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    node *cursor = table[index];
    // printf("index:[%d], word:[%s]\n", index, word);
    while (cursor != NULL)
    {
        // printf("CHECK:%d\n",!strcasecmp(cursor->word, word),word);
        // printf("%s -- %s\n",cursor->word,word);
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor -> next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    // if (word[0] >= 97)
    // {
    //     return word[0] - 97;
    // }
    // return word[0] - 65;
    if (word[0] == '\0')
    {
        return 0;
    }
    if (word[1] == '\0')
    {
        return word[0];
    }
    if (word[0] >= 'a' && word[0] <= 'z')
    {
        if (word[1] >= 'a' && word[1] <= 'z')
        {
            return (word[0] - 'a') + (word[1] - 'a');
        }
        else if ((word[1] >= 'A' && word[1] <= 'Z'))
        {
            return (word[0] - 'a') + (word[1] - 'A');
        }
        else
        {
            return (word[0] - 'a');
        }
        // printf("lower: %d \n", (word[0] - 'a') + word[1]);
        // return (word[0] - 'a') + word[1];
    }
    else if (word[0] >= 'A' && word[0] <= 'Z')
    {
        if (word[1] >= 'a' && word[1] <= 'z')
        {
            return (word[0] - 'A') + (word[1] - 'a');
        }
        else if ((word[1] >= 'A' && word[1] <= 'Z'))
        {
            return (word[0] - 'A') + (word[1] - 'A');
        }
        else
        {
            return (word[0] - 'A');
        }
        // printf("upper: %d \n", (word[0] - 'A') + word[1]);
        // return (word[0] - 'A') + word[1];
    }
    else
    {
        return 0;
    }
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    char word[LENGTH + 1];
    if (file != NULL)
    {
        while (fscanf(file, "%s", word) != EOF)
        {
            node *newNode = malloc(sizeof(node));
            if (newNode != NULL)
            {
                int index = hash(word);

                //init new node
                strcpy(newNode->word, word);
                newNode->next = NULL;

                if (table[index] == NULL)
                {
                    table[index] = newNode;
                }
                else
                {
                    newNode->next = table[index];
                    table[index] = newNode;
                }
                count++;
                // printf("AAA: %s \n",table[index] -> word);
            }

        }


        fclose(file);
        return true;
    }
    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (count > 0)
    {
        return count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    node *cursor;
    node *tmp;
    for (int i = 0; i < N; i++)
    {
        tmp = table[i];
        cursor = table[i];
        while (cursor != NULL)
        {
            cursor = cursor -> next;
            free(tmp);
            tmp = cursor;
        }

    }
    return true;
}
