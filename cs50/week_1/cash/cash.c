#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // Input change by user
    float change;
    do
    {
        change = get_float("Change owed: ");
    }
    while (change <= 0.00);

    // Turn float to int
    int cents = round(change * 100);

    // Coins counter
    int coins = 0;

    // add 0.25
    while (cents > 24)
    {
        cents = cents - 25;
        coins++;
    }
    // add 0.10
    while (cents < 25 && cents > 9)
    {
        cents = cents - 10;
        coins++;
    }
    //add 0.05
    while (cents < 10 && cents > 4)
    {
        cents = cents - 5;
        coins++;
    }
    //add 0.01
    while (cents < 5 && cents > 0)
    {
        cents = cents - 1;
        coins++;
    }
    printf("%i\n", coins);
}