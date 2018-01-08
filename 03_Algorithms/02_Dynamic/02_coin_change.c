/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>

void handle_error()
{
    printf("Error occured \n");
    exit(1);
}

#define MAX_INT_VALUE (0x7FFFFFFF)



/*
denom: array having the coin denominations. Should have atleast 1 element
num_denom: number of denominations
final_amount: amount for which change has to be obtained
Return value: Minimum number of coins needed to represent final_amount
*/
int find_min_coins(int denom[], int num_denom, int final_amount) 
{
    /*Array for storing the minimum number of coins for an amount*/
    int *min_num_coins = (int*) malloc( (final_amount+1) * sizeof(int));
    
    /*Array for storing the coin denomination chosen for an amount*/
    int *chosen_denom = (int*) malloc( (final_amount+1) * sizeof(int));
    int i, cur_amt, smaller_amt, result;
        
    min_num_coins[0] = 0;
    for (cur_amt = 1; cur_amt <= final_amount; cur_amt++) {
        min_num_coins[cur_amt] = MAX_INT_VALUE;
        for (i = 0; i < num_denom; ++i) {
            if (denom[i] <= cur_amt) {
        
                smaller_amt = cur_amt - denom[i];

                if (1 + min_num_coins[smaller_amt] < 
                        min_num_coins[cur_amt]) {
                    min_num_coins[cur_amt] = 
                        1 + min_num_coins[smaller_amt];
                    chosen_denom[cur_amt] = denom[i];
                }
            }
        }
    }
    
    result = min_num_coins[final_amount];
    printf("Minimum number of coins = %d\n", result);

    /*print the chosen denominations to get the final amount*/
    cur_amt = final_amount;
    while (cur_amt > 0) {
        printf("%d ", chosen_denom[cur_amt]);
        cur_amt = cur_amt - chosen_denom[cur_amt];
    }
    printf(" = %d\n", final_amount);

    free(min_num_coins);
    free(chosen_denom);
    return result;
}


void print_array(int a[], int length)
{
    int i;
    for (i = 0; i < length; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}


int test_01()
{
    int denom[] = {1, 2, 3, 4, 5};
    int min_coins;
    int total_amount = 13;

    printf("Coin denominations : ");
    print_array(denom, 5);
    printf("Total amount needed = %d\n", total_amount);

    min_coins = find_min_coins(denom, 5, total_amount);

    if (min_coins != 3)
        handle_error();

    printf("_____________________________________________\n");

    return 0;
}


int test_02()
{
    int denom[] = {1, 2, 3, 4};
    int min_coins;
    int total_amount = 17;

    printf("Coin denominations : ");
    print_array(denom, 4);
    printf("Total amount needed = %d\n", total_amount);

    min_coins = find_min_coins(denom, 4, total_amount);

    if (min_coins != 5)
        handle_error();

    printf("_____________________________________________\n");

    return 0;
}

int test_03()
{
    int denom[] = {1, 5, 10, 25, 50};
    int min_coins;
    int total_amount = 30;

    printf("Coin denominations : ");
    print_array(denom, 5);
    printf("Total amount needed = %d\n", total_amount);

    min_coins = find_min_coins(denom, 5, total_amount);

    if (min_coins != 2)
        handle_error();

    printf("_____________________________________________\n");

    return 0;
}


int test_04()
{
    int denom[] = {1, 3, 4, 5};
    int min_coins;
    int total_amount = 7;

    printf("Coin denominations : ");
    print_array(denom, 4);
    printf("Total amount needed = %d\n", total_amount);

    min_coins = find_min_coins(denom, 4, total_amount);

    if (min_coins != 2)
        handle_error();

    printf("_____________________________________________\n");

    return 0;
}




int main()
{
    test_01();

    test_02();

    test_03();

    test_04();

    printf("Test passed\n");
    return 0;
}


