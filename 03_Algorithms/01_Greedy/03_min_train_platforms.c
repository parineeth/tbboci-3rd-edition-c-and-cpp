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


void print_array(int a[], int length) 
{
    int i;
    
    for (i = 0; i < length; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

/*Function for comparing two elements. This function used while sorting*/
int cmp_function(const void *p1, const void *p2)
{
    int *x = (int *)p1;
    int *y = (int *)p2;

    if (*x < *y)
        return -1;
    else if (*x == *y)
        return 0;
    else 
        return 1;
}


void sort(int a[], int length)
{
    qsort(a, length, sizeof(int), cmp_function);
}


/*
arrival: array containing the arrival time of the trains
departure: array containing the departure time of the trains
n: length of arrays. Both arrays should have same length
Return value: minimum number of train platforms needed
*/
int find_min_platforms(int arrival[], int departure[], int n)
{
    int cur_num_platforms, min_num_platforms;
    int i, j;

    if (n == 0)
        return 0;

    /*Sort arrival and departure time independently in non-decreasing order*/
    sort(arrival, n);
    sort(departure, n);

    cur_num_platforms = min_num_platforms = 1;
    i = 1; /*i is used for traversing arrival*/
    j = 0; /*j is used for traversing departure*/

    while (i < n && j < n) {
        if (arrival[i] < departure[j]) {
            /*A new train is coming in before a train departs. So  
            we need an extra platform*/
            cur_num_platforms++;
            if (cur_num_platforms > min_num_platforms)
                min_num_platforms = cur_num_platforms;
            ++i;
        } else if (arrival[i] == departure[j]) {
            /*A train arrives at the same time as a departing train.  
            So we don't need an extra platform*/
            ++i;
            ++j;
        } else {
            /*A train departs before the new train arrives. So a  
            platform is freed up*/
            cur_num_platforms--;
            j++;
        }
    }

    return min_num_platforms;
}




void test_01()
{
    int arrival[] = {800, 900, 945, 1300, 1500, 1530, 1545 };
    int departure[] = {1030, 915, 1100, 1400, 1545, 1830, 1715 };
    int n = 7;
    int result, expected_result ;

    printf("Arrival: ");
    print_array(arrival, n);

    printf("Departure: ");
    print_array(departure, n);

    result = find_min_platforms(arrival, departure, n);

    printf("Minimum number of platforms = %d\n", result);

    expected_result = 2;

    if (result != expected_result)
        handle_error();

    printf("__________________________________\n");
    
}




int main()
{
    test_01();


    printf("Test passed\n");
    return 0;
}
