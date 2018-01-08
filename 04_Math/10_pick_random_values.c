/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>


void handle_error(void)
{
    printf("Test failed\n");
    exit(1);
}

/*Returns a random number between low and high, low and high are inclusive*/
int get_random_number(int low, int high)
{
    int random_num = low + rand() % (high - low + 1);

    return random_num;
}

/*
a: input array of unsorted numbers
n: number of elements in array a
k: number of random values to pick
result: the k random values will be stored in result
*/
void pick_random_values(int a[], int n, int k, int result[])
{
    int j, rand_index, last_index;

    /*We will need to rearrange the elements in array a. Since the user
    may expect array a to remain unchanged, we are allocating memory 
    for another array b and copying elements of a into b*/
    int *b = (int*) calloc(n, sizeof(int));

    for (j = 0; j < n; ++j)
        b[j] = a[j];

    j = 0;
    last_index = n-1; 
    while (j < k) {
        /*Pick a random position from 0 to last_index*/
        rand_index = get_random_number(0, last_index);

        /*Store b[rand_index] in the result*/
        result[j] = b[rand_index];

        /*Let's say original value at b[rand_index] is x.
        b[rand_index] is now overwritten with b[last_index].  
        So we cannot choose x again in the next iterations*/
        b[rand_index] = b[last_index];

        --last_index;
        ++j; 
    }

    free(b);  
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
    int a[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
    int n = 10; /*number of elements in a*/
    int k = 5;  /*number of random values to be chosen*/
    int result[5];

    printf("Input : ");
    print_array(a, n);

    pick_random_values(a, n, k, result);

    printf("The random values are: ");
    print_array(result, k); 

    printf("Test passed\n");
    
    return 0;
}

