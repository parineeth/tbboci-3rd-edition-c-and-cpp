/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>


/*Helper function for printing the words corresponding to the telephone number
digits: array of digits from 0-9
num_digits: number of digits in the array
key_pad: contains the characters corresponding to each digit
buf: contains the word formed corresponding to the telephone digits
pos: current position in buf and digits
*/
void keypad_string_gen(int digits[], int num_digits, char *keypad[], 
            char buf[], int pos)
{
    int cur_digit, i;
    char *key_string;

    if (pos == num_digits) {
        /*We have processed all the digits. So print the 
        word and terminate the recursion*/
        buf[pos] = 0;
        printf("%s\n", buf);
        return;
    }

    cur_digit = digits[pos];
    key_string = keypad[cur_digit];

    /*key_string is the string corresponding to the current digit
    So if current digit is 2, key_string will be "ABC".
    Cycle through all the characters in the key_string.*/
    i = 0;
    while (key_string[i]) {
        buf[pos] = key_string[i];
        keypad_string_gen(digits, num_digits, keypad, buf, pos+1);
        i++;
    }
}

/*Main function for printing the words corresponding to the telephone number
digits: array of digits from 0-9 in the telephone number
num_digits: number of digits in the array
*/
void telephone_digits_to_string(int digits[], int num_digits)
{
    /*Create a temporary buffer for storing the words corresponding 
    to the digits*/
    char *buf = (char*) calloc(1, num_digits+1); 

    /*digit 2 corresponds to ABC, 3 corresponds to DEF and so on*/
    char *keypad[] = {"0", "1", "ABC", "DEF", "GHI", "JKL", "MNO", "PQRS", 
            "TUV", "WXYZ"};
        
    keypad_string_gen(digits, num_digits, keypad, buf, 0);
    
    free(buf);
}


int main()
{
    int digits[] = {4, 2, 1, 1, 8, 9, 2, 5, 0, 8};
    int num_digits = 10;

    telephone_digits_to_string(digits, num_digits);

    printf("Test passed\n");
    return 0;
}
