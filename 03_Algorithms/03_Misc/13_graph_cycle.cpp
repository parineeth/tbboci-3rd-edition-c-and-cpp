
#include <vector>
#include <iostream>
#include <stdlib.h>


using namespace std;


#define WHITE 0
#define GRAY 1
#define BLACK 2


void handle_error() 
{
    cout << "Test failed\n";
    exit(1);
}

/* Helper function that performs depth first search on the graph
cur_node: the current node that we are searching
adjacency_table: an array of vectors. If there is an edge from node 0 to 
    node 5, then adjacency_table[0] is a vector which stores 5 in it
color: this array indicates the color assigned to the nodes
num_nodes: total number of nodes in the graph
Return value: true if cycle exists in directed graph, false otherwise
*/
bool dfs(int cur_node, vector<int> adjacency_table[], int color[], int num_nodes)
{
    bool does_cycle_exist = false;
    unsigned int j;
    vector<int>& neighbors = adjacency_table[cur_node];

    /*Assign the gray color to the node indicating that we have 
    started processing this node*/
    color[cur_node] = GRAY;

    for (j = 0; j < neighbors.size(); ++j) {
        int cur_neighbor = neighbors[j];

        /*If we find a neighboring node with the gray color, then we 
        have found a loop*/
        if (color[cur_neighbor] == GRAY) {
            return true;
        }

        /*If the neighboring node has a white color, then perform 
        DFS on it*/
        if (color[cur_neighbor] == WHITE) {
            does_cycle_exist = dfs(cur_neighbor, adjacency_table, 
                        color, num_nodes);
            if (does_cycle_exist)
                return true;
        }
    }

    /*Assign the node the black color to indicate that we have finished 
    processing it*/
    color[cur_node] = BLACK;
    return false;   
}

/* Main function that checks if cycle is present or not
adjacency_table: an array of vectors. If there is an edge from node 0 
    to node 5, then adjacency_table[0] is a vector which stores 5 in it
num_nodes: total number of nodes in the graph
Return value: true if cycle is present in directed graph, false otherwise
*/
bool is_cycle_present(vector<int> adjacency_table[], int num_nodes)
{
    int *color = new int[num_nodes];
    int i; 
    bool does_cycle_exist = false;

    /*Assign the white color to all the nodes to indicate that we have 
    not started processing the nodes*/
    for (i = 0; i < num_nodes; ++i) 
        color[i] = WHITE;

    /*Go through all the nodes in the graph and perform DFS on the nodes 
    whose color is white*/
    for (i = 0; i < num_nodes; ++i) {
        if (color[i] == WHITE) {
            does_cycle_exist = dfs(i, adjacency_table, color, 
                        num_nodes);
            if (does_cycle_exist) 
                break;
        }
    }

    delete [] color; 
    return does_cycle_exist;
}


void test_01()
{
    /*Construct a graph without a cycle
    The edges in the graph are 0->1, 0->2, 0->3, 1->2, 1->3, 2->3, 4->1*/

    int num_nodes = 5;

    vector<int> *adjacency_table = new vector<int> [num_nodes];

    adjacency_table[0].push_back(1);
    adjacency_table[0].push_back(2);
    adjacency_table[0].push_back(3);

    adjacency_table[1].push_back(2);
    adjacency_table[1].push_back(3);
    
    adjacency_table[2].push_back(3);

    adjacency_table[4].push_back(1);
    
    bool result = is_cycle_present(adjacency_table, num_nodes);

    if (result != false)
        handle_error();

    delete [] adjacency_table;
}



void test_02()
{
    /*Construct a graph with a cycle
    The edges in the graph are 0->1, 0->2, 0->3, 1->2, 1->3, 2->3, 3->4 and 4->2
    The cycle is 2->3, 3->4, 4->2
    */
    int num_nodes = 5;

    vector<int> *adjacency_table = new vector<int> [num_nodes];

    adjacency_table[0].push_back(1);
    adjacency_table[0].push_back(2);
    adjacency_table[0].push_back(3);

    adjacency_table[1].push_back(2);
    adjacency_table[1].push_back(3);
    
    adjacency_table[2].push_back(3);

    adjacency_table[3].push_back(4);

    adjacency_table[4].push_back(2);
    
    bool result = is_cycle_present(adjacency_table, num_nodes);

    if (result != true)
        handle_error();

    delete [] adjacency_table;
}



int main()
{
    test_01();

    test_02();

    cout << "Test passed\n";

    return 0;
}
