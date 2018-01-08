/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>

/* 
Helper function to print number from 1 to 999
number: number from 1 to 999
*/
void print_3_digits(int number)
{
    int hundreds_digit, tens_digit, unit_digit, remainder;

    /*basic_lookup[0] is empty. We want basic_lookup[1] to map to "One" 
    and so on. */
    char *basic_lookup[] = {"", "One", "Two", "Three", "Four", "Five", "Six",
            "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", 
            "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen",
            "Eighteen", "Nineteen"};

    /*tens_lookup[0] and tens_lookup[1] are empty.
    We want tens_lookup[2] to map to "Twenty" and so on. */
    char *tens_lookup[] = {"", "","Twenty", "Thirty", "Fourty", "Fifty", 
            "Sixty", "Seventy", "Eighty", "Ninety"};

    /*Suppose number is 987, then hundreds_digit is 9*/
    hundreds_digit = number / 100;
    if (hundreds_digit > 0) {
        printf("%s Hundred ", basic_lookup[hundreds_digit]);
    }
    
    /*Suppose number is 987, then remainder will be 87*/
    remainder = number % 100;
    if (remainder > 0) {
        if (remainder <= 19) {
            printf("%s ", basic_lookup[remainder]);         
        } else {
            tens_digit = remainder / 10;
            unit_digit = remainder % 10;
            printf("%s ", tens_lookup[tens_digit]);
            printf("%s ", basic_lookup[unit_digit]);
        }
    }
    
}


/*
Main function to print the number in words
number: any number from 0 to 999999999
*/
void print_num_in_words(int number)
{
    int millions, thousands, remainder;

    /*If number is 0, handle it here and return*/
    if (number == 0) {
        printf("Zero \n");
        return;
    }

    /*Suppose number is 123456789, then millions = 123, remainder = 456789*/
    millions = number / 1000000;
    remainder = number - (millions * 1000000);
    
    /*Suppose remainder = 456789, then thousands = 456, remainder = 789*/
    thousands = remainder / 1000;
    remainder = remainder - (thousands * 1000);

    if (millions > 0) {
        print_3_digits(millions);
        printf("Million ");
    }

    if (thousands > 0) {
        print_3_digits(thousands);
        printf("Thousand ");
    }

    if (remainder > 0) {
        print_3_digits(remainder);
    } 
    
    printf("\n");
}


void test(int x) 
{
    printf("%d in words = ", x);
    print_num_in_words(x);
}



int main() 
{
    test(0);
    test(8);
    test(15);
    test(75);
    test(100);
    test(512);
    test(987);
    test(1001);
    test(450012);
    test(816280);
    test(1000001);
    test(10011284);
    test(90145012);
    test(987654321);

    printf("Test passed\n");
    return 0;
}
