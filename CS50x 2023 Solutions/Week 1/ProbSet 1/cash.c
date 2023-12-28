#include "cs50.h"
#include <stdio.h>

int main(void)
{
    int cents;
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);

    int quarters;
    for (quarters = 0; cents >= 25; quarters++)
    {
        cents -= 25;
    }

    int dimes;
    for (dimes = 0; cents >= 10; dimes++)
    {
        cents -= 10;
    }

    int nickels;
    for (nickels = 0; cents >= 5; nickels++)
    {
        cents -= 5;
    }

    int pennies;
    for (pennies = 0; cents > 0; pennies++)
    {
        cents -= 1;
    }

    int coins = quarters + dimes + nickels + pennies;

    printf("%i\n", coins);
}
