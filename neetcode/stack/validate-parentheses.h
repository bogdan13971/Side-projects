// https://neetcode.io/problems/validate-parentheses

#include <stack>
#include <string>

bool isOpen(char c)
{
    return c == '(' || c == '[' || c == '{';
}

bool areClosed(char c1, char c2)
{
    return c1 == '(' && c2 == ')' ||
           c1 == '[' && c2 == ']' ||
           c1 == '{' && c2 == '}';
}

bool isValid(std::string s)
{
    std::stack<char> stack;
    for (char c : s)
    {
        if (isOpen(c))
        {
            stack.push(c);
        }
        else
        {
            if (!stack.empty() && areClosed(stack.top(), c))
            {
                stack.pop();
            }
            else
            {
                return false;
            }
        }
    }

    return stack.empty();
}