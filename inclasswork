#include <iostream>
#include <stack>
#include <string>
#include <cctype>

using namespace std;

int prec(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    if (c == '^') return 3;
    return 0;
}

void infixToPostfix(string s, string &postfix) {
    stack<char> st;
    postfix = "";
    
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];

        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
            postfix += c;
        } else if (c == '(') {
            st.push('(');
        } else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                postfix += st.top();
                st.pop();
            }
            st.pop(); 
        } else {
            while (!st.empty() && prec(c) <= prec(st.top())) {
                postfix += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    while (!st.empty()) {
        postfix += st.top();
        st.pop();
    }
}

struct Stack {
    int top;
    unsigned capacity;
    int* array;
};

struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, int value) {
    stack->array[++stack->top] = value;
}

int pop(struct Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return -1;
}

int evaluatePostfix(string exp) {
    struct Stack* stack = createStack(exp.length());
    if (!stack) return -1;

    for (int i = 0; i < exp.length(); i++) {
        if (isdigit(exp[i])) {
            push(stack, exp[i] - '0');
        } else {
            int val1 = pop(stack);
            int val2 = pop(stack);
            switch (exp[i]) {
                case '+': push(stack, val2 + val1); break;
                case '-': push(stack, val2 - val1); break;
                case '*': push(stack, val2 * val1); break;
                case '/': push(stack, val2 / val1); break;
            }
        }
    }
    return pop(stack);
}

int main() {
    string infixExp, postfixExp;
    cout<<"input: ";
    cin >> infixExp;    
    infixToPostfix(infixExp, postfixExp);
    cout << postfixExp << endl;
    int result = evaluatePostfix(postfixExp);
    cout << result << endl;  
    return 0;
}
