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
#define MAX_NUM_ELEMS (20)
#define MAX_K_VALUE (10)
#define MAX_VALUE   (100)

void handle_error(void)
{
    printf("Test failed\n");
    exit(1);
}



/* Helper function to perform heapify
heap: min heap.  Maximum number of elements in heap is k
pos: position of the heap that may need to be fixed
heap_size: current number of nodes in the heap
*/
void heapify(int heap[], int pos, int heap_size)
{
    int left = 2 * pos;
    int right = (2 * pos) + 1;
    int ix_of_smallest = pos;

    /*Find which of the three are the smallest: heap[pos] OR left child
    OR right child*/
    if (left < heap_size && heap[pos] > heap[left])
        ix_of_smallest = left;
    if (right < heap_size && heap[ix_of_smallest] > heap[right])
        ix_of_smallest = right;

    if (ix_of_smallest != pos) {
        /*
        If pos doesn't contain the smallest value,
        then swap the smallest value into pos 
        */
        int temp = heap[pos];
        heap[pos] = heap[ix_of_smallest];
        heap[ix_of_smallest] = temp;

        /*Recursively re-adjust the heap*/
        heapify(heap, ix_of_smallest, heap_size);
    }
}

/*Main function to find the k largest elements
a: array in which we have to find the k largest elements
n: number of elements in the array. n > 0
k: the number of largest elements that we need to find. k <= n
heap: the k largest elements will be stored in the heap and returned
*/
void find_k_largest(int a[], int n, int k, int heap[])
{
    int i;

    /*Store the first k elements of the array in the heap*/
    for (i = 0; i < k; ++i)
        heap[i] = a[i];

    /*Construct the initial min-heap*/
    for (i = k - 1; i >= 0; --i)
        heapify(heap, i, k);

    for (i = k; i < n; ++i) {
        /*The root of the heap will have the smallest item in the heap
        If current item in array is greater than root of the heap, then
        place current item into root of the heap and readjust the heap
        */
        if (a[i] > heap[0]) {
            heap[0] = a[i];
            heapify(heap, 0, k);
        }
    }
}


/*Sort in descending order using bubble sort*/
void sort_array(int a[], int n)
{
    int i, j, temp;

    for (i = 0; i < n - 1; ++i) {
        for (j = i + 1; j < n; ++j) {
            if (a[i] < a[j]) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}


void print_array(int a[], int n)
{
    int i;

    for (i = 0; i < n; ++i) {
        printf("%d ", a[i]);
    }

    printf("\n");
}


void test_01()
{
    int i, j, k;
    int a[MAX_NUM_ELEMS];
    int heap[MAX_K_VALUE];
    int found;

    /*Randomly generate the k value*/
    k = 1 + rand() % MAX_K_VALUE;

    printf("K = %d\n", k);

    /*randomly generate the numbers in the array*/
    for (i = 0; i < MAX_NUM_ELEMS; ++i) {
        a[i] = rand() % MAX_VALUE;
    }

    printf("Input  : ");
    print_array(a, MAX_NUM_ELEMS);

    /*Find the k largest elements using the heap*/
    find_k_largest(a, MAX_NUM_ELEMS, k, heap);

    /*Sort the array*/
    sort_array(a, MAX_NUM_ELEMS);

    /*Print the top k elements in the heap. Note that elements in the heap will themselves 
    NOT be in sorted order*/
    printf("Output : ");
    print_array(heap, k);

    /*Verify that each element in the heap is present in the top k elements in the sorted array */
    for (i = 0; i < k; ++i) {
        found = 0;
        for (j = 0; j < k; ++j) {
            if (heap[i] == a[j] ) {
                found = 1;
                break;
            }
        }
        
        if (!found)
            handle_error();
    }

}



int main()
{
    int i;

    for (i = 0; i < MAX_NUM_TESTS; ++i) {

        test_01();

        printf("\n_________________________________________________\n\n");
    }
    printf("Test passed\n");
    return 0;
}
