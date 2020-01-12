#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)
{
    // prompt user for text, initiate counter variables for letters, words, sentences
    string text = get_string("Text: ");
    const int str_len = strlen(text);
    int letter_count = 0;
    int word_count = 0;
    int sentence_count = 0;
    // scroll through the text, finding key symbols to count letters, words, sentences
    for (int i = 0; i < str_len; i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text [i] <= 'Z'))
        {
            letter_count++;
        }
        else if (text[i] ==  ' ')
        {
            word_count++;
        }
        else if ((text[i] == '.') || (text[i] == '?') || (text[i] == '!'))
        {
            sentence_count++;
        }
    }
    // add one word if there was any symbol input, because first word in the text is not counted by the "for" loop
    if (letter_count > 0)
    {
        word_count++;
    }
    //count Coleman-Liau index, round it to the nearest integer, print final grade depending on the result
    float index = (0.0588 * letter_count / word_count * 100) - (0.296 * sentence_count / word_count * 100) - 15.8;
    int grade = roundf(index);
    if ((index >= 1) && (index < 16))
    {
        printf("Grade %i\n", grade);
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
}

