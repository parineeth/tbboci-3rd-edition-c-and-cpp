/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>




struct point {
    int x;
    int y;
} ;


void handle_error(void)
{
    printf("Test failed\n");
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
left1: upper left corner of rectangle 1
right1: lower right corner of rectangle 1
left2: upper left corner of rectangle 2
right2: lower right corner of rectangle 2
Return value: area of overlap of the two rectangles
*/
int find_overlap_area(struct point left1, struct point right1, 
            struct point left2, struct point right2)
{
    struct point result_left, result_right;
    int area;

    /*one rectangle lies completely to the right or left of the other*/
    if (right1.x < left2.x || right2.x < left1.x)
        return 0;

    /*one rectangle lies completely above or below the other*/
    if (left1.y < right2.y || left2.y < right1.y)
        return 0;

    /*the rectangles overlap*/
    result_left.x = max(left1.x, left2.x);
    result_left.y = min(left1.y, left2.y);
    result_right.x = min(right1.x, right2.x);
    result_right.y = max(right1.y, right2.y);   
      
    area = (result_right.x - result_left.x)  
            * (result_left.y - result_right.y);

    return area;
}


void test(struct point left1, struct point right1, struct point left2, struct point right2, int expected_result)
{
    int result;

    result = find_overlap_area(left1, right1, left2, right2);

    if (result != expected_result)
        handle_error();

}


int main()
{
    struct point left1, right1, left2, right2;

    left1.x = 0;
    left1.y = 20;
    right1.x = 20;
    right1.y = 0;

    left2.x = 10;
    left2.y = 30;
    right2.x = 30;
    right2.y = 10;

    test(left1, right1, left2, right2, 100);

    
    left1.x = 0;
    left1.y = 10;
    right1.x = 10;
    right1.y = 0;

    left2.x = 100;
    left2.y = 10;
    right2.x = 110;
    right2.y = 0;

    test(left1, right1, left2, right2, 0);
    

    printf("Test passed\n");
    return 0;
}
