/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>





void handle_error()
{
    printf("Test failed \n");
    exit(1);
}


struct AnagramHelper
{
    char *word;
    int index;
};


void print_helper(struct AnagramHelper helper[], int num_words)
{
    int i;
    for (i = 0; i < num_words; ++i) {
        printf("[ %s , %d] ", helper[i].word, helper[i].index) ;
    }
    printf("\n");
}

/*Helper function for comparing characters. It is used during quicksort*/
int char_cmp_function(const void *p1, const void *p2) {
    char *x = (char*)p1;
    char *y = (char*)p2;

    if (*x < *y)
        return -1;
    else if (*x == *y)
        return 0;
    else 
        return 1;
}

/*Sorts the characters in a string*/
void sort_word(char buffer[], int length) {
    qsort(buffer, length, sizeof(char), char_cmp_function);
}

/*Helper function for comparing words. It is used during quicksort*/
int helper_cmp_function(const void *p1, const void *p2)
{
    struct AnagramHelper *x = (struct AnagramHelper*)p1;
    struct AnagramHelper *y = (struct AnagramHelper*)p2;

    return strcmp(x->word, y->word);
}

/*Sorts the anagram helper array based on the words in it*/
void sort_anagram_helper(struct AnagramHelper helper[], int num_words)
{
    qsort(helper, num_words, sizeof(struct AnagramHelper), 
            helper_cmp_function);
}

/*
word_list: list of words that should be sorted so that the anagrams occur together
num_words: Number of elements in the word_list
*/
void anagram_sort(char *word_list[], int num_words) 
{
    struct AnagramHelper *helper = (struct AnagramHelper*) calloc(num_words, 
                        sizeof(struct AnagramHelper));
    int i, length;
    char **scratchpad;

    for (i = 0; i < num_words; ++i) {
        length = strlen(word_list[i]);

        /*Allocate memory for the word in the helper and copy 
        the original word into it. Add 1 to length for '\0' character*/
        helper[i].word = (char*) calloc(1, length + 1);
        strcpy(helper[i].word, word_list[i]);       
        
        /*First sort the characters of the word in the helper*/
        sort_word(helper[i].word, length);
        
        /*Store the original index of the word in the helper*/
        helper[i].index = i;
    }

    /*Sort all the words in the helper*/
    sort_anagram_helper(helper, num_words);
    
    /*We need to move the words in word_list based on the indexes in the 
    helper. We can't directly move the char pointers in the words array.
    First we will copy the char pointers into a scratchpad array
    based on the indexes in the helper and then copy the scratchpad
    array into the word_list array.
    */
    scratchpad = (char**) calloc(num_words, sizeof(char *));


    for (i = 0; i < num_words; ++i) {
        int index = helper[i].index;
        scratchpad[i] = word_list[index];
    }

    for (i = 0; i < num_words; ++i) {
        word_list[i] = scratchpad[i];
    }
    
    free(scratchpad);
    free(helper);
}


void print_words(char *words[], int num_words)
{
    int i;
    
    for (i = 0; i < num_words; ++i) {
        printf("%s ", words[i]);
    }

    printf("\n");
}

void test()
{
    int i;
    int num_words = 6;
    char *word_list[] = { "rat", "atm", "hill", "art", "mat", "tar"};
    char *expected_result[] = {"atm", "mat", "rat", "art", "tar", "hill"}; 

    printf("Before sorting: ");
    print_words(word_list, num_words);  

    anagram_sort(word_list, num_words);

    printf("After  sorting: ");
    print_words(word_list, num_words);  

    for (i = 0; i < num_words; ++i) {
        if (strcmp(word_list[i], expected_result[i]) != 0) {
            handle_error();
        }
    }

}






int main()
{
    test();

    printf("Test passed\n");
    return 0;
}
