/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>



struct activity
{
    int id;
    int start_time;
    int end_time;   
};

void handle_error()
{
    printf("Error occured \n");
    exit(1);
}


/*Function for comparing two elements. This function used while sorting*/
int cmp_function(const void *p1, const void *p2)
{
    struct activity *x = (struct activity *)p1;
    struct activity *y = (struct activity *)p2;

    if (x->end_time < y->end_time)
        return -1;
    else if (x->end_time == y->end_time)
        return 0;
    else 
        return 1;
}


void sort(struct activity a[], int length)
{
    qsort(a, length, sizeof(struct activity), cmp_function);
}


/*
a: array of activities, where each activity has a start time and end time
num_activities: number of elements in the array. Should be >= 1
selected: the indexes of the selected activities 
Return value: Maximum number of activities that can be performed
*/
int activity_selection(struct activity a[],  int num_activities, int selected[])
{
    int i, count, cur_time; 

    /*Sort the activities in non-decreasing order of their end time*/
    sort(a, num_activities);

    /*Keep a track of the current time as we process the activities*/
    cur_time = 0;
    count = 0;
    for (i = 0; i < num_activities; ++i) {
        /*Pick the activity whose start time is on or after current time*/
        if (a[i].start_time >= cur_time) {
            selected[count] = i;
            count++;

            /*Update the current time to the end time of the activity*/
            cur_time = a[i].end_time;
        }
    }

    return count;
}




void test_01()
{
    struct activity a[] = {{1000, 0, 5}, {1001, 1, 2}, {1002, 3, 6}};
    int i, n = 3;
    int selected[3];
    int num_chosen_activities, expected_result ;

    num_chosen_activities = activity_selection(a, n, selected);

    for (i = 0; i < num_chosen_activities; ++i) {
        int index = selected[i];

        printf("Perform Activity %d: Start time = %d, End time = %d\n",
            a[index].id, a[index].start_time, a[index].end_time);
    }

    expected_result = 2;

    if (num_chosen_activities != expected_result)
        handle_error();

    printf("__________________________________\n");
    
}


void test_02()
{
    struct activity a[] = {{1000, 0, 1}, {1002, 1, 5}, {1001, 2, 3}, {1003, 4, 7}};
    int i, n = 4;
    int selected[4];
    int num_chosen_activities, expected_result;

    num_chosen_activities = activity_selection(a, n, selected);

    for (i = 0; i < num_chosen_activities; ++i) {
        int index = selected[i];

        printf("Perform Activity %d: Start time = %d, End time = %d\n",
            a[index].id, a[index].start_time, a[index].end_time);
    }


    expected_result = 3;

    if (num_chosen_activities != expected_result)
        handle_error();

    printf("__________________________________\n");
    
}


int main()
{
    test_01();
    test_02();

    printf("Test passed\n");
    return 0;
}
