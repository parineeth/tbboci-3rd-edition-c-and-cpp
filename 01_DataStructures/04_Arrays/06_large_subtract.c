/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_ARRAY_SIZE (10)
#define MAX_NUM_TESTS (10)
#define MAX_VALUE (10000)


void handle_error()
{
    printf("Error occured \n");
    exit(1);
}

void print_array(char a[], int length)
{
    int i;
    for (i = 0; i < length; ++i) {
        printf("%d", a[i]);
    }

}

void reverse_array(char a[], int length)
{
    int i;
    char temp;

    for (i = 0; i < length / 2; ++i) {
        temp = a[i];
        a[i] = a[length - 1 - i];
        a[length - 1 - i] = temp;
    }
}

int convert_num_to_array(int num, char a[])
{
    int pos, length, remainder;
    
    a[0] = 0;
    length = 0;
    pos = 0;
    while (num > 0) {
        remainder = num % 10;
        a[pos] = remainder;
        pos++;
        num = num / 10;
    }

    /*reverse the string*/
    length = pos;
    
    reverse_array(a, length);
    return length;
}

int convert_array_to_num(char a[], int length)
{
    int i, num;

    num = 0;
    for (i = 0; i < length; ++i) {
        num = (num * 10) + a[i];
    }

    return num;
}

void print_result(char num1[], int length1, char num2[], int length2, char result[], 
            int result_length, char is_negative)
{
    print_array(num1, length1);

    printf(" - ");

    print_array(num2, length2);

    printf (" = ");

    if (is_negative)
        printf(" -");

    print_array(result, result_length);

    printf("\n");
}

/*Helper function which returns 1 if num1 is smaller than num2*/
int is_smaller(char num1[], int length1, char num2[], int length2)
{
    int i;

    if (length1 > length2)
        return 0;

    if (length1 < length2)
        return 1;

    for (i = 0; i < length1; ++i) {
        if (num1[i] > num2[i])
            return 0;

        if (num1[i] < num2[i])
            return 1;
    }
    
    return 0;   
}

/*
num1 and num2: arrays which store the digits of the two numbers. 
    The two arrays store numeric value of the digits and not ascii values
length1 and length2: number of digits in arrays num1 and num2
result: result array which contains num1 - num2
is_negative: indicates if the result is negative or not
*/
int large_subtract(char num1[], int length1, char num2[], int length2, 
            char result[], char *is_negative)
{
    int i, difference, borrow, temp_length;
    int pos1, pos2;
    char *temp_ptr;
    
    *is_negative = 0;

    /*Store larger number in num1
    So if num1 is smaller than num2, then swap num1 and num2*/
    if (is_smaller(num1, length1, num2, length2) ) {
        /*Swap num1 and num2*/
        temp_ptr = num1; num1 = num2; num2 = temp_ptr;

        /*Swap length1 and length2*/
        temp_length = length1; length1 = length2; length2 = temp_length;

        /*If num1 was smaller than num2, then result will be negative*/
        *is_negative = 1;
    } 

    for (i = 0; i < length1; ++i) 
        result[i] = 0;

    /*Perform the subtraction for all the digits in num2*/
    pos1 = length1 - 1;
    pos2 = length2 - 1;
    borrow = 0;
    while (pos2 >= 0) {
        difference = num1[pos1] - num2[pos2] - borrow;
        if (difference < 0) {
            difference += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result[pos1] = difference; 
        pos1--;
        pos2--; 
    }

    /*Process any digits leftover in num1*/
    while (pos1 >= 0) {
        difference = num1[pos1] - borrow;
        if (difference < 0) {
            difference += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result[pos1] = difference; 
        pos1--;
    }

    return length1; 
}


int main()
{

    char num1[MAX_ARRAY_SIZE], num2[MAX_ARRAY_SIZE], result[MAX_ARRAY_SIZE]; 
    int length1, length2, result_length, test_nr;
    int val1, val2, val3;
    char is_negative;

    for (test_nr = 0; test_nr < MAX_NUM_TESTS; ++test_nr) {

        /*Generate a random value val1 and store its digits in the array num1*/
        val1 = rand() % MAX_VALUE;
        length1 = convert_num_to_array(val1, num1);

        /*Generate a random value val2 and store its digits in the array num2*/
        val2 = rand() % MAX_VALUE;
        length2 = convert_num_to_array(val2, num2);

        /*Perform the subtraction*/
        result_length = large_subtract(num1, length1, num2, length2, result, &is_negative);

        print_result(num1, length1, num2, length2, result, result_length, is_negative);

        /*Verify the result*/
        val3 = convert_array_to_num(result, result_length);
        if (is_negative)
            val3 = val3 * -1;

        if (val3 != (val1 - val2))
            handle_error();

    }

    printf("Test passed\n");
    return 0;
}




