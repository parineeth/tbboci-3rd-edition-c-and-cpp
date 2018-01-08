

#include <iostream>
#include <stack>
#include <vector>


using namespace std;


#define MAX_NUM_CHARACTERS 256


/* Helper function for performing topological sorting
cur_char: current character that we are processing
adjacency_table: an array of vectors. if there is an edge from 'a' to 'b' then 
adjacency_table['a'] contains a vector which will store b
is_visited: indicates if a character has already been visited or not
s: stack for storing the result of the topological sort
*/
void topological_sort_helper(char cur_char, vector<char> adjacency_table[], 
            bool is_visited[], stack<char>& s) {
    unsigned int i;
    
    if (is_visited[(int)cur_char])
        return;

    /*make is_visited to true here so that we don't run into loops*/
    is_visited[(int)cur_char] = true;

    
    /*Process all the characters that are neighbors of the current  
    character (ie  adjacent to current character) in the graph*/
    vector<char>& neighbor_list = adjacency_table[(int)cur_char];
    for (i = 0; i < neighbor_list.size(); ++i) {
        char neighbor_char = neighbor_list[i];

        if (!is_visited[(int)neighbor_char])
            topological_sort_helper(neighbor_char, adjacency_table, 
                        is_visited, s);

    }

    /*Push the current character onto the stack only after all the 
    characters reachable from it have been recursively added to the stack*/
    s.push(cur_char);
}

/*Function that performs topological sorting
adjacency_table: an array of vectors. if there is an edge from 'a' to 'b' then 
adjacency_table['a'] contains a vector which will store b
*/
void topological_sort(vector<char> adjacency_table[])
{
    bool is_visited[MAX_NUM_CHARACTERS];
    stack<char> s;
    int i;

    for (i = 0; i < MAX_NUM_CHARACTERS; ++i) 
        is_visited[i] = false;

    /*Process all the characters*/
    for (i = 0; i < MAX_NUM_CHARACTERS; ++i) {
        if (adjacency_table[i].size())
            topological_sort_helper(i, adjacency_table, is_visited, s);
    }

    /*Pop out the contents of the stack to get the result of topological sort
    This is the order of characters in the alien language*/
    while (!s.empty()) {
        char cur_char = s.top();
        cout << cur_char << endl;
        s.pop();
    }
    
}


/*Main function to find the order of characters in an alien language
words: the words present in the dictionary
num_words: number of words in the dictionary
*/
void get_alphabet_order(const char *words[], int num_words)
{
    /*For each character in the language we maintain a vector*/
    vector<char> adjacency_table[MAX_NUM_CHARACTERS];
    int i;

    /*Go through the consecutive pairs of words in dictionary*/
    for (i = 0; i < num_words - 1; ++i) {
        const char *word1 = words[i];
        const char *word2 = words[i+1];
        int pos = 0;
        
        while (word1[pos] && word2[pos]) {
            /*Find first mismatching position between the two words*/
            if (word1[pos] != word2[pos]) {
                char first = word1[pos];
                char second = word2[pos];

                /*In the graph, we have an edge from first char
                to second char. Fetch the vector for first char
                and store the second char in the vector, since 
                second character is adjacent to first char
                */
                adjacency_table[(int)first].push_back(second);
                break;
            }
            pos++;
        }
    }

    /*Perform the topological sort*/
    topological_sort(adjacency_table);
}


void test_01() 
{
    const char *words[] = {"aaa", "abc", "acb", "dad"}; /*Words in the alien dictionary*/
    int num_words = 4;
    int i;
    
    cout << "Dictionary: ";
    for (i = 0; i < num_words; ++i) 
        cout << words[i] << " ";

    cout << endl << "Order of characters:" << endl;

    get_alphabet_order(words, num_words);

    cout << "_____________________________\n";
    
}


void test_02() 
{
    const char *words[] = {"aba", "abb", "abd", "ac", "ad", "pq"}; /*Words in the alien dictionary*/
    int num_words = 6;
    int i;

    cout << "Dictionary: ";
    for (i = 0; i < num_words; ++i) 
        cout << words[i] << " ";

    cout << endl << "Order of characters:" << endl;

    get_alphabet_order(words, num_words);

    cout << "_____________________________\n";
    
}


int main() 
{
    test_01();
    test_02();

    cout << "Test passed\n";
    return 0;
}
