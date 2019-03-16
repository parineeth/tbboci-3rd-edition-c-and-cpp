/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void handle_error(void)
{
    printf("Test failed\n");
    exit(1);
}



/*str1: non-NULL input character string
Return value: length of longest palindrome
*/
int find_longest_palindrome(char *str1)  {
    int n, left, pos, right, max_pal_len, cur_pal_len;

    n = strlen(str1);
    max_pal_len = 0;
    for (pos = 0; pos < n; ++pos)  {
        /*Check for odd length palindromes by comparing the characters
        to the left of pos with the characters to the right of pos
        */
        left = pos - 1;
        right = pos + 1;
        cur_pal_len = 1;
        while (left >= 0 && right <= n - 1)  {
            if (str1[left] != str1[right])
                break;
            cur_pal_len += 2;
            --left;
            ++right;
        }

        if (cur_pal_len > max_pal_len)
            max_pal_len = cur_pal_len;

        /*Check for even length palindromes. If str1[pos], matches
        with str1[pos+1], then compare the characters to the left of
        pos with the characters to the right of pos+1
        */
        if (str1[pos] == str1[pos + 1])  {
            left = pos - 1;
            right = pos + 2;
            cur_pal_len = 2;
            while (left >= 0 && right <= n - 1)  {
                if (str1[left] != str1[right])
                    break;
                cur_pal_len += 2;
                --left;
                ++right;
            }

            if (cur_pal_len > max_pal_len)
                max_pal_len = cur_pal_len;
        }
    }
    return max_pal_len;
}



void test_01(char *str1, int expected_result)
{
    int result;

    result = find_longest_palindrome(str1);

    printf("Length of longest palindrome in %s = %d\n", str1, result);

    if (result != expected_result)
        handle_error();
}

int main()
{

    test_01("RACECAR", 7);

    test_01("AABB", 2);

    test_01("ABBA", 4);

    test_01("ACBBDA", 2);

    test_01("ABCDE", 1);/*A single character in the string can be treated as a palindrome*/

    printf("Test passed\n");
    return 0;
}
