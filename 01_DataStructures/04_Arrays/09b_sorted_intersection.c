/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_NUM_TESTS (10)
#define MAX_NUM_ELEMS (10)
#define MAX_VALUE     (10)

void handle_error(void)
{
    printf("Test failed\n");
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

int cmp_function(const void *p1, const void *p2)
{
    int *x = (int*)p1;
    int *y = (int*)p2;

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
a, b: two input arrays whose intersection has to be found
length1, length2: number of elements in array a and b
result: array containing the result of intersection of a and b
Returns: number of elements in the result array 
*/
int find_intersection(int a[], int length1, int b[], int length2, int result[])
{
    int i, j, result_pos;

    /*Sort the two arrays in non-decreasing order*/
    sort(a, length1);
    sort(b, length2);

    i = j = result_pos = 0;
    while (i < length1 && j < length2) {
        /*Check if the elements in a and b match*/
        if (a[i] == b[j]) {
            /*Add only unique elements to the result*/
            if (i == 0 || a[i] != a[i - 1]) {
                result[result_pos] = a[i];
                ++result_pos;
            }
            ++i; 
            ++j; 

        } else if (a[i] < b[j]) {
            ++i;
        } else {
            ++j;
        }
    }
    return result_pos;
}






void generate_array(int a[], int length)
{
    int i;
    
    for (i = 0; i < length; ++i) {
        a[i] = rand() % MAX_VALUE;
    }
}

/*
a, b: two input arrays whose intersection has to be found
length1, length2: number of elements in array a and b
result: array containing the result of intersection of a and b
Returns: number of elements in the result array 
*/
int brute_force_intersection(int a[], int length1, int b[], int length2, int result[])
{
    int i, j, result_pos;
    int found;
    
    i = result_pos = 0;

    for (i = 0; i < length1; ++i) {
        /*Search for a[i] in array b*/
        found = 0;
        for (j = 0; j < length2; ++j) {
            if (a[i] == b[j]) {
                found = 1;
                break;
            }
        }

        if (!found)
            continue;

        /*We have found a[i] in b. Now make sure that a[i] is not 
        already present in the result*/
        found = 0;
        for (j = 0; j < result_pos; ++j) {
            if (a[i] == result[j]) {
                found = 1;
                break;
            }
        }
        
        if (!found) {
            /*a[i] is present in b and a[i] is not present in result. So add 
            it to result*/
            result[result_pos] = a[i];
            result_pos++;
        }
        
    }

    return result_pos;
}


void test()
{
    int a[MAX_NUM_ELEMS], b[MAX_NUM_ELEMS], c[MAX_NUM_ELEMS], d[MAX_NUM_ELEMS]; 
    int length1, length2, length3, length4;
    int i;

    /*Randomly decide the number of elements in the two arrays*/
    length1 = 1 + rand() % MAX_NUM_ELEMS;
    length2 = 1 + rand() % MAX_NUM_ELEMS;

    /*Fill the arrays with random values*/
    generate_array(a, length1);
    generate_array(b, length2);


    printf ("A : ");
    print_array(a, length1);

    printf ("B : ");
    print_array(b, length2);

    /*Find the intersection of a and b. The result will be in c*/
    length3 = find_intersection(a, length1, b, length2, c);

    printf ("Intersection : ");
    print_array(c, length3);

    /*Apply brute force to find the intersection. The result will be in d*/
    length4 = brute_force_intersection(a, length1, b, length2, d);

    /*The two results should match*/
    if (length3 != length4)
        handle_error();

    for (i = 0; i < length3; ++i) {
        if (c[i] != d[i])
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
