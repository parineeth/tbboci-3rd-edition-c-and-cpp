
#include <stdlib.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_set>

using namespace std;



void handle_error()
{
    cout << "Error occured \n";
    exit(1);
}


void print_words(vector<string> words)
{
    auto it = words.begin();

    while (it != words.end()) {
        cout << *it << endl;
        it++;
    }
        
}

bool check_dictionary(const string& str1, unordered_set<string>& dictionary)
{
    auto found = dictionary.find(str1);

    if (found == dictionary.end())
        return false;

    return true;
} 




/*
str1: string that we need to check if it can be broken
dictionary: permitted words are stored in the dictionary 
Return value: true if we can break str1 into words in the dictionary
*/
bool word_break(const string& str1, unordered_set<string>& dictionary) 
{
    int i, j, substring_length;
    int length = str1.size();

    if (length == 0)
        return false;

    /*if we can break the string from 0 to pos, then is_break_possible[pos] 
    will be true*/
    bool *is_break_possible = new bool[length];

    /*if the substring from position i to position j of the original string
    is a word in dictionary, then word_start[j] will be i*/
    int *word_start = new int[length];

    for (i = 0; i < length; ++i) {
        is_break_possible[i] = false;
        word_start[i] = -1;
    } 

    for (i = 0; i < length; ++i) {
        /*Check if the substring from 0 to i is in the dictionary*/
        substring_length = i+1;
        if (!is_break_possible[i] 
        && check_dictionary(str1.substr(0, substring_length), 
                dictionary)) {
            is_break_possible[i] = true;
            word_start[i] = 0;
        }


        /*If we can break the substring upto i into dictionary words,
        then check if all substrings starting from i+1 can be broken 
        into dictionary words */
        if (is_break_possible[i]) {
            substring_length = 1;
            for (j = i + 1; j < length; ++j) {
                if (!is_break_possible[j]   
                && check_dictionary(str1.substr(i+1, 
                    substring_length), dictionary)) {
                    /*We can form a word from i+1 to j*/
                    is_break_possible[j] = true;
                    word_start[j] = i+1;
                }
                substring_length++;
            }
        }
    }

    /*
    If is_break_possible[length-1] is true, then entire string can be
    broken into dictionary words. If the word_start[length-1] is 0, then  
    it means the entire input word is present in the dictionary. But we
    want a compound word that has 2 or more dictionary words in it.
    So modify the result condition to check word_start[length-1] != 0
    */
    bool result = is_break_possible[length-1] && word_start[length-1] != 0;

    delete [] is_break_possible;
    delete [] word_start;

    return result;
}

bool compare(string a, string b) {
    return (a.length() > b.length()); /*Longer string should come first*/
}

/*words: the input list of words
Return value: pointer to the longest compound word if it exists, NULL otherwise
*/
string* find_longest_compound_word(vector<string>& words)
{
    unordered_set<string> dictionary;

    /*Store the input words in the dictionary*/
    auto it = words.begin();
    for (it = words.begin(); it != words.end(); ++it) {
        dictionary.emplace(*it);
    }
    /*Sort the words so that the longest word appears first*/
    sort(words.begin(), words.end(), compare);

    /*Starting from the longest word, check if the word can be broken 
    into two or more words present in the dictionary. If yes, then we 
    have found the longest compound word*/
    for (it = words.begin(); it != words.end(); ++it) {
        if (word_break(*it, dictionary))
            return &(*it);
    }
    /*There is no compound word in the input*/
    return NULL;
}


void test_01()
{
    vector<string> words;

    words.push_back("hello");
    words.push_back("jack");
    words.push_back("lumber");
    words.push_back("hellolumberjack");
    words.push_back("hellojack");

    print_words(words);

    string* longest = find_longest_compound_word(words);

    if (longest)
        cout << "Longest compound word = " << *longest << endl;

    if (longest->compare("hellolumberjack") != 0) {
        handle_error();
    }


    cout << "________________________________________\n";
}


void test_02()
{
    vector<string> words;

    words.push_back("hello");
    words.push_back("jack");
    words.push_back("lumber");

    print_words(words);

    string* longest = find_longest_compound_word(words);

    if (longest)
        cout << "Longest compound word = " << *longest << endl;
    else
        cout << "No compound word possible \n";

    if (longest != NULL) {
        handle_error();
    }


    cout << "________________________________________\n";
}


int main()
{
    test_01();
    test_02();

    cout << "Test passed \n";
    return 0;
}
