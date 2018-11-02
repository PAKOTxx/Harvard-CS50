#include <stdio.h>
#include <cs50.h>

int main()
{
    int height, width, row_counter, col_counter;
    do
    {
        printf("Please give me a non-negative integer no greater than 23: "); 
        height = GetInt();
    } 
    while (height < 0 || height > 23);
    printf("Thank you for the valid integer!\nHere is Mario's half-pyramid of height %i:\n", height);
    
    width = height + 1;
    
    for (row_counter = 1; row_counter <= height; row_counter++)  
    {
        for (col_counter = 1; col_counter <= width; col_counter++)
        {
            if (col_counter <= width - (row_counter + 1))
                printf(" ");
            else
                printf("#");
        }
        printf("\n");
    }
    return 0;
}