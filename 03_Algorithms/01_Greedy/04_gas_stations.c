/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM_TESTS 100
#define MAX_NUM_STATIONS 10
#define MAX_DISTANCE 100

void handle_error()
{
    printf("Error occured \n");
    exit(1);
}

void print_array(int a[], int length)
{
    int i;
    for (i = 0; i < length; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

/*
gas: the amount of gas available at each gas station. The total gas in all 
    stations should be sufficient to complete the circular trip 
distance: distance[i] has the distance between gas station i and i+1
num_stations: number of gas stations. Should be >= 1
mileage: how much distance can the car travel for 1 unit of gas consumed
Return value: station from where to start so that we don't run out of fuel and
    complete the circular trip around all stations
*/
int find_starting_gas_station(int gas[], int distance[], int num_stations, int mileage)
{
    int i, starting_station;
    int least_gas, gas_required, gas_in_tank;
    
    /*Station from where to start the journey so that we don't run out of fuel*/
    starting_station = 0; 

    least_gas = 0; /*Tracks the least amount of gas in fuel tank*/
    gas_in_tank = 0; /*Tracks how much fuel is currently present in fuel tank*/
    for (i = 0; i < num_stations; ++i) {
        gas_required = distance[i] / mileage;
        
        /*At station i, we fill up gas[i] and then as we drive, we consume   
        gas_required to reach the destination station = (i+1) % num_stations */
        gas_in_tank += gas[i] - gas_required; 
        if (gas_in_tank < least_gas) {
            least_gas = gas_in_tank;
            /*The starting station is the station where we have
            the least amount of gas in the tank just before we fill up*/
            starting_station = (i+1) % num_stations;
        }
    }

    return starting_station;
}

/*Verifies if we start at starting_station, we can complete the journey without running out of fuel*/
void verify(int starting_station, int gas[], int distance[], int num_stations, int mileage)
{
    int i, cur_station;
    int gas_required, gas_in_tank;

    /*Check if starting_station is out of range*/
    if (starting_station < 0 || starting_station >= num_stations)
        handle_error();

    cur_station = starting_station;
    gas_in_tank = 0;
    for (i = 1; i < num_stations; ++i) {
        gas_required = distance[cur_station] / mileage;
        gas_in_tank += gas[cur_station] - gas_required;

        /*gas in the fuel tank should always be >= 0*/
        if (gas_in_tank < 0) {
            handle_error();
        }

        cur_station = (cur_station + 1) % num_stations;
    }

}


void test() 
{
    int i, num_stations, mileage;
    int gas[MAX_NUM_STATIONS];
    int distance[MAX_NUM_STATIONS];
    int total_distance, total_gas, remaining_gas;
    int starting_station;
    int per_station_quota;

    /*Randomly pick the number of gas stations*/
    num_stations = 1 + rand() % MAX_NUM_STATIONS;

    total_distance = 0;
    for (i = 0; i < num_stations; ++i) {
        /*Randomly pick the distance between the gas stations between
        1 and 10*/
        distance[i] = 1 + rand() % 10;
        total_distance += distance[i];
    }

    /*We are fixing the mileage to 1 mile/gallon since we will
    not have to deal with fractional values*/
    mileage = 1;

    /*Compute the gas needed to complete the journey around all stations*/
    total_gas = total_distance / mileage;

    /*Randomly distribute the total_gas among the gas stations*/
    remaining_gas = total_gas;
    per_station_quota = remaining_gas / num_stations;
    for (i = 0; i < num_stations; ++i) {
        if (remaining_gas > 0)
            gas[i] = rand() % per_station_quota;
        else 
            gas[i] = 0; 
        remaining_gas -= gas[i];
    } 

    /*If there is any gas left over, then distribute the 
    remaining gas equally among the gas stations*/
    i = 0;
    per_station_quota = remaining_gas / num_stations;
    while (remaining_gas > 0 && i < num_stations - 1) {
        gas[i] += per_station_quota;
        remaining_gas -= per_station_quota;
        ++i;
    }
    /*If there is still any gas left over, give it to the last gas station*/
    gas[num_stations - 1] += remaining_gas; 

    printf("Gas      : ");
    print_array(gas, num_stations);


    printf("Distance : ");
    print_array(distance, num_stations);

    /*Find the gas station from where to start the journey
    IMPORTANT: ensure that while calling this function that the sum of gas in all
    the stations should be sufficient to complete the journey*/
    starting_station = find_starting_gas_station(gas, distance, num_stations, mileage);

    printf("Starting station = %d\n", starting_station);

    verify(starting_station, gas, distance, num_stations, mileage);

    printf("____________________________________________________\n");
}




int main() 
{
    int i;
    for (i = 0; i < MAX_NUM_TESTS; ++i) {
        test();
    }

    printf("Test passed\n");
    return 0;
}
