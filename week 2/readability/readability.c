#include <cs50.h>
#include <stdio.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
// prompt for sentence
    string text = get_string("Text: ");

// check for number of letters
    int noOfLetters = count_letters(text);

// check for number of words
    int noOfWords = count_words(text);

// check for number of sentences
    int noOfSentences = count_sentences(text);

    float L = (float) noOfLetters / (float) noOfWords * 100;
    float S = (float) noOfSentences / (float) noOfWords * 100;
    float unroundedIndex = 0.0588 * L - 0.296 * S - 15.8;
    printf("%f\n", unroundedIndex);
    int index = unroundedIndex;
    printf("%i\n", index);
    float remainder = unroundedIndex - index;
    printf("%f\n", remainder);
    if (remainder >= 0.5)
    {
        index += 1;
    }
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
    // printf("%i letters\n", noOfLetters);
    // printf("%i words\n", noOfWords);
    // printf("%i sentences\n", noOfSentences);
}

// count letters
int count_letters(string text)
{
    int i = 0;
    int count = 0;
    while (text[i] != '\0')
    {
        char x = text[i];
        if ((x >= 65 && x <= 90) || (x >= 97 && x <= 122))
        {
            count += 1;
        }
        i++;
    }
    return count;
}

// count words
int count_words(string text)
{
    int i = 0;
    int count = 0;
    while (text[i] != '\0')
    {
        char x = text[i];
        if (x == 32)
        {
            count += 1;
        }
        i++;
    }
    int words = count + 1;
    return words;
}

// count sentences
int count_sentences(string text)
{
    int i = 0;
    int count = 0;
    while (text[i] != '\0')
    {
        char x = text[i];
        if (x == 46 || x == 63 || x == 33)
        {
            count += 1;
        }
        i++;
    }
    return count;
}