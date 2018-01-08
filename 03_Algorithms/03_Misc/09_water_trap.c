#include <stdio.h>
#include <stdlib.h>



void handle_error()
{
    printf("Error occured\n");
    exit(1);
}


int max(int a, int b)
{
    return (a > b ? a : b);
}

int min(int a, int b)
{
    return (a < b ? a : b);
}

/* 
histogram: histogram[i] contains the height of the bar at location i
n: number of bars in the histogram. Should be >= 1
Return value: amount of water that can be trapped by the histogram 
*/
int water_trap(int histogram[], int n)
{
    int i, total_water, smaller_max;
    int *left_max = (int *) calloc(n, sizeof(int));
    int *right_max = (int *) calloc(n, sizeof(int));

    /*The left max of bar i is the height of the tallest bar in the 
    region (0, i). Note that region (0, i) includes 0 and i*/
    left_max[0] = histogram[0];
    for (i = 1; i < n; ++i) {
        left_max[i] = max(left_max[i-1], histogram[i]);
    }

    /*The right max of bar i is the height of the tallest bar in the 
    region (i, n-1). Note that region (i, n-1) includes i and n-1*/
    total_water = 0;
    right_max[n-1] = histogram[n-1];
    for (i = n - 2; i >= 0; --i) {
        /*Compute the right max and simultaneously calculate the 
        amount of water that can be trapped*/
        right_max[i] = max(right_max[i+1], histogram[i]);
        
        smaller_max = min(left_max[i], right_max[i]);

        /*calculate the amount of water that can be stored
        on top of the histogram bar i*/
        total_water += smaller_max - histogram[i];
    }

    free(left_max);
    free(right_max);
    
    return total_water;
}


void test()
{
    int histogram[] = { 3, 1, 4, 0, 2, 5, 0, 3, 2};
    int n = 9;
    int total_water = water_trap(histogram, n);

    printf("Total water trapped = %d\n", total_water);

    if (total_water != 11)
        handle_error();
    
}


int main()
{
    test();

    printf("Test passed \n");
    return 0;
}


