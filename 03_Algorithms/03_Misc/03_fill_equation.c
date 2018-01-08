#include <stdio.h>
#include <stdlib.h>

#define MAX_ARRAY_SIZE (100)

void handle_error()
{
    printf("Test failed \n");
    exit(1);
}

/* Helper function that evaluates the numbers and operators
a: array of numbers
n: how many elements are present in array a. Should be >= 1
operators: array of operators (+, -) to be applied on numbers
*/
int evaluate(int a[], int n, char operators[])
{
    int i, result = a[0];

    for (i = 1; i < n; ++i) {
        if (operators[i-1] == '+')
            result += a[i];
        else 
            result -= a[i];
    }

    return result;
}

/*
a: array of numbers
n: how many elements are present in array a. Should be >= 1
rhs: right hand side of the equation
operators: array for storing the operators to be applied on the numbers
num_operators: number of operators that have been filled so far
Return value: 1 if we can obtain the rhs by placing operators between numbers
*/
int fill_operators(int a[], int n, int rhs, char operators[], int num_operators)
{
    int is_possible, result;

    if (num_operators == n - 1) {
        /*We have filled in all the operators. So evaluate the result and
        terminate the recursion*/
        result = evaluate(a, n, operators);
        if (result == rhs) 
            return 1;
        else
            return 0;
    }
    
    /*Fill in + as the next operator and try out*/
    operators[num_operators] = '+';
    is_possible = fill_operators(a, n, rhs, operators, num_operators + 1);
    if (is_possible)
        return 1;

    /*Fill in - as the next operator and try out*/
    operators[num_operators] = '-';
    is_possible = fill_operators(a, n, rhs, operators, num_operators + 1);

    return is_possible;
}



void test()
{
    int i, n = 3;
    int a[MAX_ARRAY_SIZE] = {10, 20, 30};
    char operators[MAX_ARRAY_SIZE];
    int rhs = -40;
    int is_possible;
    
    is_possible = fill_operators(a, n, rhs, operators, 0);

    /*We should be able to get -40 since 10 - 20 - 30 = -40 */
    if (is_possible == 0)
        handle_error();

    printf("%d ", a[0]);
    for (i = 1; i <= n - 1; ++i) {
        printf("%c ", operators[i-1]);
        printf("%d ", a[i]);
    }
    printf(" = %d \n", rhs);
    printf("\n");  
}








int main()
{
    test();

    printf("Test passed\n");
    return 0;
}
