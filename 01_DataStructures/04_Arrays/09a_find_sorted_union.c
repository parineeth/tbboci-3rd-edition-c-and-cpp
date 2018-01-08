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
a, b: two input arrays whose union has to be found
length1, length2: number of elements in array a and b
result: array containing the result of union of a and b
Returns: number of elements in the result array 
*/
int find_union(int a[], int length1, int b[], int length2, int result[])
{
    int i, j, pos;
    
    if (length1 + length2 <= 0)
        return 0;

    /*Sort the two input arrays in non-decreasing order*/
    sort(a, length1);
    sort(b, length2);

    /*Process as long as there are elements in both a and b. 
    Pick the smaller element among a[i] and b[j] and if it
    doesn't match with previous element in result, then add it to result*/
    i = j = pos = 0;
    while (i < length1 && j < length2) {
        if (a[i] <= b[j]) {
            if (pos == 0 || a[i] != result[pos - 1]) 
                result[pos++] = a[i];

            if (a[i] == b[j]) 
                ++j; /*advance b*/
            ++i;
        } else {
            if (pos == 0 || b[j] != result[pos - 1])
                result[pos++] = b[j];
            ++j;
        }
    }

    /*Process the remainder elements in a*/
    while (i < length1) {
        if (pos == 0 || a[i] != result[pos - 1])
            result[pos++] = a[i];
        ++i;
    }

    /*Process the remainder elements in b*/
    while (j < length2) {
        if (pos == 0 || b[j] != result[pos - 1])
            result[pos++] = b[j];
        ++j;
    }

    return pos;
}





void generate_array(int a[], int length)
{
    int i;
    
    for (i = 0; i < length; ++i) {
        a[i] = rand() % MAX_VALUE;
    }

    
}

/*
Adds all the unique items of array a into the result array
a: input array
length: number of elements in a
result: the result will have the unique elements of array a appended to the result
    result will store only unique elements
result_pos: initial number of elements in the result
Return: final number of elements in the result
*/
int brute_force_unique(int a[], int length, int result[], int result_pos)
{
    int i, j;
    int found;
    
    i = 0;

    for (i = 0; i < length; ++i) {
        
        found = 0;
        for (j = 0; j < result_pos; ++j) {
            if (a[i] == result[j]) {
                found = 1;
                break;
            }
        }
        
        if (!found) {
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

    /*Find the union of a and b. The result will be in c*/
    length3 = find_union(a, length1, b, length2, c);

    printf ("Union : ");
    print_array(c, length3);


    /*Find the union using brute force. The result will be in d*/   
    length4 = 0;
    length4 = brute_force_unique(a, length1, d, length4);
    length4 = brute_force_unique(b, length2, d, length4);

    /*c and d should match. Since c is sorted, but d is not we need to sort d*/
    sort(d, length4); 

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
