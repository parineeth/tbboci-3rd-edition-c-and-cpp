#include <stdlib.h>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>


using namespace std;




/* 
IMPORTANT: WE NEED TO COMPILE THIS CODE WITH THE OPTION -std=c++11
*/

void handle_error()
{
    cout << "Error occured\n";
    exit(1);
}


/*
tickets: 2D array which stores the information about the tickets bought. 
    ticket[i][0] stores the starting city of the ith ticket
    ticket[i][1] stores the destination city of the ith ticket
    There should be no loop in the trip 
num_tickets: number of tickets. Should be >= 1
Return value: vector containing the names of cities in the order of travel 
*/
vector<string>* reconstruct_trip(string tickets[][2], int num_tickets)
{
    unordered_map<string, string> next_hop;
    unordered_set<string> destinations;
    int i;

    /*Store the starting city (key) and destination city (value) in next_hop
    hash table. Store the destination cities in the destinations set*/
    for (i = 0; i < num_tickets; ++i) {
        next_hop.emplace(tickets[i][0], tickets[i][1]);
        destinations.emplace(tickets[i][1]);
    }
    
    /*Search the starting city of each ticket in the destinations set
    Only the first city of the entire trip will NOT be in destinations*/
    int start_index = -1;
    for (i = 0; i < num_tickets; ++i) {
        auto found = destinations.find(tickets[i][0]);
        if (found == destinations.end()) {
            /*We didn't find the city in the destinations set.
            So this must be the first city of the entire trip*/
            start_index = i;
            break;
        }
    }

    if (start_index == -1)
        return NULL;

    vector<string> *result = new vector<string>();

    /*push the first city of entire trip into the result*/
    result->push_back(tickets[start_index][0]); 

    /*Search for the first city of the entire trip in the hash table*/
    auto it = next_hop.find(tickets[start_index][0]);

    while (it != next_hop.end()) {
        /*Store the destination city in the result*/
        result->push_back(it->second); 

        /*make the destination city as the next starting city and 
        search for it in the hash table*/
        it = next_hop.find(it->second); 
    }

    return result;
} 


void verify(vector<string>& result, int num_tickets)
{
    int i;
    int num_cities = num_tickets + 1;
    string expected_result[] = {"LA", "SF", "TOKYO", "BEIJING", "DELHI", "ROME"};

    for (i = 0; i < num_cities; ++i) {
        if (result[i].compare(expected_result[i]) != 0)
            handle_error(); 
    }
}

void test()
{
    string tickets[][2] = {{"TOKYO", "BEIJING"}, {"LA", "SF"}, {"DELHI", "ROME"}, {"SF", "TOKYO"}, {"BEIJING", "DELHI"}};
    int i, num_tickets = 5;

    for (i = 0; i < num_tickets; ++i) {
        cout << tickets[i][0] << " -> " << tickets[i][1] << endl;
    }

    vector<string> *result = reconstruct_trip(tickets, num_tickets);

    cout << "The order of visiting: ";
    for (string city : *result) {
        cout << city << " ";
    }

    cout << endl;

    verify(*result, num_tickets);
}


int main()
{
    test();

    cout << "Test passed \n";
    return 0;
}
