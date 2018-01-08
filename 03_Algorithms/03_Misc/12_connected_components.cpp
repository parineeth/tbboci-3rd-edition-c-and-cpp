
#include <vector>
#include <iostream>
#include <stdlib.h>


using namespace std;





void handle_error() 
{
    cout << "Test failed\n";
    exit(1);
}

/* Helper function that performs depth first search on the graph
cur_node: the cur_node that we are searching
adjacency_table: an array of vectors. If there is an edge between node 0 and
      node 5, then adjacency_table[0] is a vector which will store 5 in it. 
is_visited: this array indicates if a node has already been visited or not
num_nodes: total number of nodes in the graph
*/
void dfs(int cur_node, vector<int> adjacency_table[], bool is_visited[], int num_nodes)
{
    unsigned int j;
    vector<int>& neighbors = adjacency_table[cur_node];

    is_visited[cur_node] = true;

    /*Go through all the neighbors of the current node*/
    for (j = 0; j < neighbors.size(); ++j) {
        int cur_neighbor = neighbors[j];

        /*If the current neighbor has not been visited, then recursively 
        call dfs on it*/
        if (!is_visited[cur_neighbor])
            dfs(cur_neighbor, adjacency_table, is_visited, num_nodes);
    }
}

/*Main function to compute number of connected components in an undirected graph
adjacency_table: an array of vectors. If there is an edge between node 0 and 
     node 5, then adjacency_table[0] is a vector which will store 5 in it. 
num_nodes: total number of nodes in the graph
Return value: number of connected components in the graph
*/
int connected_components(vector<int> adjacency_table[], int num_nodes)
{
    bool *is_visited = new bool[num_nodes];
    int i, count; 

    for (i = 0; i < num_nodes; ++i) 
        is_visited[i] = false;

    /*Traverse through all the nodes in the graph and perform Depth First 
    Search. Each time we perform DFS on a node that has not been visited  
    so far, increment the number of connected components*/
    count = 0;
    for (i = 0; i < num_nodes; ++i) {
        if (!is_visited[i]) {
            dfs(i, adjacency_table, is_visited, num_nodes);
            ++count;
        }
    }

    delete [] is_visited; 
    return count;
}


void test_01()
{
    int num_nodes = 4;

    vector<int> *adjacency_table = new vector<int> [num_nodes];

    /*Create an undirected graph where there is only one connected component*/
    /*The edges in the graph are 0-1, 0-2, 0-3, 1-2, 1-3 and 2-3*/
    adjacency_table[0].push_back(1);
    adjacency_table[0].push_back(2);
    adjacency_table[0].push_back(3);

    adjacency_table[1].push_back(2);
    adjacency_table[1].push_back(3);
    
    adjacency_table[2].push_back(3);
    
    int result = connected_components(adjacency_table, num_nodes);

    if (result != 1)
        handle_error();

    delete [] adjacency_table;
}



void test_02()
{
    int num_nodes = 8;

    vector<int> *adjacency_table = new vector<int> [num_nodes];

    /*
    Create an undirected graph where there are 3 connected component
    The edges in the graph are 0-1, 0-2, 0-3, 
    4-5, 5-6 
    7-7
    */

    adjacency_table[0].push_back(1);
    adjacency_table[0].push_back(2);
    adjacency_table[0].push_back(3);

    adjacency_table[4].push_back(5);
    adjacency_table[5].push_back(6);
    
    adjacency_table[7].push_back(7);

    int result = connected_components(adjacency_table, num_nodes);

    if (result != 3)
        handle_error();

    delete [] adjacency_table;
}


void test_03()
{
    int num_nodes = 8;

    /*Create a graph with 8 nodes and no edges. So there will be 8 components */

    vector<int> *adjacency_table = new vector<int> [num_nodes];

    int result = connected_components(adjacency_table, num_nodes);

    if (result != 8)
        handle_error();

    delete [] adjacency_table;
}



int main()
{
    test_01();

    test_02();

    test_03();

    cout << "Test passed\n";

    return 0;
}
