#include <stdio.h>
#include <cs50.h>
#include <math.h>
int main(void)
{
    float dollars;
    int cents;
    int counter = 0;

    do 
    {
        dollars = get_float("Change owed: ");
    } 
    while (dollars < 0);

    cents = round(dollars * 100);

    while (cents >= 25)
    {
        cents = cents - 25;
        counter++;
    }

    while (cents >= 10)
    {
        cents = cents - 10;
        counter++;
    }

    while (cents >= 5)
    {
        cents = cents - 5;
        counter++;
    }

    while (cents >= 1)
    {
        cents = cents - 1;
        counter++;
    }
    printf("%d\n", counter);
}
