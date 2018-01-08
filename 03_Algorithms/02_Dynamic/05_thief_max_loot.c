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
    printf("Error occured \n");
    exit(1);
}

int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}


/*
house_value: value that the thief can steal from each house
n: number of houses
Return value: maximum loot value that the thief can steal from all the houses
*/
int find_max_loot(int house_value[], int n)
{
    int i;
    int cur_val, val1, val2;

    if (n == 0)
        return 0;

    if (n == 1)
        return house_value[0];

    if (n == 2)
        return max(house_value[0], house_value[1]);

    /*
    val1 has the max loot till the previous house,
    val2 has the max loot till the second previous house
    */
    val1 = max(house_value[0], house_value[1]);
    val2 = house_value[0];

    for (i = 2; i < n; ++i) {
        /*cur_val stores the maximum loot till the current house (ith house)*/
        cur_val = max(val2 + house_value[i], val1);

        /*val2 now takes the value of val1 and val1 takes the current value*/
        val2 = val1;
        val1 = cur_val;
    }

    return cur_val;
}



void print_array(int a[], int length)
{
    int i;
    for (i = 0; i < length; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}







void test_01()
{
    int n = 4;
    int house_value[] = {6, 1, 2, 7};
    int max_loot;

    printf("House values : ");
    print_array(house_value, n);

    max_loot = find_max_loot(house_value, n);

    printf("Max loot = %d\n", max_loot);

    if (max_loot != 13)
        handle_error();

    printf("__________________________________\n");
}



void test_02()
{
    int n = 1;
    int house_value[] = {6};
    int max_loot;

    printf("House values : ");
    print_array(house_value, n);

    max_loot = find_max_loot(house_value, n);

    printf("Max loot = %d\n", max_loot);

    if (max_loot != 6)
        handle_error();
    
    printf("__________________________________\n");
}


void test_03()
{
    int n = 2;
    int house_value[] = {6, 4};
    int max_loot;

    printf("House values : ");
    print_array(house_value, n);

    max_loot = find_max_loot(house_value, n);

    printf("Max loot = %d\n", max_loot);

    if (max_loot != 6)
        handle_error();

    printf("__________________________________\n");
}


void test_04()
{
    int n = 2;
    int house_value[] = {6, 8};
    int max_loot;

    printf("House values : ");
    print_array(house_value, n);

    max_loot = find_max_loot(house_value, n);

    printf("Max loot = %d\n", max_loot);

    if (max_loot != 8)
        handle_error();

    printf("__________________________________\n");
}


void test_05()
{
    int n = 5;
    int house_value[] = {1, 6, 2, 8, 3};
    int max_loot;

    printf("House values : ");
    print_array(house_value, n);

    max_loot = find_max_loot(house_value, n);

    printf("Max loot = %d\n", max_loot);

    if (max_loot != 14)
        handle_error();

    printf("__________________________________\n");
}



int main()
{
    test_01();

    test_02();

    test_03();

    test_04();

    test_05();

    printf("Test passed \n");

    return 0;
}
