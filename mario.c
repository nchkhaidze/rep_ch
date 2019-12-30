#include <stdio.h>
#include <cs50.h>

int main (void) 
{
    // prompt user to enter the correct value
    int height;
    do 
    {
        height = get_int ("Height:\n ");
    }
    while (height < 1 || height > 8); 
    
    // loop the amount of rows
    for (int row = 0; row < height; row++)
    {
        // print the amount of spaces equal to height - (row + 1)
        for (int spaces = height - row; spaces > 1; spaces--)  
        {
            printf (" ");
        }
        // print the amount of hashes equal to row + 1
        for (int hash = 0; hash < row + 1; hash++)
        {
            printf ("#");
        }
        // print 2 spaces
        printf ("  ");
        // print amount of hashes equal to row + 1
         for (int hash = 0; hash < row + 1; hash++)
        {
            printf ("#");
        }
        //new line
        printf ("\n");
            
    }

}
