#include <stdlib.h>
#include <iostream>
#include <stack>

using namespace std;


void handle_error(void)
{
    cout<<"Test failed " << endl;
    exit(1);
}


void print_array(int a[], int n)
{
    int i;
    for (i = 0; i < n; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
}


/*histo_height: histo_height[i] has height of ith bar
n: number of bars in the histogram. Should be >= 1
Return value: returns the area of the largest rectangle in the histogram
*/
int find_max_area(int histo_height[], int n)
{
    int i, area, popped_index, popped_height, max_area = 0;
    stack<int> height_stack; /*used for storing the height of the bars*/
    stack<int> index_stack; /*used for storing the index of the bars*/

    for (i = 0; i < n; ++i) {
        if ( height_stack.empty() || histo_height[i] > height_stack.top() ) {
            /*push height and index of current bar*/
            height_stack.push(histo_height[i]);
            index_stack.push(i);

        } else if (histo_height[i] < height_stack.top()) {

            while (!height_stack.empty() && 
            histo_height[i] < height_stack.top()) {
                /* keep popping from index and height stacks*/
                popped_index = index_stack.top();
                index_stack.pop();
                popped_height = height_stack.top();
                height_stack.pop();

                /* calculate the area from popped bar to the 
                current bar. 
                Area = popped height * difference of index of 
                current bar and popped bar*/
                area =  popped_height * (i - popped_index);

                if (area > max_area)
                    max_area = area;
            }

            /*push height of the current bar into the height stack */
            height_stack.push(histo_height[i]);


            /*push the LAST POPPED INDEX into the index stack, 
            since we can form a rectangle from the LAST POPPED INDEX 
            to the current bar (where the height of the rectangle is 
            height of current bar)*/
            index_stack.push(popped_index);
        }
    }

    
    /*Process the remaining elements in the stacks*/
    while (!height_stack.empty() ) {
        popped_index = index_stack.top();
        index_stack.pop();
        area = height_stack.top() * (n - popped_index);
        height_stack.pop();

        if (area > max_area)
            max_area = area;
    }

    return max_area;
}





void test_01()
{
    int n = 7;
    int histo_height[] = {3, 2, 5, 6, 1, 4, 4};
    int max_area;

    max_area = find_max_area(histo_height, n);

    cout << "Histogram: ";
    print_array(histo_height, n);
    cout << "Max area = " << max_area << endl;

    if (max_area != 10)
        handle_error();

    cout << "____________________________________" << endl;
}


void test_02()
{
    int n = 4;
    int histo_height[] = {2, 4, 2, 1};
    int max_area;

    max_area = find_max_area(histo_height, n);

    cout << "Histogram: ";
    print_array(histo_height, n);
    cout<<"Max area = " << max_area << endl;

    if (max_area != 6)
        handle_error();

    cout << "____________________________________" << endl;
}



int main()
{
    test_01();

    test_02();

    cout << "Test passed " << endl;
    return 0;
}
