#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long numberType = get_long("Number: ");
    long number = numberType;
    long numberHead1;
    long numberHead2;
    long cardValidateHead;
    int count = 0;
    int checksum = 0;

    while (number != 0)
    {
        if (count % 2 != 0)
        {
            checksum = checksum + (number % 10) * 2 / 10 + (number % 10) * 2 % 10;
        }
        else
        {
            checksum = checksum + number % 10;  
        }

        //record the first and second number 
        numberHead2 = numberHead1;
        numberHead1 = number % 10;
            
        number = number / 10;
        count++;
        // printf("numberHead1: %ld, numberHead2: %ld\n", numberHead1, numberHead2);
    }      

    checksum = checksum % 10;
    cardValidateHead = numberHead1 * 10 + numberHead2;
    // printf("%d\n", checksum);
    // printf("%d\n", count);s
    if (checksum == 0)
    {
        if (count == 15 && ((cardValidateHead == 34) || (cardValidateHead == 37))) 
        {
            printf("AMEX\n");
        }
        else if (count == 16 && ((cardValidateHead >= 51) && (cardValidateHead <= 55)))
        {
            printf("MASTERCARD\n");  
        }
        else if ((numberHead1 == 4) && (count == 13 || count == 16))
        {
            printf("VISA\n");  
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }        
}
