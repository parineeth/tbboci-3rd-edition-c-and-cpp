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

/*
str: string to be converted to an integer
Result: integer value of the string
*/
int function_atoi(const char * str)
{
    int i, length; 
    int val = 0;
    int is_negative = 0;

    if (!str)
        return 0;

    length = strlen(str);
    i = 0;
    if (str[0] == '-') {
        is_negative = 1;
        ++i;
    } 

    while (i < length ) {
        if (str[i] >= '0' && str[i] <= '9') {
            val = (val * 10) + (str[i] - '0');
        }
        else {
            break;
        }
        ++i;
    }
    
    if (is_negative)
        val = -1 * val;

    return val;
}

void test(char *str1, int expected_result)
{
    int result = function_atoi(str1);

    printf("%s => %d\n", str1, result);

    if (result != expected_result)
        handle_error();
}

int main()
{
    test("-47", -47);
    test("987", 987);
    test("", 0);


    printf("Test passed \n");
    return 0;
}
