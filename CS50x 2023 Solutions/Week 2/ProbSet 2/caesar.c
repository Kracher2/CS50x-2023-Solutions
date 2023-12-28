#include "cs50.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);
char rotate(char c, int n);
char cc;
int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    if (only_digits(argv[1]) == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int rot = atoi(argv[1]);
    string text = get_string("plaintext:  ");
    printf("ciphertext:  ");
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (islower(text[i]))
        {
            while (((text[i]) + rot) > 122)
            {
                text[i] -= 26;
            }
            rotate(text[i], rot);
        }
        else if (isupper(text[i]))
        {
            while (((text[i]) + rot) > 90)
            {
                text[i] -= 26;
            }
            rotate(text[i], rot);
        }
        else
        {
            cc = text[i];
        }
        printf("%c", cc);
    }
    printf("\n");
    return 0;
}

bool only_digits(string s)
{
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

char rotate(char c, int n)
{

    cc = (c) + n;
    return cc;
}