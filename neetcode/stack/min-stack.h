// https://leetcode.com/problems/min-stack/

#include <stack>

class MinStack
{
private:
    // keep pairs where first is element and second is the global minimum
    // can also be achivied with 2 stacks
    std::stack<std::pair<int, int>> stack;

public:
    MinStack()
    {
    }

    void push(int val)
    {
        int min = val;
        if (!stack.empty())
        {
            min = std::min(min, stack.top().second);
        }

        stack.push({val, min});
    }

    void pop()
    {
        stack.pop();
    }

    int top()
    {
        return stack.top().first;
    }

    int getMin()
    {
        return stack.top().second;
    }
};