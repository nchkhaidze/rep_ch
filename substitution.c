#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

string encrypt(int key[]);

int main(int argc, string argv[])
{
    //check if there are two command line arguments, print error if not
    if (argc != 2)
    {
        printf("Invalid command line argument\n");
        return 1;
    }
    //check if the length of the key is 26, print error if not
    unsigned const int key_len = 26;
    string key = argv[1];
    if (strlen(key) != key_len)
    {
        printf("Invalid key length\n");
        return 1;
    }
    int key_check[key_len];
    for (int i = 0; i < key_len; i++)
    {
        //check each character of the key whether it is alphabetic
        if (isalpha(key[i]) == 0)
        {
            printf("Non-alphabetic key\n");
            return 1;
        }
        // write each character down in an array as its alphabet order
        if (isupper(key[i]) != 0)
        {
            key_check[i] = key[i] - 'A';
        }
        else if (islower(key[i]) != 0)
        {
            key_check[i] = key[i] - 'a';
        }
    }
    //check the resulting array if it has any repeated characters
    for (int i = 0; i < key_len; i++)
    {
        int rep_char = 0;
        for (int j = 0; j < key_len; j++)
        {
            if (key_check[i] == key_check[j])
            {
                rep_char++;
            }
        }
        // > 1 because it compares number with itself at least once
        if (rep_char > 1)
        {
            printf("Repeated characters in the key\n");
            return 1;
        }
    }
    string ciphertext = encrypt(key_check);
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}

string encrypt(int key[])
{
    //prompt user for plaintext
    string plaintext = get_string("plaintext: ");
    //change each alphabetic character in the plaintext into its corresponding character from key
    for (int i = 0, pltext_len = (strlen(plaintext)); i < pltext_len; i++)
    {
        if (isupper(plaintext[i]) != 0)
        {
            plaintext[i] = plaintext[i] - 'A';
            plaintext[i] = key[(int)plaintext[i]] + 'A';

        }
        else if (islower(plaintext[i]) != 0)
        {
            plaintext[i] = plaintext[i] - 'a';
            plaintext[i] = key[(int)plaintext[i]] + 'a';
        }

    }
    return plaintext;
}