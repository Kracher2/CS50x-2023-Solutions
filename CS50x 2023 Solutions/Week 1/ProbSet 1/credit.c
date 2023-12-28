#include "cs50.h"
#include <stdio.h>

int main(void)
{
    long num = get_long("num: ");

    long num2 = num;

    int mod[16];
    for (int i = 1; i < 17; i++)
    {
        mod[i] = num % 10;
        num /= 10;
    }

    int second = 0;
    for (int j = 1; j < 9; j++)
    {
        mod[j * 2] *= 2;
        mod[j * 2] = (mod[j * 2] % 10) + (mod[j * 2] / 10) % 10;
        second += mod[j * 2] + mod[(j * 2) - 1];
    }

    if (second % 10 == 0 &&
        ((num2 >= 4000000000000 && num2 <= 4999999999999) || (num2 >= 4000000000000000 && num2 <= 4999999999999999) ||
         (num2 >= 340000000000000 && num2 <= 349999999999999) || (num2 >= 370000000000000 && num2 <= 379999999999999) ||
         (num2 >= 5100000000000000 && num2 <= 5599999999999999)))
    {
        if ((num2 >= 4000000000000 && num2 <= 4999999999999) || (num2 >= 4000000000000000 && num2 <= 4999999999999999))
        {
            printf("VISA\n");
        }
        else
        {
            if ((num2 >= 340000000000000 && num2 <= 349999999999999) || (num2 >= 370000000000000 && num2 <= 379999999999999))
            {
                printf("AMEX\n");
            }
            else
            {
                if (num2 >= 5100000000000000 && num2 <= 5599999999999999)
                {
                    printf("MASTERCARD\n");
                }
            }
        }
    }
    else
    {
        printf("INVALID\n");
    }
}