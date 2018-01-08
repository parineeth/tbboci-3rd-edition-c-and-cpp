/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>

void handle_error(void)
{
    printf("Test failed\n");
    exit(1);
}



/*
slope1: slope of the first line
c1: y-intercept of the first line
slope2: slope of the second line
c2: y-intercept of the second line
Return value: 1 if the lines intersect, 0 otherwise
*/
int do_lines_intersect(double slope1, double c1, double slope2, double c2)
{
    double epsilon = 0.0001;
    int intersect = 0;
    
    if (abs(slope1 - slope2) < epsilon) { 
        /*Both lines have the same slope. Check the y-intercept*/
        if (abs(c1 - c2) < epsilon) {
            /*The y-intercepts are the same. 
            So both lines are the same lines.
            We consider such lines to intersect with each other*/
            intersect = 1;      
        } else {
            /*The lines are parallel and not coincident on each other
            So these lines will not intersect*/
            intersect = 0;
        }
    } else {
        /*The two lines have different slopes. They will intersect*/
        intersect = 1;
    }

    return intersect;
}


void test(double slope1, double c1, double slope2, double c2, int expected_result)
{
    int result;

    result = do_lines_intersect(slope1, c1, slope2, c2);

    printf("Lines (slope = %lf, y-intercept = %lf) and (slope = %lf, y-intercept = %lf) ", 
            slope1, c1, slope2, c2);
    if (result)
        printf("intersect\n");
    else
        printf("do NOT intersect\n");

    if (result != expected_result)
        handle_error();  
}


int main()
{
    double slope1, slope2, c1, c2;
    int expected_result;

    /*Same slope, different y-intercept. Should NOT intersect*/ 
    slope1 = 1.0;
    slope2 = 1.0;
    c1 = 1.0;
    c2 = 2.0;
    expected_result = 0;
    test(slope1, c1, slope2, c2, expected_result);


    /*Same y-intercept, different slope. Should intersect*/ 
    slope1 = 2.0;
    slope2 = 1.0;
    c1 = 1.0;
    c2 = 1.0;
    expected_result = 1;
    test(slope1, c1, slope2, c2, expected_result);


    /*Different y-intercept, different slope. Should intersect*/    
    slope1 = 1.0;
    slope2 = 2.0;
    c1 = 3.0;
    c2 = 4.0;
    expected_result = 1;
    test(slope1, c1, slope2, c2, expected_result);


    /*Same y-intercept, same slope. Identical lines, should intersect*/ 
    slope1 = 1.0;
    slope2 = 1.0;
    c1 = 1.0;
    c2 = 1.0;
    expected_result = 1;
    test(slope1, c1, slope2, c2, expected_result);

    printf("Test passed\n");
    return 0;
}



