/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void handle_error()
{
    printf("Error occured \n");
    exit(1);
}



/*n: number >= 0 whose square root has to be computed
accuracy: how accurate should the result be
Return value: square root of n */
double compute_sqrt(int n, double accuracy)  {
    double low = 1.0, mid = 1.0, high = n * 1.0;
    double square, difference;

    if (n == 0) 
        return 0.0;

    if (n == 1)
        return 1.0;
    
    while (low < high) {
        mid = (low + high) / 2;
        square = mid * mid;

        /*Find absolute difference between (mid * mid) and n*/
        difference =  square - n;
        if (difference < 0)
            difference = difference * -1;
        
        /*If the absolute difference is within the required accuracy
        then mid contains the square root. So break out of the loop*/
        if (difference < accuracy)
            break;
            
        if (square > n) 
            high = mid;
        else
            low = mid;
        
    }
    return mid; /*Return the square root*/
}


int main()
{
    int i;
    double computed_sqrt, expected_sqrt, difference;

    for (i = 0; i < 1000; ++i) {

        computed_sqrt = compute_sqrt(i, 0.001);

        printf("Square root of %d = %lf\n", i, computed_sqrt);

        expected_sqrt = sqrt(i);

        difference = abs(computed_sqrt - expected_sqrt);

        if (difference > 0.1) 
            handle_error();

    }

    printf("Test passed \n");

    return 0;
}



