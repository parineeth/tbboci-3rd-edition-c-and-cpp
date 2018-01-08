/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM_TESTS 100

#define MAX_NUM_EGGS 5
#define MAX_NUM_FLOORS 100

#define MAX_INT 9999999

void handle_error()
{
    printf("Error occured \n");
    exit(1);
}

int max(int a, int b)
{
    return (a > b ? a : b);
}


/*Suppose an egg doesn't break from any floor it is dropped, we are printing
what is the next floor from which to drop the egg so that the number of throws 
needed are minimal*/
void print_floors(int chosen_floor[][MAX_NUM_FLOORS + 1], int num_eggs, int num_floors)
{
    int floor_pos = chosen_floor[num_eggs][num_floors];
    int num_floors_processed = 0;

    while (floor_pos > 0 && floor_pos <= num_floors) {
        printf("Chosen floor = %d\n", floor_pos + num_floors_processed);
        num_floors_processed += floor_pos;
        floor_pos = chosen_floor[num_eggs][num_floors - num_floors_processed];
    }
    
}

/*
num_eggs: total number of identical eggs available. should be >= 1 
num_floors: total number of floors available. should be >= 1
Return value: minimum number of throws with which we can find egg strength
*/
int find_min_egg_drops(int num_eggs, int num_floors) 
{
    int min_throws[MAX_NUM_EGGS+1][MAX_NUM_FLOORS+1];
    int cur_egg, cur_floor, floor_iter;


    /*If there is only 1 floor, we need only 1 throw*/
    for (cur_egg = 1; cur_egg <= num_eggs; ++cur_egg) 
        min_throws[cur_egg][1] = 1;


    /*If there is only 1 egg and k floors, we need k throws*/
    for (cur_floor = 1; cur_floor <= num_floors; ++cur_floor) 
        min_throws[1][cur_floor] = cur_floor;


    for (cur_egg = 2; cur_egg <= num_eggs; ++cur_egg) {
        for (cur_floor = 2; cur_floor <= num_floors; ++cur_floor) {
            min_throws[cur_egg][cur_floor] = MAX_INT;

            for (floor_iter = 1; floor_iter <= cur_floor; ++floor_iter) {
                /*Find the number of throws needed from floor_iter*/
                int num_throws = max(
                    1 + min_throws[cur_egg - 1][floor_iter - 1], 
                    1 + min_throws[cur_egg][cur_floor - floor_iter]);

                if (min_throws[cur_egg][cur_floor] > num_throws) 
                    min_throws[cur_egg][cur_floor] = num_throws;

            }
        }
    }

    return min_throws[num_eggs][num_floors];
}


void test(int num_eggs, int num_floors, int expected_result)
{
    int result;

    result = find_min_egg_drops(num_eggs, num_floors);

    printf("Num eggs = %d, num floors = %d, minimum throws = %d\n", num_eggs, num_floors, result);

    if (result != expected_result)
        handle_error(); 

}

int main()
{
    test(2, 100, 14);
    test(2, 36, 8);

    printf("Test passed\n");
    return 0;
}
