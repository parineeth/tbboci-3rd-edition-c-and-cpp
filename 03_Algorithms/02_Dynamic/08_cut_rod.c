/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>


#define MAX_NUM_TESTS (100)
#define MAX_LENGTH (10)
#define MAX_VALUE     (10)



void handle_error()
{
    printf("Error occured \n");
    exit(1);
}

int max(int a, int b)
{
    return (a > b ? a : b);
}

/*Helper function for printing out the sizes of the individual pieces*/
void print_pieces(int first_cut[], int total_length)
{
    int cur_length;

    printf("The rod piece lengths are : ");

    cur_length = total_length;
    while (cur_length > 0 && first_cut[cur_length] > 0) {
        printf("%d ", first_cut[cur_length]);
        cur_length = cur_length - first_cut[cur_length];
    }
    
    printf("\n");   
}

/*
price: price[i] gives the price of a rod of length i. price[0] is 0
total_length: the total length of the rod given to us. Should be >= 1
Return value: the best value that can be fetched from the rod 
*/
int cut_rod(int price[], int total_length)
{
    /*Initialize best_value to 0*/
    int *best_value = (int*) calloc(total_length + 1, sizeof(int));
    
    /*first_cut[i] will indicate the length of the first piece when we cut 
    the rod of length i. This is needed to print out where we should cut 
    so that we get the best value*/
    int *first_cut = (int*) calloc(total_length + 1, sizeof(int));
    int i, cur_length, result;

    for (cur_length = 1; cur_length <= total_length; ++cur_length) {
        /*We are cutting a rod whose length is cur_length
        The length of the first piece after the cut can range from 
        1 to cur_length*/
        for (i = 1; i <= cur_length; ++i) {
            if (price[i] + best_value[cur_length - i] > 
                    best_value[cur_length]) {
                best_value[cur_length] = price[i] + 
                        best_value[cur_length - i];
                first_cut[cur_length] = i;
            }
        }
    }
    
    print_pieces(first_cut, total_length);
    
    result = best_value[total_length];
    free(first_cut);    
    free(best_value);
    
    return result;
}


int cut_rod_recursive(int price[], int cur_length)
{
    int i, best_value;

    if (cur_length <= 0)
        return 0;

    best_value = price[cur_length];
    for (i = 1; i < cur_length; ++i) {
        best_value = max(best_value, price[i] + cut_rod_recursive(price, cur_length - i));
    }

    return best_value;
}


void print_array(int price[], int num_elems) 
{
    int i;

    printf("Length: ");
    for (i = 0; i < num_elems; ++i)
        printf("%d ", i);
    printf("\n");
    
    printf("Price : ");
    for (i = 0; i < num_elems; ++i) {
        printf("%d ", price[i]);
    }
    
    printf("\n");
}


void test()
{
    int price[MAX_LENGTH+1];    
    int i, length;
    int result, expected_result;

    /*Randomly decide the length*/
    length = 1 + rand() % MAX_LENGTH;

    price[0] = 0;
    /*Randomly fill in the remaining prices*/
    for (i = 1; i <= length; ++i) {
        price[i] = rand() % MAX_VALUE;
    }

    print_array(price, length + 1);

    /*Find the result using an efficient technique*/
    result = cut_rod(price, length);
    
    printf("Max value = %d \n", result);


    /*Find the result using the recursive technique*/
    expected_result = cut_rod_recursive(price, length);


    /*The two results should match*/
    if (result != expected_result) {
        handle_error();
    }


    printf("________________________________________________\n");

}



int main() 
{
    int i;

    for (i = 0; i < MAX_NUM_TESTS; ++i) {
        test();
    }

    printf("Test passed\n");
    return 0;
}


