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
    printf("Test failed \n");
    exit(1);
}


int max(int a, int b)
{
    return a > b ? a : b;
}

int min(int a, int b)
{
    return a < b ? a : b;
}



struct Box
{
    int height;
    int length;
    int breadth;
};


int cmp_function(const void *p1, const void *p2)
{
    struct Box *box1 = (struct Box *)p1;
    struct Box *box2 = (struct Box *)p2;

    /*Higher area boxes should be stored first after sorting*/
    return (box2->length * box2->breadth) - (box1->length * box1->breadth);
}


void sort(struct Box a[], int num_elements)
{
    qsort(a, num_elements, sizeof(struct Box), cmp_function);
}


/*
a: array of boxes of different dimensions. Should contain atleast one box
num_input_boxes: number of boxes in the array. Should be >= 1
Result: maximum height of the stack of boxes that can be constructed.
Assumption is that multiple instances of each box are available
*/
int max_stack_height(struct Box a[], int num_input_boxes) {
    struct Box *boxes = (struct Box*) calloc(3 * num_input_boxes, 
                        sizeof(struct Box));
    int *best_height = (int *) calloc(3 * num_input_boxes, sizeof(int));
    int i, j, num_boxes, result;

    /*For each box, all 3 orientations are possible. Length will always be
    greater than breadth */
    for (i = 0; i < num_input_boxes; ++i) {
        boxes[3*i].height = a[i].height;
        boxes[3*i].length = max(a[i].length, a[i].breadth);
        boxes[3*i].breadth = min(a[i].length, a[i].breadth);
        
        boxes[3*i + 1].height  = a[i].length;
        boxes[3*i + 1].length  = max(a[i].breadth, a[i].height);
        boxes[3*i + 1].breadth = min(a[i].breadth, a[i].height);

        boxes[3*i + 2].height  = a[i].breadth;
        boxes[3*i + 2].length  = max(a[i].length, a[i].height);
        boxes[3*i + 2].breadth = min(a[i].length, a[i].height);
    }

    num_boxes = 3 * num_input_boxes;

    /*Sort the boxes so that the boxes with larger base area appear first*/
    sort(boxes, num_boxes);

    for (i = 0; i < num_boxes; ++i) {
        best_height[i] = boxes[i].height;
    }

    for (i = 1; i < num_boxes; ++i) {
        for (j = 0; j < i; ++j) {
            /*We can place box i on box j, only if base of box i 
            is smaller than the base of box j*/
            if (boxes[i].length < boxes[j].length 
            && boxes[i].breadth < boxes[j].breadth) {
                if (best_height[i] < 
                best_height[j] + boxes[i].height) {
                    best_height[i] = best_height[j] + 
                                boxes[i].height;
                }
            }
        }
    }

    /*Find the stack with the maximum height*/
    result = best_height[0];
    for (i = 1; i < num_boxes; ++i) {
        if (best_height[i] > result)
            result = best_height[i];
    }

    free(best_height);
    free(boxes);

    return result;
}


void test_01()
{
    struct Box a[] = { {100, 120, 320}, {10, 20, 30}, {40, 60, 70}, {40, 50, 60} };
    int n = 4;
    int result;
    
    result = max_stack_height(a, n);

    printf("Max stack height = %d \n", result);

    if (result != 600)
        handle_error();
}


void test_02()
{
    struct Box a[] = { {10, 20, 30} };
    int n = 1;
    int result;
    
    result = max_stack_height(a, n);

    printf("Max stack height = %d \n", result);

}



int main()
{
    test_01();
    test_02();

    printf("Test passed \n");
    return 0;
}
