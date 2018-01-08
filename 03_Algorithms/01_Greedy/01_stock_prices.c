/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_NUM_TESTS 10
#define MAX_NUM_ELEMENTS 10
#define MAX_VALUE 100


void handle_error()
{
    printf("Error occured\n");
    exit(1);
}



/*
stock_price: array of stock price values
n: number of elements in the array
Return value: maximum profit possible
*/
int find_max_profit(int stock_price[], int n)
{
    int i, min_stock_price, cur_profit, max_profit;

    max_profit = 0;
    if (n <= 1)
        return max_profit;

    min_stock_price = stock_price[0];

    for (i = 1; i < n; ++i) {
        
        cur_profit = stock_price[i] - min_stock_price;

        if (cur_profit > max_profit)
            max_profit = cur_profit;

        if (stock_price[i] < min_stock_price)
            min_stock_price = stock_price[i];
    }

    return max_profit;
}





int find_brute_force_max_profit(int stock_price[], int n)
{
    int cur_profit, max_profit;
    int i, j;


    max_profit = 0;
    if (n <= 1)
        return max_profit;

    for (i = 0; i < n - 1; ++i) {
        for (j = i+1; j < n ; ++j) {
            if (stock_price[j] > stock_price[i]) {
                cur_profit = stock_price[j] - stock_price[i];
                if (cur_profit > max_profit)
                    max_profit = cur_profit;
            }

        }
    }


    return max_profit;

}


void print_array(int a[], int length)
{
    int i;
    for (i = 0; i < length; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}




int main()
{
    int a[MAX_NUM_ELEMENTS];
    int result, brute_force_result;
    int i, test_nr, num_elements;

    for (test_nr = 0; test_nr < MAX_NUM_TESTS; ++test_nr) {
        /*Randomly pick the number of elements*/
        num_elements = 1 + (rand() % MAX_NUM_ELEMENTS);

        /*Add random share values to the array*/
        for (i=0; i < num_elements; ++i)
            a[i] = rand() % MAX_VALUE;

        printf("Input : ");
        print_array(a, num_elements);

        /*Find the best profit possible*/
        result = find_max_profit(a, num_elements);

        printf("Maximum profit = %d\n", result);

        /*Find the best profit using the brute force approach*/
        brute_force_result = find_brute_force_max_profit(a, num_elements);

        /*Both results should match*/
        if (result != brute_force_result)
            handle_error();

        printf("__________________________________________________\n");

    }


    printf("Test passed\n");
    return 0;

}
