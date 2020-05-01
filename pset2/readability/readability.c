#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int numberOfLetters(string s);
int numberOfWords(string s);
int numberOfSentences(string s);
void getReadablity(int index);

int main(void)
{
    string text = get_string("Text: ");

    int letter = numberOfLetters(text);
    int word   = numberOfWords(text);
    int sentence = numberOfSentences(text);

    // printf("%i  %i   %i", letter, word, sentence);
    float l = (float) letter / word * 100;
    float s = (float) sentence / word * 100;

    int index = round(0.0588 * l - 0.296 * s - 15.8);

    getReadablity(index);

}

void getReadablity(int index)
{
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int numberOfLetters(string s)
{
    int letterCounter = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (('a' <= s[i] && s[i] <= 'z') || ('A' <= s[i] && s[i] <= 'Z'))
        {
            letterCounter++;
        }
    }
    return letterCounter;
}

int numberOfWords(string s)
{
    int wordCounter = 0;

    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == ' ')
        {
            wordCounter++;
        }
    }
    return wordCounter + 1;
}

int numberOfSentences(string s)
{
    int sentenceCounter = 0;

    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            sentenceCounter++;
        }
    }
    return sentenceCounter;
}