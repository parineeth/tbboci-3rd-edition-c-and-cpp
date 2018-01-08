/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_STRING_LENGTH 100

void handle_error(void)
{
    printf("Test failed\n");
    exit(1);
}


/*Helper function which reverses a string between indexes low and high
str1: string which needs to be reversed
low: lower index of region to be reversed
high: higher index of region to be reversed
*/
void reverse_string(char str1[], int low, int high)
{
    char temp;

    while (low < high) {
        temp = str1[low];
        str1[low] = str1[high];
        str1[high] = temp;
        low++;
        high--;
    }
}

/*Helper function which checks if a character is an alphabet(a-zA-Z)*/
int is_alphabet(char c)
{
    if (c >= 'A' && c <= 'Z')
        return 1;

    if (c >= 'a' && c <= 'z')
        return 1;

    return 0;       
}


/*Main function to reverse the words in a string
str1: the string in which the words have to be reversed
*/
void reverse_words(char str1[])
{
    int length, low, high, pos;
    
    length = strlen(str1);
    if (length < 2)
        return;

    /*Reverse the entire string*/
    reverse_string(str1, 0, length - 1);

    /*Reverse the individual words in the string*/
    pos = 0;
    while (pos < length) {
        if (is_alphabet(str1[pos])) {
            low = pos;
            while (pos < length && is_alphabet(str1[pos])) {
                pos++;
            }
            high = pos - 1;
            reverse_string(str1, low, high);
        } else {
            pos++;
        }   
    }
}


void test(char str1[], char expected_result[])
{
    printf("%s ", str1);

    reverse_words(str1);

    printf("=>  %s\n", str1);

    if (strcmp(str1, expected_result) != 0)
        handle_error();

}









int main()
{
    char str1[MAX_STRING_LENGTH];

    str1[0] = 0;    
    test(str1, "");

    strcpy(str1, "a");
    test(str1, "a");

    strcpy(str1, "Hello how are you");
    test(str1, "you are how Hello");


    printf("Test passed\n");
    return 0;
}
