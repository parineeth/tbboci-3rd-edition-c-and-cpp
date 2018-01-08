/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdlib.h>
#include <iostream>
#include <stack>

using namespace std;


void handle_error(void)
{
    cout<<"Test failed\n";
    exit(1);
}


/*Verify if the braces, brackets and parenthesis are properly nested */
void verify(char *str1)
{
    stack<char> s;
    int i = 0;

    while (str1[i]) {
        char c, top_char;
        
        c = str1[i];
        if (c == '{' || c == '[' || c == '(') {
            /*If we get an opening brace, bracket or parenthesis in string, 
            then push it on to the stack*/
            s.push(c);
        } else if (c == '}' || c == ']' || c == ')') {
            /*If we get a closing brace, bracket or parenthesis in string, 
            then the character on top of stack should be the corresponding opening
            character*/
            if (s.empty())
                handle_error();

            top_char = s.top();
            if (c == '}' && top_char != '{')
                handle_error();
            else if (c == ']' && top_char != '[')
                handle_error();
            else if (c == ')' && top_char != '(')
                handle_error();

            /*Since we have matched the opening and closing character,
            remove the opening character from the stack*/
            s.pop();
        } else {
            /*We found a character other than a brace, bracket or parenthesis*/
            handle_error();
        }
        ++i;
    }

    /*At the end of processing the stack, the stack should be empty*/
    if (!s.empty())
        handle_error();
}


void process_string(char str1[])
{
    cout<<str1<<endl;
    verify(str1);
}

/*Helper function for finding the nearest unmatched opening character
str1: input string containing braces, brackets and parenthesis
pos: we will search for unmatched opening character from pos - 1 to 0
Return value: index of the first unmatched character when traversing from
    pos - 1 to 0  if it exists, -1 otherwise*/
int find_unmatched(char str1[], int pos)
{
    int back_pos = pos - 1;
    int n_braces = 0, n_brackets = 0, n_parenthesis = 0;

    /*When we get a closing character, decrement the count by 1,
    when we get an opening character, increment the count by 1*/
    while (back_pos >= 0) {
        if (str1[back_pos] == '{') 
            n_braces++;
        else if (str1[back_pos] == '[')
            n_brackets++;
        else if (str1[back_pos] == '(')
            n_parenthesis++;
        else if (str1[back_pos] == '}')
            n_braces--;
        else if (str1[back_pos] == ']')
            n_brackets--;
        else if (str1[back_pos] == ')')
            n_parenthesis--;

        /*If we encounter more opening characters than closing
        characters as we traverse backwards, then we have found
        the location of the mismatch*/
        if (n_braces > 0 || n_brackets > 0 || n_parenthesis > 0)
            return back_pos;

        back_pos--;
    }
    return -1;
}

/*Main function for printing the braces, brackets and parenthesis
str1: string used to store braces, brackets and parenthesis
pos: next free position in the string str1
n_max: maximum number of opening characters (equal to max closing characters)
n_open: number of opening characters currently in str1
n_close: number of closing characters currently in str1
*/
void print_nesting(char *str1, int pos, int n_max, int n_open, int n_close) {
    /*Condition for terminating the recursion*/
    if (n_close == n_max) {
        str1[pos] = 0;
        process_string(str1);
        return;
    }

    if (n_open < n_max) {
        /*Add an opening brace and call print_nesting recursively*/
        str1[pos] = '{';
        print_nesting(str1, pos+1, n_max, n_open + 1, n_close);

        /*Add an opening bracket and call print_nesting recursively*/
        str1[pos] = '[';
        print_nesting(str1, pos+1, n_max, n_open + 1, n_close);

        /*Add an opening parenthesis and call print_nesting recursively*/
        str1[pos] = '(';
        print_nesting(str1, pos+1, n_max, n_open + 1, n_close); 
    }

    int unmatched_pos = find_unmatched(str1, pos);
    if (n_open > n_close && unmatched_pos >= 0) {
        /*to balance the characters, add the closing character corresponding
        to nearest unmatched character and call print_nesting recursively*/
        char unmatched_char = str1[unmatched_pos];
        
        if (unmatched_char == '{') {
            str1[pos] = '}';
            print_nesting(str1, pos+1, n_max, n_open, n_close + 1);
        } else if (unmatched_char == '[') {
            str1[pos] = ']';
            print_nesting(str1, pos+1, n_max, n_open, n_close + 1);
        } else if (unmatched_char == '(') {
            str1[pos] = ')';
            print_nesting(str1, pos+1, n_max, n_open, n_close + 1);
        }
    }
}






void test_01()

{
    int i;
    char str1[10];


    for (i = 1; i <= 4; ++i) {
        print_nesting(str1,  0, i, 0, 0) ;
        cout<<"\n______________________________________\n";

    }
}


int main()
{
    test_01();

    cout<<"Test passed" << endl << flush;
    return 0;
}



