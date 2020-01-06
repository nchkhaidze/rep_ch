#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void) 
{
    // makes sure the number is not a negative, otherwise prints invalid
    long long number = get_long_long("Enter credit card number:\n");
    if (number <= 0)
    {
        printf("INVALID\n");
    }
    //counts the amount of digits in the number
    else 
    {
        int amount_of_digits = 0;
        long long counter_digits = number;
        while (counter_digits > 0) 
        {
            amount_of_digits++;
            counter_digits /= 10;
        }
        //makes sure the amount of digits is correct for a credit card, otherwise prints invalid
        if ((amount_of_digits == 16) || (amount_of_digits == 15) || (amount_of_digits == 13))
        {
            int underlined_digit;
            int sum_products = 0;
            int not_multiplied;
            int sum_not_multiplied = 0;
            bool underlined = false;
            long long n = 1;      
            //scrolls through all the digits
            for (int i = 0; i < amount_of_digits; i++)
            {
                //if the digit is underlined, multiplies by two; if it is 10 or more presents it as a sum of digits
                //adds the products' digits into one sum
                if (underlined == true)
                {
                     underlined_digit = ((number / n) % 10) * 2;
                     if (underlined_digit > 9) 
                     {
                     underlined_digit = (underlined_digit % 10) + 1;
                     }
                     sum_products = sum_products + underlined_digit;
                     underlined = false;
                }
                // if the digit is not being multiplied, just adds it to a sum
                else 
                {
                    not_multiplied = (number / n) % 10;
                    sum_not_multiplied = sum_not_multiplied + not_multiplied;                    
                    underlined = true;
                }
                n = n * 10;
            }
            if ((sum_products + sum_not_multiplied) % 10 == 0) 
            {
                //finds the first two digits 
                long long count_type = number;
                int first_two;
                int first_digit;
                while (count_type >= 100)
                {
                    count_type = count_type / 10;
                }
                first_two = count_type;
                first_digit = count_type / 10;
                //figures out and prints card type
                if (first_digit == 4) 
                {
                    printf("VISA\n");
                }
                else if ((first_two == 34) || (first_two == 37)) 
                {
                    printf("AMEX\n");
                }
                else if ((first_two == 51) || (first_two == 52) || (first_two == 53) || (first_two == 54) || (first_two == 55))
                {
                    printf("MASTERCARD\n");
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
        else 
        {
            printf("INVALID\n");
        }
    }
   
    
   
    
  
}
