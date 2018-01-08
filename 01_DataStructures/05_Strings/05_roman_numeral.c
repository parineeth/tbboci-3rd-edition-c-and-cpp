/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void handle_error()
{
    printf("Error occured \n");
    exit(1);
}

/*Helper function that returns the numeric value of a Roman alphabet*/
int get_numeric_value(char c)
{
    int result;

    switch(c) {
        case 'I': result = 1; break;
        case 'V': result = 5; break;
        case 'X': result = 10; break;
        case 'L': result = 50; break;
        case 'C': result = 100; break;
        case 'D': result = 500; break;
        case 'M': result = 1000; break;
        default: result = 0; break;
    }
    return result;
}


/* 
Main function that converts a Roman string into an integer
str1: valid input string with Roman alphabets
Return value: integer equivalent of the Roman string
*/
int roman_to_int(char *str1) 
{
    int i, result;
    
    /*Process the string from the rear*/
    i = strlen(str1) - 1;
    if (i < 0)
        return 0;
    
    result = get_numeric_value(str1[i]);
    --i;
    while (i >= 0) {
        int cur_value = get_numeric_value(str1[i]);
        int next_value = get_numeric_value(str1[i+1]);

        if (cur_value < next_value)
            result -= cur_value;
        else
            result += cur_value;        
            
        --i;
    }
    
    return result;
}


void test(char *str1, int expected_result)
{
    int result = roman_to_int(str1);

    printf("%s => %d\n", str1, result);

    if (result != expected_result)
        handle_error();
}


int main()
{
    test("MMCX", 2110);
    test("MMXC", 2090);
    test("LIX", 59);
    test("LVIIII", 59);
    test("X", 10);
    test("", 0);

    printf("Test passed \n");
    return 0;
}
