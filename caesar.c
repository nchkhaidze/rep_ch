#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //check if the user gives only one argument for the function, otherwise print error
    if (argc != 2)
    {
        printf("Invalid command line argument\n");
        return 1;
    }
    int arg_len = strlen(argv[1]);
    char key_array[arg_len];
    // loop through all the characters of the second word in function argument
    for (int i = 0, n = 0; i < arg_len; i++)
    {
        //check each character if it is a decimal digit
        //if it is a decimal digit, then write its character down in an array for key
        //otherwise print error
        if ((argv[1][i] >= '0') && (argv[1][i] <= '9'))
        {
            key_array[n] = argv[1][i];
            n++;
        }
        else
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    //convert the contents of the key array into integer
    int key = atoi(key_array);
    printf("%i\n", key);
    //prompt the user for plaintext input
    string plaintext = get_string("plaintext: ");
    //loop through plaintext string and if the string element is an alphabet letter, shift it by key position within alphabet letters
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if ((plaintext[i] >= 'a') && (plaintext[i] <= 'z'))
        {
            plaintext[i] = (((plaintext [i] - 'a') + key)) % 26 + 'a';
        }
        else if ((plaintext[i] >= 'A') && (plaintext[i] <= 'Z'))
        {
            plaintext[i] = (((plaintext [i] - 'A') + key)) % 26 + 'A';
        }
    }
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        printf("%c %i\n", plaintext[i], plaintext[i]);
    }
}



