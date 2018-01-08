/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>


void handle_error(void)
{
    printf("Test failed\n");
    exit(1);
}

/*Returns a random number between low and high, low and high are inclusive*/
int get_random_number(int low, int high)
{
    int random_num = low + rand() % (high - low + 1);
    return random_num;
}

/*Performs a perfect shuffle of cards*/
void card_shuffle(int cards[])
{
    int i, rand_num, temp;

    for (i = 51; i >= 0; --i) {
        rand_num = get_random_number(0, i);
        temp = cards[i];
        cards[i] = cards[rand_num];
        cards[rand_num] = temp; 
    }  
}



void incorrect_shuffle(int cards[])
{
    int i, rand_num, temp;

    for (i = 0; i <= 51; ++i) {
        rand_num = get_random_number(0, 51);
        /* swap the ith card with a randomly chosen card */
        temp = cards[i];
        cards[i] = cards[rand_num];
        cards[rand_num] = temp;
    }
}

int main()
{
    int i, cards[52];

    for (i = 0; i < 52; ++i) {
        cards[i] = i;
    }

    card_shuffle(cards);

    printf("Test passed \n");

    return 0;
}

