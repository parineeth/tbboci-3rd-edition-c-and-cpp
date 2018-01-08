/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdlib.h>
#include <iostream>
#include <unordered_map>

using namespace std;

#define MAX_NUM_ITERATIONS 50


/* 
IMPORTANT: WE NEED TO COMPILE THIS CODE WITH THE OPTION -std=c++11
*/

void handle_error()
{
    cout << "Error occured\n";
    exit(1);
}



struct node
{
    int key;
    int value;
    struct node *prev;
    struct node *next;
};


struct lru_cache
{
    int max_size; /*Maximum number of nodes that the cache can hold*/
    int count; /*current number of nodes in the cache*/
    struct node *head; /*Head of the doubly linked list*/
    struct node *tail; /*Tail of the doubly linked list*/
    unordered_map<int, struct node*> *ht; /*hash table*/
};


struct lru_cache* lru_create(int max_size)
{
    struct lru_cache *cache = new struct lru_cache;
    cache->ht = new unordered_map<int, struct node*>();
    cache->max_size = max_size;
    return cache;
}


/*
cache - the LRU cache
new_item - new node to be added to the LRU cache
Return value: 0 on success
*/
int lru_add(struct lru_cache *cache, struct node *new_item)
{
    if (cache->count == cache->max_size) {
        /*The cache is full. So remove the last node from the linked list */
        struct node *temp = cache->tail;

        cache->tail = cache->tail->prev;

        if (cache->tail == NULL)
            cache->head = NULL;
        else
            cache->tail->next = NULL;

        cache->count--;

        /*Remove the last node from the hash table*/
        cache->ht->erase(temp->key);

        delete temp; /*Free the last node*/
    }

    /*Add the new node to the front of the linked list*/
    new_item->prev = NULL;
    new_item->next = cache->head;

    if (cache->head)
        cache->head->prev = new_item;

    cache->head = new_item;

    if (!cache->tail)
        cache->tail = new_item;

    cache->count++;

    /*Add the new node to the hash table*/
    cache->ht->emplace(new_item->key, new_item);

    return 0;
}






/*
cache - LRU cache
key - key for the node that should be fetched from the cache
Return value: node corresponding to the key
*/
struct node* lru_get(struct lru_cache *cache, int key)
{
    struct node *cur_node;

    /*Get the node pointer from the key using the hash table
    "auto" is used to automatically find the type of the variable "it"
    based on the return value of the stl hash table find function */
    auto it = cache->ht->find(key);

    /*it is an iterator. If it == cache->ht->end(), then it is invalid
    and it means that the key was not found in the hash table */
    if (it == cache->ht->end())
        return NULL;

    /*it->first gives the key and it->second gives the data which in 
    this case is the node corresponding to the key*/
    cur_node = it->second;

    /*If the node being fetched is at the head of the linked list, then 
    simply return*/
    if (cache->head == cur_node)
        return cur_node;

    /*
    The node being fetched is not at the front. So detach it from the linked
    list and add it to the beginning. If the node was removed from the tail,  
    then update the tail
    */
    if (cache->tail == cur_node)
        cache->tail = cur_node->prev;

    cur_node->prev->next = cur_node->next;
    if (cur_node->next)
        cur_node->next->prev = cur_node->prev;

    cur_node->prev = NULL;
    cur_node->next = cache->head;
    cache->head->prev = cur_node;
    cache->head = cur_node;

    return cur_node;
}




/*Check that we don't exceed the maximum size of the lru_cache*/
void lru_verify(struct lru_cache *cache)
{
    struct node *cur_node;
    int count;

    /*If there are no items in the cache, then head and tail should be NULL*/
    if (cache->count == 0) {
        if (cache->head != NULL || cache->tail != NULL)
            handle_error();
        return;
    }

    /*head->prev should be NULL*/
    if (cache->head->prev != NULL)
        handle_error();

    /**tail->next should be NULL*/
    if (cache->tail->next != NULL)
        handle_error();

    /*If there is only 1 item in the cache, then head and tail should be identical*/
    if (cache->count == 1) {
        if (cache->head != cache->tail)
            handle_error();

        return;
    }

    /*Count the number of nodes in cache from the head and verify if it matches cache->count*/
    cur_node = cache->head;
    count = 0;
    while (cur_node != NULL) {
        count++;
        cur_node = cur_node->next;
    }

    if (count != cache->count)
        handle_error();


    /*Count the number of nodes in cache from the tail and verify if it matches cache->count*/
    cur_node = cache->tail;
    count = 0;
    while (cur_node != NULL) {
        count++;
        cur_node = cur_node->prev;
    }

    if (count != cache->count)
        handle_error();

    return;
}



void test_01(int max_size)
{
    struct lru_cache *cache = lru_create(max_size);
    int key = 0;
    int rand_num;
    struct node *new_node, *cur_node;
    int i;

    for ( i = 0; i < MAX_NUM_ITERATIONS; ++i) {

        /*Perform either the add or the get operation based on random number*/
        rand_num = rand() % 2;

        if (rand_num == 0) {
            /*Perform the add operation*/
            new_node = new struct node;
            new_node->key = key++;
            lru_add(cache, new_node);
        } else {
            /*Perform the get operation*/
            int search_key = rand() % (key + 1);
            cur_node = lru_get(cache, search_key);

            if (cur_node) {
                /*Since we just accessed the cur_node in the cache, the head of cache
                should point to it*/
                if (cache->head != cur_node)
                    handle_error();
            } else {
                /*We didn't find the key in the cache. Verify that the key doesn't
                exist in the cache*/
                cur_node = cache->head;
                while (cur_node != NULL) {
                    if (cur_node->key == search_key)
                        handle_error();
                    cur_node = cur_node->next;
                }
            }

        }


        lru_verify(cache);
    }

}


int main()
{
    int max_size;

    /*Test for different max sizes of LRU cache*/
    for (max_size = 1; max_size <= 20; ++max_size)
        test_01(max_size);

    cout << "Test passed \n";
    return 0;
}
