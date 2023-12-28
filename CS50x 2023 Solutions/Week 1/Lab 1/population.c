#include "cs50.h"
#include <stdio.h>

int main(void)
{
    int start;
    do
    {
        start = get_int("Start size: ");
    }
    while (start < 9);

    int end;
    do
    {
        end = get_int("End size: ");
    }
    while (end < start);

    int years = 0;

    if (start != end)
        do
        {
            start = start + start / 3 - start / 4;
            years++;
        }
        while (start < end);

    printf("Years: %i\n", years);
}
