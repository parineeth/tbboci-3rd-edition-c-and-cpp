
#include <stdio.h>
#include <stdlib.h>


#define MAX_NUM_TESTS (100)
#define MAX_NUM_ELEMS (10)
#define MAX_VALUE     (10)



void handle_error()
{
    printf("Error occured \n");
    exit(1);
}



void print_array(int a[], int num_elems) 
{
    int i;

    for (i = 0; i < num_elems; ++i)
        printf("%d ", a[i]);

    printf("\n");
}

/*Helper function that merges two sorted regions
a: array where a[left] to a[mid] is sorted and a[mid+1] to a[right] is sorted
    We now need to merge these two regions
temp: temporary array used for sorting
Return value: Number of inversions  
*/
int merge(int a[], int temp[], int left, int mid, int right)
{
    int i, j, k;
    int num_inversions = 0;

    i = left;
    j = mid + 1;
    k = left;

    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) {
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
            num_inversions += mid + 1 - i;
        }
    }

    /*Handle any pending entries in first region*/
    while (i <= mid) 
        temp[k++] = a[i++];

    /*Handle any pending entries in second region*/
    while (j <= right)
        temp[k++] = a[j++];

    /*Restore the values from temp into a*/
    for (i = left; i <= right; ++i)
        a[i] = temp[i];

    return num_inversions;
}

/* Helper function that performs merge sort
a: array that should be sorted
temp: temporary array used for sorting
left: first index of the region in the array to be sorted
right: last index of the region in the array to be sorted
Return value: Number of inversions  
*/
int merge_sort(int a[], int temp[], int left, int right)
{
    int num_inversions, mid;

    if (left >= right)
        return 0;

    mid = (left + right) / 2;
 
    num_inversions = merge_sort(a, temp, left, mid);

    num_inversions += merge_sort(a, temp, mid + 1, right);

    num_inversions += merge(a, temp, left, mid, right);
    
    return num_inversions;
}


/*
a: array of numbers
num_elements: number of elements in the array. Should be >= 1
Return value: number of inversions
*/
int find_inversions(int a[], int num_elements)
{
    int num_inversions;

    int *temp = (int*) calloc(num_elements, sizeof(int));

    num_inversions =  merge_sort(a, temp, 0, num_elements - 1);

    free(temp);

    return num_inversions;
}



int brute_force_inversions(int a[], int num_elems)
{
    int num_inversions = 0;
    int i, j;

    for (i = 1; i < num_elems; ++i) {
        for (j = 0; j < i; ++j) {
            if (a[j] > a[i])
                num_inversions++;
        }
    }

    return num_inversions; 
} 


void test()
{
    int a[MAX_NUM_ELEMS];   
    int i, num_elems;
    int result, expected_result;

    /*Randomly decide the number of elements in the array*/
    num_elems = 1 + rand() % MAX_NUM_ELEMS;

    /*Randomly fill in the array*/
    for (i = 0; i < num_elems; ++i) {
        a[i] = rand() % MAX_VALUE;
    }

    print_array(a, num_elems);

    /*Find the result using the brute force technique*/
    expected_result = brute_force_inversions(a, num_elems);

    /*Find the result using an efficient technique*/
    result = find_inversions(a, num_elems);
    
    printf("Number of Inversions = %d \n", result);


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


