#include <iostream>
#include <string>
#include <stack>
#include <string.h>
#include <stdlib.h>

using namespace std;

#define MAX_STR_LEN (10)

void handle_error() 
{
    cout << "Test failed\n";
    exit(1);
}

/* Helper function that picks the operator from the top of operator stack
and applies them on the two values at the top of the num_stack. The result
will then be pushed back onto the num_stack */
void compute(stack<int>& num_stack, stack<char>& operator_stack) {
    int value1, value2;
    char c;

    c = operator_stack.top();
    operator_stack.pop();

    /*Since stack is LIFO we will first pop value2 and then pop value1 */
    value2 = num_stack.top();
    num_stack.pop();

    value1 = num_stack.top();
    num_stack.pop();

    if (c == '+') 
        num_stack.push(value1 + value2);
    else if (c == '-')
        num_stack.push(value1 - value2);
    else if (c == '*')
        num_stack.push(value1 * value2);
    else if (c == '/')
        num_stack.push(value1 / value2);
    
}

/* Helper function to check precedence of operators
stack_operator: operator that is at the top of the operator stack
exp_operator: operator that is currently being examined in the expression
Return value: true if the operator in the stack is equal or greater 
precedence than operator being examined in the expression
*/
bool is_eq_or_grt_precedence(char stack_operator, char exp_operator)
{
    if ((stack_operator == '*' || stack_operator == '/') && 
        (exp_operator == '+' || exp_operator == '-'))
        return true;

    if (stack_operator == exp_operator)
        return true;
    
    return false;
}

/*Main function for evaluating an expression
expression: string containing the expression to be evaluated
Return value: the integer result value obtained by evaluating the expression
*/
int evaluate_expression(const string& expression)
{
    stack<int> num_stack;
    stack<char> operator_stack;
    int i, cur_value;
    int length = expression.length();
    char temp_str[MAX_STR_LEN];

    i = 0;
    while (i < length) {
        /*Skip the white space characters*/
        if (expression[i] == ' ' || expression[i] == '\t' 
        || expression[i] == '\n') {
            ++i;
            continue;
        } 
        
        /*If we encounter an integer, then parse out the digits in it*/ 
        if (expression[i] >= '0' && expression[i] <= '9') {
            int pos = 0;
            while (i < length && expression[i] >= '0' 
            && expression[i] <= '9') {
                temp_str[pos++] = expression[i];
                ++i;
            }
            temp_str[pos] = '\0';
            cur_value = atoi(temp_str);
            num_stack.push(cur_value);

        } else if (expression[i] == '(') {
            operator_stack.push(expression[i]);
            ++i;

        } else if (expression[i] == ')') {
            /*Till we encounter '(', process the two stacks*/
            while (operator_stack.top() != '(') {
                compute(num_stack, operator_stack);
            }
            operator_stack.pop(); /*pop out '('*/
            ++i;            
        } else if (expression[i] == '+' || expression[i] == '-' ||
            expression[i] == '*' || expression[i] == '/') {
            /*
            As long as the operator in the stack is of higher precedence
            than the current token in expression, keep processing the 
            two stacks 
            */
            while (!operator_stack.empty() 
            && is_eq_or_grt_precedence(operator_stack.top(), expression[i])) {
                compute(num_stack, operator_stack);
            }
            operator_stack.push(expression[i]);
            ++i; 
        }

    }

    /*If there are still operators in the operator stack, then process them*/
    while (!operator_stack.empty())
        compute(num_stack, operator_stack);

    /*The result will be present at the top of the num_stack*/
    return num_stack.top();
}


void test(const string& expression, int expected_result)
{
    int result = evaluate_expression(expression);

    cout << expression << " = " << result << endl;

    if (result != expected_result)
        handle_error();
}


int main()
{
    test("20 * 40", 800);

    test("10 + 10 * 40", 410);

    test("(200 - (100 + 50)) * 30 / 10", 150); 

    test("2 - 6 - 7", -11);

    test("2 + 5 - 1", 6);

    test("5 * 6 + 40", 70);

    test("7 / 10 * 100 + 87", 87);

    cout << "Test passed \n";
    return 0;
}
