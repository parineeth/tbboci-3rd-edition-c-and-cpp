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


/*
Verify if the braces, brackets and parenthesis are properly nested 
str1: input string containing braces, brackets and parenthesis
Return value: 1 if the nesting is proper, 0 otherwise 
*/
int validate_nesting(const char *str1) {
    stack<char> s;
    int i = 0;

    while (str1[i]) {
        char c, top_char;
        
        c = str1[i];
        if (c == '{' || c == '[' || c == '(') {
            /*If we get an opening brace, bracket or parenthesis 
            in string, then push it on to the stack*/
            s.push(c);
        } else if (c == '}' || c == ']' || c == ')') {
            /*If we get a closing brace, bracket or parenthesis  
            in string, then the character on top of stack should be 
            the corresponding opening character*/
            if (s.empty())
                return 0;

            top_char = s.top();
            if (c == '}' && top_char != '{')
                return 0;
            else if (c == ']' && top_char != '[')
                return 0;
            else if (c == ')' && top_char != '(')
                return 0;

            /*Since we have matched the opening and closing character,
            remove the opening character from the stack*/
            s.pop();
        } else {
            /*We found a character other than a brace, bracket 
            or parenthesis*/
            return 0;
        }
        ++i;
    }

    /*At the end of processing, the stack should be empty*/
    if (!s.empty())
        return 0;

    return 1;
}








void test(const char str1[], int expected_result)
{
    int result;

    result = validate_nesting(str1);

    if (result)
        cout << str1 << " => is balanced " << endl;
    else 
        cout << str1 << " => is NOT balanced " << endl;

    if (result != expected_result)
        handle_error();
}


int main()
{
    test("[{()}]", 1);
    test("[{]", 0);

    cout<<"Test passed" << endl;
    return 0;
}



