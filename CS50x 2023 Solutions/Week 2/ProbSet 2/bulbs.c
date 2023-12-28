#include "cs50.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string phrase = get_string("Message: ");
    for (int i = 0, len = strlen(phrase); i < len; i++)
    {
        int iphrase[len];
        iphrase[i] = phrase[i];

        for (int j = 7; j >= 0; j--)
        {
            if (iphrase[i] >= pow(2, j))
            {
                iphrase[i] = iphrase[i] - pow(2, j);
                printf("\U0001F7E1");
            }
            else
            {
                printf("\U000026AB");
            }
        }
        printf("\n");
    }
}
