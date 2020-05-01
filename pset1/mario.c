#include <cs50.h>
#include <stdio.h>

//        #
//       ##
//      ###
//     ####
//    #####
//   ######
//  #######
// ########

int main(void)
{
    int number;

    do 
    {
        number = get_int("Height: ");
    }
    while (number <= 0 || number > 8);

    for (int i = 0; i < number; i++)
    {
        for (int j = 0; j < number - i - 1; j++)
        {
            printf(" ");
        }
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}
