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



/*
left1: upper left corner of rectangle 1
right1: lower right corner of rectangle 1
left2: upper left corner of rectangle 2
right2: lower right corner of rectangle 2
Return value: 1 if the rectangles overlap, 0 otherwise
*/
int do_rectangles_overlap(struct point left1, struct point right1, 
            struct point left2, struct point right2)
{
    /*one rectangle lies completely to the right or left of the other*/
    if (right1.x < left2.x || right2.x < left1.x)
        return 0;

    /*one rectangle lies completely above or below the other*/
    if (left1.y < right2.y || left2.y < right1.y)
        return 0;

    /*the rectangles overlap*/
    return 1;
}


void test(struct point left1, struct point right1, struct point left2, struct point right2, int expected_result)
{
    int result;

    result = do_rectangles_overlap(left1, right1, left2, right2);

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

    test(left1, right1, left2, right2, 1);

    
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
