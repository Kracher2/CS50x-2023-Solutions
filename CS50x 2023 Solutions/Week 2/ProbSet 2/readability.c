#include "cs50.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int get_clindex(string text);
float clindex;

int main(void)
{

    string text = get_string("Text: ");

    get_clindex(text);

    if (clindex < 1)
    {
        printf("Before Grade 1\n");
    }

    clindex = round(clindex);

    if (clindex > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        for (int j = 0; j <= clindex; j++)
        {
            if (clindex == j)
            {
                printf("Grade %i\n", j);
            }
        }
    }
}

int get_clindex(string text)
{
    float letters = 0, words = 1, sentences = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isupper(text[i]) || islower(text[i]))
        {
            letters++;
        }
        else if (text[i] == ' ')
        {
            words++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    clindex = 0.0588 * (letters / words * 100) - 0.296 * (sentences / words * 100) - 15.8;

    return clindex;
}