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
#define MAX_NUM_ELEMENTS (10)
#define MAX_VALUE   (100)
#define MAX_NUM_ARRAYS (5)
#define MAX_INT     (99999)

void handle_error(void)
{
    printf("Test failed\n");
    exit(1);
}


struct node
{
    int value;
    int array_no;
};

/*
heap - min heap of nodes. 
pos - position of the heap that may need to be fixed
heap_size - current number of nodes in the heap
*/
void heapify(struct node heap[], int pos, int heap_size)
{
    int left = 2 * pos;
    int right = (2 * pos) + 1;
    int ix_of_smallest = pos;

    /*Find which of the three are the smallest - heap[pos] OR left child
    OR right child*/
    if (left < heap_size && heap[pos].value > heap[left].value)
        ix_of_smallest = left;

    if (right < heap_size && heap[ix_of_smallest].value > heap[right].value)
        ix_of_smallest = right;

    if (ix_of_smallest != pos) {
        /*If pos doesn't contain the smallest node,
        then swap the smallest node into pos */
        struct node temp = heap[pos];
        heap[pos] = heap[ix_of_smallest];
        heap[ix_of_smallest] = temp;

        heapify(heap, ix_of_smallest, heap_size);
    }
}


/*
arrays: the arrays to be merged. arrays[0] has the first array, arrays[1] has 
        the second array and so on
n: number of elements in each array
k: number of arrays
result: the merged results are passed back in this array
*/
void merge_k_sorted_arrays(int arrays[][MAX_NUM_ELEMENTS], int n, int k, 
            int *result)
{
    struct node *heap = (struct node*) calloc(k, sizeof(struct node));
    int *arr_pos = (int*) calloc(k, sizeof(int));
    int i, pos, res_index, array_no;

    /*Store the first element in each array into the heap*/
    for (i = 0; i < k; ++i) {
        heap[i].value = arrays[i][0];
        heap[i].array_no = i;
        arr_pos[i] = 1;
    }

    /*Construct the initial heap using the heapify procedure*/
    for (i = k - 1; i >= 0; --i)
        heapify(heap, i, k);
    
    /*
    Process the remaining elements in the arrays. When all elements in the 
    arrays have been processed, MAX_INT will be present at root of heap
    */
    res_index = 0;
    while (heap[0].value != MAX_INT) {
        /*
        root of the heap will have the lowest value. So store
        it into the result
        */
        result[res_index++] = heap[0].value;

        array_no = heap[0].array_no;
        pos = arr_pos[array_no];

        /*
        If the root belongs to array x, then replace the root with
        the next element in array x
        */
        if (pos >= n) {
            /*If we have exhausted all elements in the array, 
            then insert MAX_INT into the heap*/
            heap[0].value = MAX_INT;
            heap[0].array_no = array_no;
        } else {
            heap[0].value = arrays[array_no][pos];
            heap[0].array_no = array_no;
        }

        /*Re-adjust the heap after replacing the root*/
        heapify(heap, 0, k);

        arr_pos[array_no]++;
    }

    free(arr_pos);
    free(heap);
}



void sort_array(int a[], int n)
{
    int i, j, temp;

    for (i = 0; i < n - 1; ++i) {
        for (j = i + 1; j < n; ++j) {
            if (a[i] > a[j]) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}


void print_array(int array[], int n)
{
    int i;

    for (i = 0; i < n; ++i) {
        printf("%d ", array[i]);
    }

    printf("\n");
}


void test_01(int num_arrays, int num_elements)
{
    int i, j, pos;
    int result[MAX_NUM_ARRAYS * MAX_NUM_ELEMENTS];
    int expected_result[MAX_NUM_ARRAYS * MAX_NUM_ELEMENTS];
    int arrays[MAX_NUM_ARRAYS][MAX_NUM_ELEMENTS];

    for (i = 0; i < num_arrays ; ++i) {
        for (j = 0; j < num_elements; ++j) {
            arrays[i][j] = rand() % MAX_VALUE;
        }
    }

    for (i = 0; i < num_arrays; ++i) {
        sort_array(arrays[i], num_elements);
        printf("Array %d: ", i);
        print_array(arrays[i], num_elements);
    }

    merge_k_sorted_arrays(arrays, num_elements, num_arrays, result);


    printf("Output : ");
    print_array(result, num_arrays * num_elements);

    pos = 0;
    for (i = 0; i < num_arrays ; ++i) {
        for (j = 0; j < num_elements; ++j) {
            expected_result[pos] = arrays[i][j];
            pos++;
        }
    }
    sort_array(expected_result, num_arrays * num_elements);

    for (i = 0; i < num_arrays * num_elements; ++i)
        if (result[i] != expected_result[i])
            handle_error();
}



int main()
{
    int i, num_arrays, num_elements;

    for (i = 0; i < MAX_NUM_TESTS; ++i) {
        num_arrays = 1 + rand() % MAX_NUM_ARRAYS;
        if (num_arrays < 2)
            num_arrays = 2;

        num_elements = 1 + rand() % MAX_NUM_ELEMENTS;

        test_01(num_arrays, num_elements);

        printf("\n_________________________________________________\n\n");
    }
    printf("Test passed\n");
    return 0;
}
