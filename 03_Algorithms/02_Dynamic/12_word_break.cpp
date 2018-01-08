/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdlib.h>
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;


#define MAX_NUM_TESTS 100



void handle_error()
{
    cout << "Error occured \n";
    exit(1);
}

bool check_dictionary(const string& str1, unordered_set<string>& dictionary)
{
    auto found = dictionary.find(str1);

    if (found == dictionary.end())
        return false;

    return true;
} 

/* Helper function to print the words present in the string
str1: input string
word_start: if the substring from position i to position j of the original 
    string is a word in dictionary, then word_start[j] will be i
*/
void print_result(const string& str1, int word_start[])
{
    int pos = str1.size() - 1;
    while (pos >= 0) {
        /*The current word ends at pos in the input string and
        starts at word_start[pos] */
        int substring_length = pos - word_start[pos] + 1;
        cout << str1.substr(word_start[pos], substring_length) << " ";
        pos = word_start[pos] - 1;
    }
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

    if (result)
        print_result(str1, word_start);

    delete [] is_break_possible;
    delete [] word_start;

    return result;
}



void test(const string& str1, bool expected_result)
{
    string words[] = {"i", "will", "play", "now"};
    unordered_set<string> dictionary;

    /*Store the input words in the dictionary*/
    for (string curWord : words) {
        dictionary.emplace(curWord);
    }

    cout << str1 << " => ";

    bool result = word_break(str1, dictionary);

    cout << endl;

    if (result) {
        cout << str1 << " can be broken \n";
    } else {
        cout << str1 << " cannot be broken \n";
    }

    if (result != expected_result)
        handle_error();

    cout << "________________________________________\n";
}


int main()
{
    test("iwilli", true);
    test("iwillplaynow", true);
    test("nowplayiwill", true);
    test("iiiiiiiiiii", true);
    test("iwpn", false);

    cout << "Test passed \n";
    return 0;
}
