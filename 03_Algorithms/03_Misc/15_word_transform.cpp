#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <list>
#include <string.h>

using namespace std;

#define MAX_WORD_LENGTH (20)

void handle_error()
{
    cout << "Test failed \n";
    exit(1);
}

/* 
begin_word: starting word in the word transformation
end_word: ending word in the word transformation
dictionary: contains the permitted words that can be used in the transformation
Result: list that contains the sequence of words if word transformation is 
    possible, NULL if word transformation is not possible
*/
list<string>* transform_word(string& begin_word, string& end_word, 
            unordered_set<string>& dictionary)
{
    queue<string> q;
    unordered_set<string> visited;  /*words that have already been visited*/

    /*If we can transform word a to word b, then we store b -> a mapping 
    in the reverse_path. b is the key and a is the value*/
    unordered_map<string, string> reverse_path;
    char char_array[MAX_WORD_LENGTH];
    unsigned int i;


    q.push(begin_word);
    visited.insert(begin_word);

    while (!q.empty()) {
        /*Get the word at the beginning of the queue*/
        string cur_word = q.front();
        q.pop();

        /*If the current word matches the ending word, we have found
        the word transformation. Store the sequence of transformation 
        in the result list*/
        if (cur_word.compare(end_word) == 0) {
            list<string> *result = new list<string>();
            result->push_front(cur_word);

            /*Find previous word from where we reached the current
            word and add the previous word to the result list*/
            auto it = reverse_path.find(cur_word);
            while (it != reverse_path.end()) {
                result->push_front(it->second);
                it = reverse_path.find(it->second);
            }

            return result;
        }


        /*Look at all possible words that can be generated from the 
        current word by changing a single character*/
        for (i = 0; i < cur_word.length(); ++i) {
            strcpy(char_array, cur_word.c_str()); 
            
            /*Generate new word by changing the character at 
            position i*/
            for (char c = 'a'; c <= 'z'; ++c) {
                char_array[i] = c;
                string new_word = string(char_array);

                auto it_in_dictionary = dictionary.find(new_word);
                auto it_in_visited = visited.find(new_word);

                /*If new word is present in dictionary and has not
                been visited so far, then add it to the queue*/
                if (it_in_dictionary != dictionary.end() && 
                    it_in_visited == visited.end() ) {
                    q.push(new_word);
                    visited.insert(new_word);

                    /*Store information that we reached 
                    new_word from cur_word*/
                    reverse_path.emplace(new_word, cur_word);
                }

            }
        }

    }

    return NULL; /*transformation is not possible*/
}

void test()
{
    unordered_set<string> dictionary;
    string begin_word("bell");
    string end_word("walk");

    dictionary.insert("tall");
    dictionary.insert("bell");
    dictionary.insert("walk");
    dictionary.insert("ball");
    dictionary.insert("talk");

    list<string> *result = transform_word(begin_word, end_word, dictionary);

    if (!result)
        handle_error();

    /*Print out the word transformation*/
    for (auto it = result->begin(); it != result->end(); ++it)
        cout << *it << " ";

    cout << endl;
    
}


int main()
{
    test();

    cout << "Test passed \n";
    return 0;
}
