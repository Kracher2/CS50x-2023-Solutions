#include "cs50.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2 || strlen(argv[1]) != 26)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    string key = argv[1];
    int const lenkey = strlen(key);
    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    int x = 0;
    for (int i = 0; i < lenkey; i++)
    {
        for (int j = 0; j < lenkey; j++)
        {
            if (key[i] == key[j])
            {
                x++;
                if (x > 26)
                {
                    printf("Not 26 unique character\n");
                    return 1;
                }
            }
        }
    }

    string plain = get_string("plaintext:  ");
    printf("ciphertext:  ");
    for (int i = 0, lenplain = strlen(plain); i < lenplain; i++)
    {
        char cipher[lenplain];
        int diff;
        if (isupper(plain[i]))
        {
            diff = (plain[i] - 'A');
            cipher[i] = toupper(key[diff]);
        }
        else if (islower(plain[i]))
        {
            diff = (plain[i] - 'a');
            cipher[i] = tolower(key[diff]);
        }
        else
        {
            cipher[i] = plain[i];
        }
        printf("%c", cipher[i]);
    }
    printf("\n");
}